%{
#include <stdio.h>
%}

%%
[a-z]   printf("%c", yytext[0] - 32);
\n return 0;
.  printf("%c", yytext[0]);

%%

int main() {
    printf("\nEnter an input: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
