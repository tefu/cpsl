%{
#include <string>
#include "Expression.hpp"
#include "ProgramNode.hpp"
#include "LValue.hpp"
#include "Statement.hpp"
#include "parser.hpp"
#include <iostream>

void print_error(std::string error)
{
  std::cout << "Error: I don't know what " << error << " is. ";
  std::cout << "Line: " << yylineno << std::endl;
}

%}

%option noyywrap
%option yylineno

%%

  /* Keywords
  ------------------------------------------------------------------ */
array|ARRAY { return ARRAY; }
begin|BEGIN { return BEGIN_KW; }
chr|CHR { return CHR; }
const|CONST { return CONST; }
do|DO { return DO; }
downto|DOWNTO { return DOWNTO; }
else|ELSE { return ELSE; }
elseif|ELSEIF { return ELSEIF; }
end|END { return END; }
for|FOR { return FOR; }
forward|FORWARD { return FORWARD; }
function|FUNCTION { return FUNCTION; }
if|IF { return IF; }
of|OF { return OF; }
ord|ORD { return ORD; }
pred|PRED { return PRED; }
procedure|PROCEDURE { return PROCEDURE; }
read|READ { return READ; }
record|RECORD { return RECORD; }
ref|REF { return REF; }
repeat|REPEAT { return REPEAT; }
return|RETURN { return RETURN; }
stop|STOP { return STOP; }
succ|SUCC { return SUCC; }
then|THEN { return THEN; }
to|TO { return TO; }
type|TYPE { return TYPE; }
until|UNTIL { return UNTIL; }
var|VAR { return VAR; }
while|WHILE { return WHILE; }
write|WRITE { return WRITE; }

  /* Identifiers
  ------------------------------------------------------------------ */
[a-zA-Z][a-zA-Z0-9_]* { yylval.string_constant = new std::string(yytext);
                        return IDENT; }

  /* Operators
  ------------------------------------------------------------------ */
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIVIDE; }
"&" { return AND; }
"|" { return OR; }
"~" { return NEGATION; }
"=" { return EQUALITY; }
"<>" { return INEQUALITY; }
"<" { return LESS_THAN; }
"<=" { return LESS_THAN_OR_EQUAL; }
">" { return GREATER_THAN; }
">=" { return GREATER_THAN_OR_EQUAL; }
"." { return DOT; }
"," { return COMMA; }
":" { return COLON; }
";" { return SEMICOLON; }
"(" { return LEFT_PAREN; }
")" { return RIGHT_PAREN; }
"[" { return LEFT_BRACKET; }
"]" { return RIGHT_BRACKET; }
":=" { return ASSIGNMENT; }
"%" { return MODULUS; }


  /* Constants
  ------------------------------------------------------------------ */
0(0|[1-7][0-7]*) {
                    yylval.integer = std::stoi(std::string(yytext), 0, 8);
                    return INTEGER;
                 }
0x(0|[1-9a-fA-F][0-9a-fA-F]*) {
                    yylval.integer = std::stoi(std::string(yytext), 0, 16);
                    return INTEGER;
                 }
(0|[1-9][0-9]*)  {
                    yylval.integer = std::stoi(std::string(yytext));
                    return INTEGER;
                 }
'\\?[^\n]'       {
                    yylval.string_constant = new std::string(yytext);
                    return CHAR;
                 }

\"[^\"\n]*\"     {
                    yylval.string_constant = new std::string(yytext);
                    return STRING;
                 }

  /* Other
  ------------------------------------------------------------------ */
\$.*$ { }

[\t\n ]+

.    { print_error(yytext); }


%%
