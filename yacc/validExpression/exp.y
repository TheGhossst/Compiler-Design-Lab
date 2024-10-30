%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char *s);
    int yylex();
%}

%token NUMBER
%token INVALID
%%

Expr:
      Expr '+' Term   { printf("Add\n"); }
    | Expr '-' Term   { printf("Subtract\n"); }
    | Term
    ;

Term:
      Term '*' Factor { printf("Multiply\n"); }
    | Term '/' Factor { printf("Divide\n"); }
    | Factor
    ;

Factor:
      '(' Expr ')'
    | NUMBER          { printf("Number: %d\n", $1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    if (yyparse() == 0){
        printf("Valid Expression\n");
        printf("Parsing succeeded.\n");
    }
    else
        printf("Parsing failed.\n");
    return 0;
}
/*Output
(2+3)*(4*3)/2
Number: 2
Number: 3
Add
Number: 4
Number: 3
Multiply
Multiply
Number: 2
Divide
Valid Expression
Parsing succeeded.
*/