%{
	#include <stdio.h>
	int vowels = 0;
    int consonents = 0;
%}
%%
[aeiouAEIOU] {
    vowels++;
}
[a-zA-Z] {
    consonents++;
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
