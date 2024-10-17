%{
    #include <stdio.h>
    #include "y.tab.h"
%}

%% 
[a-zA-Z0-9] {printf("%s", yytext); return ALNUM;}
"+"  return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"(" return '(';
")" return ')';
. return  INVALID;
\n return 0;
%%