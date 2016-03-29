%{
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "instructions.hpp"
#include "ProgramNode.hpp"
#include "Expression.hpp"
#include "ParseTree.hpp"
#include "Block.hpp"

namespace PT = ParseTree;

extern int yylex();
extern int yylineno;
extern std::stringstream sout;
extern char* yytext;

void yyerror(const char* message)
{
  std::cout << "Build failed: " << message << " at line " << yylineno << " with "
  << yytext << "." << std::endl;
  exit(EXIT_FAILURE);
}

void parsed(std::string term)
{
  std::cout << "I parsed " << std::setw(28) << term
            << " at line " << std::setw(5) << yylineno << " with val: "
            << yytext << "\n";
}

%}

/* Types
------------------------------------------------------------------ */
%union {
  int integer;
  bool boolean;
  std::string* string_constant;
  std::vector<std::string>* string_list;
  Expression* expr;
  std::vector<Expression*>* exprList;
  ProgramNode* node;
  std::vector<ProgramNode*>* nodeList;
  LValue* lval;
  std::vector<LValue*>* lvalList;
  ElseIf* elseif;
  std::vector<ElseIf*>* elseifList;
  FormalParameter* fparam;
  std::vector<FormalParameter*>* fparams;
  Type* cpsl_type;
  std::vector<Type*>* cpsl_types;
}

%start program

/* Keywords
------------------------------------------------------------------ */
%token ARRAY
%token BEGIN_KW
%token CHR
%token CONST
%token DO
%token DOWNTO
%token ELSE
%token ELSEIF
%token END
%token FOR
%token FORWARD
%token FUNCTION
%token IF
%token OF
%token ORD
%token PRED
%token PROCEDURE
%token READ
%token RECORD
%token REF
%token REPEAT
%token RETURN
%token STOP
%token SUCC
%token THEN
%token TO
%token TYPE
%token UNTIL
%token VAR
%token WHILE
%token WRITE


/* Operators
------------------------------------------------------------------ */
%token DOT
%token COMMA
%token COLON
%token SEMICOLON
%token LEFT_PAREN
%token RIGHT_PAREN
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token ASSIGNMENT

%left OR
%left AND
%nonassoc NEGATION
%nonassoc EQUALITY INEQUALITY LESS_THAN LESS_THAN_OR_EQUAL GREATER_THAN GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULT DIVIDE MODULUS
%nonassoc UNARY_MINUS

/* Other
------------------------------------------------------------------ */
%token <string_constant> IDENT
%token <integer> INTEGER
%token <string_constant> STRING
%token <string_constant> CHAR

/* Nonterminals
------------------------------------------------------------------ */
%type <node> program
%type <node> block
%type <node> statement
%type <node> assignment

%type <nodeList> optional_proc_or_func_decls
%type <nodeList> proc_or_func_decls
%type <node> func_decl
%type <node> proc_decl
%type <string_constant> func_head
%type <string_constant> proc_head
%type <node> body

%type <node> if_statement
%type <elseifList> optional_else_ifs
%type <elseifList> else_ifs
%type <elseif> else_if
%type <nodeList> optional_else
%type <nodeList> else


%type <node> while_statement
%type <node> repeat_statement

%type <node> for_statement
%type <lval> for_head
%type <boolean> direction

%type <nodeList> statement_sequence
%type <node> stop_statement
%type <node> return_statement
%type <node> read_statement
%type <node> write_statement
%type <node> procedure_call
%type <node> null_statement
%type <expr> expression
%type <expr> optional_expression
%type <exprList> optional_expression_list
%type <exprList> expression_list
%type <string_list> ident_list

%type <node> var_decl
%type <node> var_members

%type <fparams> formal_parameter
%type <fparams> formal_parameters
%type <fparams> some_formal_parameters
%type <boolean> optional_var_or_ref
%type <lval> l_value
%type <lvalList> l_value_list

%type <cpsl_type> type
%type <cpsl_type> simple_type
%type <cpsl_type> array_type


%%


program : symbol_table_init
          optional_constant_decl
          optional_type_decl
          optional_var_decl
          optional_proc_or_func_decls
          block
          DOT
          {$$ = PT::program($5,$6);
           sout << $$->gen_asm();}
		  ;

symbol_table_init : { Symbol::init(); }

optional_constant_decl : constant_decl
                       |
                       ;

optional_type_decl : type_decl
                   |
                   ;

optional_var_decl : var_decl
                   |
                   ;

optional_proc_or_func_decls : proc_or_func_decls { $$=$1;}
                            | { $$=new std::vector<ProgramNode*>(); }
                            ;

