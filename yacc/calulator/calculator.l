%{
    #include "y.tab.h"
%}

%%
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
"+"  return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"(" return '(';
")" return ')';
. return  INVALID;
\n return 0;
%%