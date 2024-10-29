%{
    #include <stdio.h>
    int yylex();
    void yyerror(const char *s);
%}

%token IF

%%
S: Statements {printf("Max depth = %d\n", $1);};
Statements : IF '(' ')' '{' Statements '}' Statements   { $$ = $5 >= $7 ? $5 + 1 : $7; }
      |                    { $$ = 0; }
      ;
%%

void yyerror(const char *s){
    fprintf(stderr, "%s", s);
}

int main(){
    yyparse();
    return 0;
}