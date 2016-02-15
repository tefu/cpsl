%{
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "instructions.hpp"
#include "ProgramNode.hpp"
#include "Expression.hpp"

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
  std::cout << "I parsed " << std::setw(28) << term << " at line " << std::setw(5) << yylineno << " (!)\n";
}

%}

/* Types
------------------------------------------------------------------ */
%union {
  int integer;
  bool boolean;
  std::string* string_constant;
  Expression* expr;
  ProgramNode* node;
  std::vector<Expression*>* exprList;
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
%token IDENT
%token <integer> INTEGER
%token <string_constant> STRING
%token <string_constant> CHAR

/* Nonterminals
------------------------------------------------------------------ */
%type <node> program
%type <expr> expression
%type <expr> optional_expression
%type <exprList> optional_expression_list
%type <exprList> expression_list



%%


program : optional_constant_decl
          optional_type_decl
          optional_var_decl
          optional_proc_or_func_decls
          block {parsed("Block");}
          DOT
          {parsed("Program");}
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

proc_or_func_decls : func_decl {parsed("Function Declaration");}
                   | proc_decl {parsed("Procedure Declaration");}
                   | func_decl proc_or_func_decls
                   | proc_decl proc_or_func_decls
                   ;

constant_decl : CONST definitions {parsed("Constant Declaration");}
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

block : BEGIN_KW statement_sequence END
      ;


type_decl : TYPE type_definitions {parsed("Type Declaration"); }
          ;

type_definitions : IDENT EQUALITY type SEMICOLON
                 | type_definitions IDENT EQUALITY type SEMICOLON
                 ;

type : simple_type
     | record_type
     | array_type
     ;

simple_type : IDENT
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

ident_list : IDENT
           | ident_list COMMA IDENT
           ;

var_decl : VAR members {parsed("Variable Declaration");}
         ;


statement_sequence : statement
                   | statement_sequence SEMICOLON statement

statement : assignment
          | if_statement
          | while_statement
          | repeat_statement
          | for_statement
          | stop_statement { std::cout << "I parsed a stop statement, ya bastard!" << std::endl;
                             sout << MIPS::system_call(10) << std::endl; }
          | return_statement
          | read_statement
          | write_statement
          | procedure_call
          | null_statement
          ;

assignment : l_value ASSIGNMENT expression
           ;

if_statement : IF expression THEN statement_sequence optional_else_ifs optional_else END
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

for_statement : FOR IDENT ASSIGNMENT expression polarity expression
                DO statement_sequence END
              ;

polarity : TO
         | DOWNTO
         ;

stop_statement : STOP
               ;

return_statement : RETURN optional_expression
                 ;

read_statement : READ LEFT_PAREN l_value_list RIGHT_PAREN
               ;


write_statement : WRITE LEFT_PAREN expression_list RIGHT_PAREN
                 ;


procedure_call : IDENT LEFT_PAREN optional_expression_list RIGHT_PAREN
               ;

null_statement :
               ;

optional_expression_list : expression_list { $$ = $1; }
                         | { $$ = nullptr; }
                         ;

expression_list : expression { $$ = new std::vector<Expression*>(); $$->push_back($1); }
                | expression_list COMMA expression { $$ = $1; $$->push_back($3); }
                ;

optional_expression : expression { $$ = $1; }
                    | { $$ = nullptr; }
                    ;

expression : expression OR expression { $$ = new LogicalOr{$1, $3}; }
           | expression AND expression { $$ = new LogicalAnd{$1, $3}; }
           | expression EQUALITY expression { $$ = new Equality{$1, $3}; }
           | expression INEQUALITY expression { $$ = new Inequality{$1, $3}; }
           | expression LESS_THAN_OR_EQUAL expression { $$ = new LessThanOrEqual{$1, $3}; }
           | expression LESS_THAN expression { $$ = new LessThan{$1, $3}; }
           | expression GREATER_THAN_OR_EQUAL expression { $$ = new GreaterThanOrEqual{$1, $3}; }
           | expression GREATER_THAN expression { $$ = new GreaterThan{$1, $3}; }
           | expression PLUS expression { $$ = new OperatorPlus{$1, $3}; }
           | expression MINUS expression { $$ = new OperatorMinus{$1, $3}; }
           | expression MULT expression { $$ = new OperatorMult{$1, $3}; }
           | expression DIVIDE expression { $$ = new OperatorDivide{$1, $3}; }
           | expression MODULUS expression { $$ = new OperatorModulus{$1, $3}; }
           | NEGATION expression { $$ = new Negation{$2}; }
           | MINUS expression %prec UNARY_MINUS { $$ = new UnaryMinus{$2}; }
           | LEFT_PAREN expression RIGHT_PAREN { $$ = $2; }
           | IDENT LEFT_PAREN optional_expression_list RIGHT_PAREN { $$ = new FunctionCall{$3}; }
           | CHR LEFT_PAREN expression RIGHT_PAREN { $$ = new ToChar{$3}; }
           | ORD LEFT_PAREN expression RIGHT_PAREN { $$ = new ToInt{$3}; }
           | PRED LEFT_PAREN expression RIGHT_PAREN { $$ = new Predecessor{$3}; }
           | SUCC LEFT_PAREN expression RIGHT_PAREN { $$ = new Successor{$3}; }
           | CHAR { $$ = new StringLiteral{$1}; }
           | STRING { $$ = new StringLiteral{$1}; }
           | INTEGER { $$ = new IntLiteral{$1}; }
           | l_value { $$ = new LValue(); }
           ;

l_value_list : l_value
             | l_value_list COMMA l_value
             ;

l_value : IDENT
        | l_value DOT IDENT
        | l_value LEFT_BRACKET expression RIGHT_BRACKET
        ;



%%


