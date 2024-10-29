/*Write a YACC program to recognize strings of the form a^nb^n+b^mc^m, n,m>=0.*/
%{
    #include <stdio.h>
    int yylex();
    void yyerror(const char *s);
%}

%token A B C PLUS

%%
S   : E PLUS F       { printf("Valid string!\n"); }
    ;

E   :
    | A E B          
    ;

F   :   
    | B F C          
    ;

%%

void yyerror(const char *s) {
    printf("Syntax error\n");
}

int main() {
    printf("Enter string (Example: ab+bc): ");

    if (yyparse() == 0)  printf("\nSuccess\n");
    else printf("\nFailure\n");
    return 0;
}