%{
    #include <stdio.h>
    int result = 0;
    void yyerror(const char *s);
    int yylex();
%}

%token NUMBER
%token INVALID

%%
S : E {$$ = $1; result = $$;} ;
E : E '+' T {$$ = $1 + $3;};
    | E '-' T {$$ = $1 - $3;}
    | T  {$$ = $1;} ;
T : T '*' F {$$ = $1 * $3;}
    | T '/' F {$$ = $1 / $3;}
    | F {$$ = $1;};
F : '(' E ')' {$$ = $2;}
    | NUMBER {$$ = $1;}
%%

void yyerror(const char *s){
    return;
}

int main(){
    printf("\nEnter the input: ");
    if (yyparse() == 0) printf("\nResult -> %d", result);
    else printf("\nFailure");
    return 1;
}