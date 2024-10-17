%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char substring[30];

void capitalize(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}
%}

%%
[a-zA-Z]+ {
    if (strcmp(yytext, substring) == 0) {
        capitalize(yytext);
        printf("%s", yytext);
    }
    else{
        printf("%s", yytext);
    }
}

%%

int main(){
    FILE *infile = fopen("input.txt", "r");
    yyin = infile;

    printf("\nEnter a substring to capitalize: ");
    fgets(substring, sizeof(substring), stdin);
    substring[strcspn(substring, "\n")] = '\0';

    yylex();
    fclose(infile);
    return 1;
}