proc_or_func_decls : func_decl { $$= new std::vector<ProgramNode*>; $$->push_back($1); }
                   | proc_decl { $$ = new std::vector<ProgramNode*>; $$->push_back($1); }
                   | proc_or_func_decls func_decl { $$ = $1; $$->push_back($2); }
                   | proc_or_func_decls proc_decl { $$ = $1; $$->push_back($2); }
                   ;

constant_decl : CONST definitions
              ;

definitions : definition
            | definitions definition
            ;

definition : IDENT EQUALITY expression SEMICOLON { PT::ConstDecl($1,$3); }
           ;

proc_decl : proc_head FORWARD SEMICOLON { $$=nullptr; Symbol::pop_table(); }
          | proc_head body SEMICOLON { $$=PT::procedure_body($1,$2); }
          ;

proc_head : PROCEDURE IDENT LEFT_PAREN formal_parameters RIGHT_PAREN SEMICOLON
            { $$=PT::function_decl($2,$4,new Null()); }
          ;

func_decl : func_head FORWARD SEMICOLON { $$=nullptr; Symbol::pop_table(); }
          | func_head body SEMICOLON { $$=PT::procedure_body($1,$2);}
          ;

func_head : FUNCTION IDENT LEFT_PAREN formal_parameters RIGHT_PAREN COLON type SEMICOLON
          { $$=PT::function_decl($2,$4,$7);}
          ;

formal_parameters : some_formal_parameters { $$=$1; }
                  | { $$=new std::vector<FormalParameter*>; }
                  ;

some_formal_parameters : formal_parameter { $$=$1; }
                       | some_formal_parameters SEMICOLON formal_parameter
                       {  $$=$1; $$->insert($$->end(),$3->begin(),$3->end()); }
                       ;

formal_parameter : optional_var_or_ref ident_list COLON type { $$=PT::formal_parameter($1,$2,$4); }
                 ;

optional_var_or_ref : VAR {$$=true;}
                    | REF {$$=false;}
                    | {$$=true;}
                    ;

body : optional_constant_decl
       optional_type_decl
       optional_var_decl
       block { $$=$4; }
       ;

block : BEGIN_KW statement_sequence END { $$ = PT::block($2); }
      ;


type_decl : TYPE type_definitions
          ;

type_definitions : IDENT EQUALITY type SEMICOLON { PT::TypeDecl($1,$3); }
                 | type_definitions IDENT EQUALITY type SEMICOLON { PT::TypeDecl($2,$4); }
                 ;

type : simple_type {$$=$1;}
     | record_type
     | array_type {$$=$1;}
     ;

simple_type : IDENT { $$ = PT::simple_type($1); }
            ;

record_type : RECORD optional_members END
            ;

array_type : ARRAY LEFT_BRACKET expression COLON expression RIGHT_BRACKET OF type
           { $$=PT::array_type($3,$5,$8); }
           ;

optional_members : members
                 |
                 ;

members : ident_list COLON type SEMICOLON
        | members ident_list COLON type SEMICOLON
        ;

ident_list : IDENT { $$ = new std::vector<std::string>(); $$->push_back(*$1); }
           | ident_list COMMA IDENT { $$ = $1; $$->push_back(*$3); }
           ;

var_members : ident_list COLON type SEMICOLON { $$=nullptr; PT::VarDecl($1,$3); }
            | var_members ident_list COLON type SEMICOLON { $$=nullptr; PT::VarDecl($2,$4); }
            ;

var_decl : VAR var_members
         ;


statement_sequence : statement
                     { $$ = new std::vector<ProgramNode*>(); $$->push_back($1); }
                   | statement_sequence SEMICOLON statement
                     { $$ = $1; $$->push_back($3); }

statement : assignment         {$$=$1;}
          | if_statement       {$$=$1;}
          | while_statement    {$$=$1;}
          | repeat_statement   {$$=$1;}
          | for_statement      {$$=$1;}
          | stop_statement     {$$=$1;}
          | return_statement   {$$=$1;}
          | read_statement     {$$=$1;}
          | write_statement    {$$=$1;}
          | procedure_call     {$$=$1;}
          | null_statement     {$$=nullptr;}
          ;

assignment : l_value ASSIGNMENT expression { $$ = PT::assign($1, $3); }
           ;

if_statement : IF expression
               THEN statement_sequence
               optional_else_ifs
               optional_else
               END { $$= PT::if_statement($2, $4, $5, $6); }
             ;


optional_else_ifs : else_ifs { $$=$1; }
                  | { $$=nullptr; }
                  ;

