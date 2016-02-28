%{
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "instructions.hpp"
#include "ProgramNode.hpp"
#include "Statement.hpp"
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
%type <node> if_statement
%type <node> while_statement
%type <node> repeat_statement
%type <node> for_statement
%type <node> stop_statement
%type <node> return_statement
%type <node> read_statement
%type <node> write_statement
%type <node> procedure_call
%type <node> null_statement
%type <nodeList> statement_sequence
%type <expr> expression
%type <expr> optional_expression
%type <exprList> optional_expression_list
%type <exprList> expression_list

%type <string_constant> simple_type
%type <string_constant> type
%type <string_list> ident_list

%type <node> var_decl
%type <node> var_members
%type <lval> l_value
%type <lvalList> l_value_list





%%


program : optional_constant_decl
          optional_type_decl
          optional_var_decl
          optional_proc_or_func_decls
          block
          DOT
          {$$ = PT::program($5);
           sout << $$->gen_asm();}
		  ;

optional_constant_decl : constant_decl
                       |
                       ;

optional_type_decl : type_decl
                   |
                   ;

optional_var_decl : var_decl
                   |
                   ;

optional_proc_or_func_decls : proc_or_func_decls
                            |
                            ;

proc_or_func_decls : func_decl
                   | proc_decl
                   | func_decl proc_or_func_decls
                   | proc_decl proc_or_func_decls
                   ;

constant_decl : CONST definitions
              ;

definitions : definition
            | definitions definition
            ;

definition : IDENT EQUALITY expression SEMICOLON
           ;

proc_decl : PROCEDURE IDENT LEFT_PAREN formal_parameters RIGHT_PAREN
            SEMICOLON FORWARD SEMICOLON
          | PROCEDURE IDENT LEFT_PAREN formal_parameters RIGHT_PAREN
            SEMICOLON body SEMICOLON
          ;

func_decl : FUNCTION IDENT LEFT_PAREN formal_parameters RIGHT_PAREN
            COLON type SEMICOLON FORWARD SEMICOLON
          | FUNCTION IDENT LEFT_PAREN formal_parameters RIGHT_PAREN
            COLON type SEMICOLON body SEMICOLON
          ;


formal_parameters : some_formal_parameters
                  |
                  ;

some_formal_parameters : formal_parameter
                       | some_formal_parameters SEMICOLON formal_parameter
                       ;

formal_parameter : optional_var_or_ref ident_list COLON type
                 ;

optional_var_or_ref : VAR
                    | REF
                    |
                    ;

body : optional_constant_decl
       optional_type_decl
       optional_var_decl
       block
       ;

block : BEGIN_KW statement_sequence END { $$ = PT::block($2); }
      ;


type_decl : TYPE type_definitions
          ;

type_definitions : IDENT EQUALITY type SEMICOLON
                 | type_definitions IDENT EQUALITY type SEMICOLON
                 ;

type : simple_type {$$=$1;}
     | record_type {$$=nullptr;}
     | array_type {$$=nullptr;}
     ;

simple_type : IDENT { $$ = $1; }
            ;

record_type : RECORD optional_members END
            ;

array_type : ARRAY LEFT_BRACKET range RIGHT_BRACKET OF type
           ;

optional_members : members
                 |
                 ;

members : ident_list COLON type SEMICOLON
        | members ident_list COLON type SEMICOLON
        ;



range : expression COLON expression
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

statement : assignment {$$=$1;}
          | if_statement {$$=nullptr;}
          | while_statement {$$=nullptr;}
          | repeat_statement {$$=nullptr;}
          | for_statement {$$=nullptr;}
          | stop_statement { $$ = $1; }
          | return_statement {$$=nullptr;}
          | read_statement {$$=$1;}
          | write_statement { $$ = $1; }
          | procedure_call {$$=nullptr;}
          | null_statement { $$=nullptr; }
          ;

assignment : l_value ASSIGNMENT expression { $$ = PT::assign($1, $3); }
           ;

if_statement : IF expression
               THEN statement_sequence
               optional_else_ifs
               optional_else
               END
             ;


optional_else_ifs : else_ifs
                  |
                  ;

else_ifs : else_if
         | else_ifs else_if
         ;

else_if : ELSEIF expression THEN statement_sequence
        ;

optional_else : else
              |
              ;

else : ELSE statement_sequence
     ;

while_statement : WHILE expression DO statement_sequence END
                ;

repeat_statement : REPEAT statement_sequence UNTIL expression
                 ;

for_statement : FOR IDENT ASSIGNMENT expression direction expression
                DO statement_sequence END
              ;

direction : TO
          | DOWNTO
          ;

stop_statement : STOP { $$ = new StopStatement(); }
               ;

return_statement : RETURN optional_expression
                 ;

read_statement : READ LEFT_PAREN l_value_list RIGHT_PAREN { $$=new ReadStatement($3); }
               ;


write_statement : WRITE LEFT_PAREN expression_list RIGHT_PAREN
                  { $$ = new WriteStatement($3) ; }
                 ;


procedure_call : IDENT LEFT_PAREN optional_expression_list RIGHT_PAREN
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
                                                       { $$ = PT::function_call($3); }
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


