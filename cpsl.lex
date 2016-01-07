%{
#include <iostream>
void print_term(std::string term) {
  std::cout << "I found " << term << "!" << std::endl;
}
%}

%option noyywrap

%%

  /* Keywords
  ------------------------------------------------------------------ */
array|ARRAY { print_term(yytext); }
begin|BEGIN { print_term(yytext); }
chr|CHR { print_term(yytext); }
const|CONST { print_term(yytext); }
do|DO { print_term(yytext); }
downto|DOWNTO { print_term(yytext); }
else|ELSE { print_term(yytext); }
elseif|ELSEIF { print_term(yytext); }
end|END { print_term(yytext); }
for|FOR { print_term(yytext); }
forward|FORWARD { print_term(yytext); }
function|FUNCTION { print_term(yytext); }
if|IF { print_term(yytext); }
of|OF { print_term(yytext); }
ord|ORD { print_term(yytext); }
pred|PRED { print_term(yytext); }
procedure|PROCEDURE { print_term(yytext); }
read|READ { print_term(yytext); }
record|RECORD { print_term(yytext); }
ref|REF { print_term(yytext); }
repeat|REPEAT { print_term(yytext); }
return|RETURN { print_term(yytext); }
stop|STOP { print_term(yytext); }
succ|SUCC { print_term(yytext); }
then|THEN { print_term(yytext); }
to|TO { print_term(yytext); }
type|TYPE { print_term(yytext); }
until|UNTIL { print_term(yytext); }
var|VAR { print_term(yytext); }
while|WHILE { print_term(yytext); }
write|WRITE { print_term(yytext); }


  /* Operators
  ------------------------------------------------------------------ */

"+" { print_term("Plus Operator"); }
"−" { print_term("Minus Operator"); }
"∗" { print_term("Multiplication Operator"); }
"/" { print_term("Division Operator"); }
"&" { print_term("Bitwise And"); }
"|" { print_term("Bitwise Or"); }
"˜" { print_term("Bitwise Negation"); }
"=" { print_term("Equality Operator"); }
"<>" { print_term("Inequality Operator"); }
"<" { print_term("Less Than Operator"); }
"<=" { print_term("Less Than or Equal to Operator"); }
">" { print_term("Greater Than Operator"); }
">=" { print_term("Greater Than or Equal to Operator"); }
"." { print_term("End Program Delimiter"); }
"," { print_term("Comma Delimiter"); }
":" { print_term("Colon Delimiter"); }
";" { print_term("Semicolon Delimiter"); }
"(" { print_term("Left Parenthesis"); }
")" { print_term("Right Parenthesis"); }
"[" { print_term("Left Bracket"); }
"]" { print_term("Right Bracket"); }
":=" { print_term("Assignment Operator"); }


  /* Constants
  ------------------------------------------------------------------ */

0[0-7]+|0x[0-9]+|[0-9]+ { print_term("Integer Constant"); }
'[a-zA-Z]' { print_term("Character Constant"); }

\"[^\"\n]*\" { print_term("String Constant"); }

  /* Other
  ------------------------------------------------------------------ */

\$.*$ { print_term("Comment"); }

.|\n    { ECHO; }

%
%%

int main(void)
{
    yylex();
}
