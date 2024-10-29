/*Write a LEX program to count the number of comment lines in a C Program*/
/*Also eliminate them and copy that program into a separate file*/
%{
    #include <stdio.h>
    int single_count = 0;
    int multi_count = 0;
    int total = 0;
%}

%%
"//".*\n {single_count++;}
"/*"[^*/]*"*/" { multi_count++; }
\"[^\"]*\" {}
\n {printf("\n");}
. {printf("%s", yytext);}
%%

int main(){
    FILE *fp = fopen("input.c", "r");
    yyin = fp;

    yylex();

    total = single_count + multi_count;

    printf("\nSingle line = %d", single_count);
    printf("\nMulti line = %d", multi_count);
    printf("\nTotal = %d", total);

    fclose(fp);
    return 0;
}