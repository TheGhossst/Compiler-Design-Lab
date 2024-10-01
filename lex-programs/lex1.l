%{
	#include <stdio.h>
	int lines = 0;
	int words = 0;
	int total = 0;
%}
%%
[ \n\t]+ {
	words++;
	if(yytext[0]=='\n')
	lines++;
}
[a-zA-Z0-9] {
	   total++;
	   }
%%

int main(){
	FILE *infile = fopen("input.txt", "r");
	FILE *outfile = fopen("output.txt", "w");
	yyin = infile;
	yylex();
	fprintf(outfile,"Words : %d\n", words);
	fprintf(outfile,"Lines : %d\n", lines);
	fprintf(outfile,"Total : %d\n", total+1);
	fclose(infile);
	fclose(outfile);
	return 0;
}

/*
flex lex1.l
gcc lex.yy.c -o lexer -lfl
./lexer
*/