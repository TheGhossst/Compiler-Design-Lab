%{
    #include <stdio.h>
    int single_count = 0;
    int multi_count = 0;
    int total = 0;
%}

%%
"//" {single_count++;}
"/*" {multi_count++;}
\"[^\"]*\" {}
\n {}
. {}
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