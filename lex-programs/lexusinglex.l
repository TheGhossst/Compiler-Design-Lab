%{
    #include <stdio.h>
    #include <string.h>

    struct token {
        char token_name[32];
        char token_type[32];
    };
    
    struct token Tokens[1024];
    int tokenCount = 0;
%}

KEYWORD if|int|printf|void|main
OPERATOR "+"|"-"|"*"|"/"|"<"|">"|"<="|">="|"=="

%%
[ \t] ;
\n    ;

{KEYWORD} {
    printf("\n<KEYWORD, %s>\n", yytext);
    strcpy(Tokens[tokenCount].token_name, yytext);
    strcpy(Tokens[tokenCount].token_type, "KEYWORD");
    tokenCount++;
}

[_a-zA-Z][a-zA-Z0-9]* {
    printf("<IDENTIFIER, %s>\n", yytext);
    strcpy(Tokens[tokenCount].token_name, yytext);
    strcpy(Tokens[tokenCount].token_type, "IDENTIFIER");
    tokenCount++;
}

[0-9]+ {
    printf("\n<DIGIT, %s>\n", yytext);
    strcpy(Tokens[tokenCount].token_name, yytext);
    strcpy(Tokens[tokenCount].token_type, "DIGIT");
    tokenCount++;
}

{OPERATOR} {
    printf("\n<OPERATOR, %s>\n", yytext);
    strcpy(Tokens[tokenCount].token_name, yytext);
    strcpy(Tokens[tokenCount].token_type, "OPERATOR");
    tokenCount++;
}

\"[^\"]*\" {
    printf("\n<STRING LITERAL, %s>\n", yytext);
    strcpy(Tokens[tokenCount].token_name, yytext);
    strcpy(Tokens[tokenCount].token_type, "STRING LITERAL");
    tokenCount++;
}

. {
    printf("\n<UNKNOWN, %s>\n", yytext);
}

%%

void printsymtab() {
    printf("\n%-20s %-20s\n", "TOKEN", "TYPE");
    printf("............................................................\n");

    for (int i = 0; i < tokenCount; i++) {
        printf("%-20s %-20s\n", Tokens[i].token_name, Tokens[i].token_type);
    }
}

int main() {
    yyin = fopen("code.c", "r");
    yylex();
    printsymtab();
    fclose(yyin);
    return 0;
}

int yywrap() {
    printf("\nSuccessful\n");
    return 1;
}
