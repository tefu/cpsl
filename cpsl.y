%{
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
extern int yylex();
extern int yylineno;
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
  std::string* string_constant;
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
%precedence NEGATION
%nonassoc EQUALITY INEQUALITY LESS_THAN LESS_THAN_OR_EQUAL GREATER_THAN GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULT DIVIDE MODULUS
%precedence UNARY_MINUS

/* Other
------------------------------------------------------------------ */
%token IDENT
%token <integer> INTEGER
%token <string_constant> STRING
%token <string_constant> CHAR


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
                       | %empty
                       ;

optional_type_decl : type_decl
                   | %empty
                   ;

optional_var_decl : var_decl
                   | %empty
                   ;

optional_proc_or_func_decls : proc_or_func_decls
                            | %empty
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
                  | %empty
                  ;

some_formal_parameters : formal_parameter
                       | some_formal_parameters SEMICOLON formal_parameter
                       ;

formal_parameter : optional_var_or_ref ident_list COLON type
                 ;

optional_var_or_ref : VAR
                    | REF
                    | %empty
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
                 | %empty
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
          | stop_statement
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
                  | %empty
                  ;

else_ifs : else_if
         | else_ifs else_if
         ;

else_if : ELSEIF expression THEN statement_sequence
        ;

optional_else : else
              | %empty
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

null_statement : %empty
               ;


definitions : IDENT EQUALITY expression
            | IDENT EQUALITY expression SEMICOLON definitions
            ;

optional_expression_list : expression_list
                         | %empty
                         ;

expression_list : expression
                | expression_list COMMA expression
                ;

optional_expression : expression
                    | %empty
                    ;

expression : expression OR expression
           | expression AND expression
           | expression EQUALITY expression
           | expression INEQUALITY expression
           | expression LESS_THAN_OR_EQUAL expression
           | expression LESS_THAN expression
           | expression GREATER_THAN_OR_EQUAL expression
           | expression GREATER_THAN expression
           | expression PLUS expression
           | expression MINUS expression
           | expression MULT expression
           | expression DIVIDE expression
           | expression MODULUS expression
           | NEGATION expression
           | MINUS expression %prec UNARY_MINUS
           | LEFT_PAREN expression RIGHT_PAREN
           | IDENT LEFT_PAREN optional_expression_list RIGHT_PAREN
           | CHR LEFT_PAREN expression RIGHT_PAREN
           | ORD LEFT_PAREN expression RIGHT_PAREN
           | PRED LEFT_PAREN expression RIGHT_PAREN
           | SUCC LEFT_PAREN expression RIGHT_PAREN
           | l_value
           ;

l_value_list : l_value
             | l_value_list COMMA l_value
             ;

l_value : IDENT
        | CHAR
        | STRING
        | INTEGER
        | l_value DOT IDENT
        | l_value LEFT_BRACKET expression RIGHT_BRACKET
        ;



%%

int main()
{
  yyparse();
}

