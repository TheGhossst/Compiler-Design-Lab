%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token O
%token L

%%
Input	: O l
		| L l
		;

l	: l L
			| L
					;
%%

void yyerror(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
}

int main(void)
{
	printf("Input: ");
	
	if (yyparse() == 0) printf("Recognized successfully!\n");
	else printf("Invalid input!\n");
	
	return 0;
}
/*Output
Input: #123
Recognized successfully!

Input: 1#123
Error: syntax error
Invalid input!
*/