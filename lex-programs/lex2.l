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
	fprintf(outfile,"Vowels : %d\n", vowels);
	fprintf(outfile,"Consonents : %d\n", consonents);
	fclose(infile);
	fclose(outfile);
	return 0;
}