else_ifs : else_if { $$=new std::vector<ElseIf*>(); $$->push_back($1); }
         | else_ifs else_if { $$=$1; $$->push_back($2); }
         ;

else_if : ELSEIF expression THEN statement_sequence { $$ = PT::else_if($2, $4); }
        ;

optional_else : else { $$=$1; }
              | { $$=nullptr; }
              ;

else : ELSE statement_sequence { $$=$2; }
     ;

while_statement : WHILE expression DO statement_sequence END { $$=PT::while_statement($2, $4); }
                ;

repeat_statement : REPEAT statement_sequence UNTIL expression { $$=PT::repeat_statement($4, $2); }
                 ;

for_statement : for_head ASSIGNMENT expression direction expression
                DO statement_sequence END { $$ = PT::for_statement($1,$3,$4,$5,$7); }
              ;

for_head: FOR IDENT { $$=PT::for_head($2); }



direction : TO { $$=true; }
          | DOWNTO { $$=false; }
          ;

stop_statement : STOP { $$ = new StopStatement(); }
               ;

return_statement : RETURN optional_expression { $$=PT::return_statement($2); }
                 ;

read_statement : READ LEFT_PAREN l_value_list RIGHT_PAREN { $$=PT::read_statement($3); }
               ;


write_statement : WRITE LEFT_PAREN expression_list RIGHT_PAREN
                  { $$ = PT::write_statement($3); }
                 ;


procedure_call : IDENT LEFT_PAREN optional_expression_list RIGHT_PAREN { auto fc=PT::function_call($1,$3); fc->release(); $$=fc;}
               ;

null_statement :
               ;

optional_expression_list : expression_list { $$ = $1; }
                         | { $$ = new std::vector<Expression*>(); }
                         ;

expression_list : expression { $$ = new std::vector<Expression*>(); $$->push_back($1); }
                | expression_list COMMA expression { $$ = $1; $$->push_back($3); }
                ;

optional_expression : expression { $$ = $1; }
                    | { $$ = nullptr; }
                    ;

expression : expression OR expression                  { $$ = PT::logical_or($1,$3); }
           | expression AND expression                 { $$ = PT::logical_and($1,$3); }
           | expression EQUALITY expression            { $$ = PT::equality($1, $3); }
           | expression INEQUALITY expression          { $$ = PT::inequality($1, $3); }
           | expression LESS_THAN_OR_EQUAL expression  { $$ = PT::less_than_or_equal($1, $3); }
           | expression LESS_THAN expression           { $$ = PT::less_than($1, $3); }
           | expression GREATER_THAN_OR_EQUAL expression
                                                       { $$ = PT::greater_than_or_equal($1, $3); }
           | expression GREATER_THAN expression        { $$ = PT::greater_than($1, $3); }
           | expression PLUS expression                { $$ = PT::plus($1, $3); }
           | expression MINUS expression               { $$ = PT::minus($1, $3); }
           | expression MULT expression                { $$ = PT::mult($1, $3); }
           | expression DIVIDE expression              { $$ = PT::divide($1, $3); }
           | expression MODULUS expression             { $$ = PT::modulus($1, $3); }
           | NEGATION expression                       { $$ = PT::negation($2);}
           | MINUS expression %prec UNARY_MINUS        { $$ = PT::unary_minus($2);}
           | LEFT_PAREN expression RIGHT_PAREN         { $$ = $2; }
           | IDENT LEFT_PAREN optional_expression_list RIGHT_PAREN
                                                       { $$ = PT::function_call($1,$3); }
           | CHR LEFT_PAREN expression RIGHT_PAREN     { $$ = PT::CHR($3); }
           | ORD LEFT_PAREN expression RIGHT_PAREN     { $$ = PT::ORD($3); }
           | PRED LEFT_PAREN expression RIGHT_PAREN    { $$ = PT::PRED($3); }
           | SUCC LEFT_PAREN expression RIGHT_PAREN    { $$ = PT::SUCC($3); }
           | CHAR                                      { $$ = PT::char_literal($1); }
           | STRING                                    { $$ = PT::string_literal($1); }
           | INTEGER                                   { $$ = PT::integer_literal($1); }
           | l_value                                   { $$ = $1->read(); }
           ;

l_value_list : l_value { $$ = new std::vector<LValue*>(); $$->push_back($1); }
             | l_value_list COMMA l_value { $$ = $1; $$->push_back($3); }
             ;

l_value : IDENT { $$ = PT::l_value($1); }
        | l_value DOT IDENT
        | l_value LEFT_BRACKET expression RIGHT_BRACKET
        ;



%%


