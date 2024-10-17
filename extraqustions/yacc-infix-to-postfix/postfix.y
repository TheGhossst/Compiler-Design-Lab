%{
    #include <stdio.h>
    void yyerror(const char *s);
    int yylex();    
%}

%token ALNUM
%token INVALID

%%
E : E '+' T {printf("+");};
    | E '-' T {printf("-");}
    | T  {$$ = $1;} ;
T : T '*' F {printf("*");}
    | T '/' F {printf("/");}
    | F {$$ = $1;};
F : '(' E ')' {$$ = $2;}
    | ALNUM 
%%

void yyerror(const char *s){
    fprintf(stderr, "%s", s);
}

int main(){
    printf("\nEnter an infix expression : ");
    yyparse();
    return 1;
}