%{
#include "parser.hpp"
#include <iostream>

void print_term(std::string term, std::string value)
{
  std::cout << "I found:  " << term << " (" << value << ")  ";
  std::cout << "at line: " << yylineno << std::endl;
}
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
array|ARRAY { print_term("array", yytext); }
begin|BEGIN { print_term("begin", yytext); }
chr|CHR { print_term("chr",yytext); }
const|CONST { print_term("const",yytext); }
do|DO { print_term("do",yytext); }
downto|DOWNTO { print_term("downto",yytext); }
else|ELSE { print_term("else",yytext); }
elseif|ELSEIF { print_term("elseif",yytext); }
end|END { print_term("end",yytext); }
for|FOR { print_term("for",yytext); }
forward|FORWARD { print_term("forward",yytext); }
function|FUNCTION { print_term("function",yytext); }
if|IF { print_term("if",yytext); }
of|OF { print_term("of",yytext); }
ord|ORD { print_term("ord",yytext); }
pred|PRED { print_term("pred",yytext); }
procedure|PROCEDURE { print_term("procedure",yytext); }
read|READ { print_term("read",yytext); }
record|RECORD { print_term("record",yytext); }
ref|REF { print_term("ref",yytext); }
repeat|REPEAT { print_term("repeat",yytext); }
return|RETURN { print_term("return",yytext); }
stop|STOP { print_term("stop",yytext); }
succ|SUCC { print_term("succ",yytext); }
then|THEN { print_term("then",yytext); }
to|TO { print_term("to",yytext); }
type|TYPE { print_term("type",yytext); }
until|UNTIL { print_term("until",yytext); }
var|VAR { print_term("var",yytext); }
while|WHILE { print_term("while",yytext); }
write|WRITE { print_term("write",yytext); }

  /* Identifiers
  ------------------------------------------------------------------ */
[a-zA-Z][a-zA-Z0-9_]* { print_term("Identifier", yytext); }

  /* Operators
  ------------------------------------------------------------------ */
"+" { print_term("Plus Operator", yytext); }
"-" { print_term("Minus Operator", yytext); }
"*" { print_term("Multiplication Operator", yytext); }
"/" { print_term("Division Operator", yytext); }
"&" { print_term("And Operator", yytext); }
"|" { print_term("Or Operator", yytext); }
"~" { print_term("Negation Operator", yytext); }
"=" { print_term("Equality Operator", yytext); }
"<>" { print_term("Inequality Operator", yytext); }
"<" { print_term("Less Than Operator", yytext); }
"<=" { print_term("Less Than or Equal to Operator", yytext); }
">" { print_term("Greater Than Operator", yytext); }
">=" { print_term("Greater Than or Equal to Operator", yytext); }
"." { print_term("End Program Delimiter", yytext); }
"," { print_term("Comma Delimiter", yytext); }
":" { print_term("Colon Delimiter", yytext); }
";" { print_term("Semicolon Delimiter", yytext); }
"(" { print_term("Left Parenthesis", yytext); }
")" { print_term("Right Parenthesis", yytext); }
"[" { print_term("Left Bracket", yytext); }
"]" { print_term("Right Bracket", yytext); }
":=" { print_term("Assignment Operator", yytext); }
"%" { print_term("Modulus Operator", yytext); }


  /* Constants
  ------------------------------------------------------------------ */
0(0|[1-7][0-7]*) { print_term("Octal Integer Constant", yytext); }
0x(0|[1-9a-fA-F][0-9a-fA-F]*) { print_term("Hex Integer Constant", yytext); }
(0|[1-9][0-9]*) { print_term("Integer Constant", yytext); }
'\\?[^\n]' { print_term("Character Constant", yytext); }

\"[^\"\n]*\" { print_term("String Constant", yytext); }

  /* Other
  ------------------------------------------------------------------ */
\$.*$ { print_term("Comment", yytext); }

[\t\n ]+

.    { print_error(yytext); }


%%

int main(void)
{
    yylex();
}
