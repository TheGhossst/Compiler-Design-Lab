%{
    #include <stdio.h>
    int postitive_int = 0;
    int negetive_int = 0;
    int positive_fraction = 0;
    int negetive_fraction = 0;
%}

%%
[0-9]+ { postitive_int++; printf("Positive int %s\n", yytext);}
-[0-9]+ {negetive_int++; printf("Negetive int %s\n", yytext);}
[0-9]+\.[0-9]+ {positive_fraction++; printf("Positive fravtion %s\n", yytext);}
-[0-9]+\.[0-9]+ { negetive_fraction++; printf("Negetive fraction %s\n", yytext);}
\n {}
. {}

%%

int main(){
    yylex();

    printf("\nResults:\n");
    printf("Positive Integers: %d\n", postitive_int);
    printf("Negative Integers: %d\n", negetive_int);
    printf("Positive Fractions: %d\n", positive_fraction);
    printf("Negative Fractions: %d\n", negetive_fraction);

    return 0;
}