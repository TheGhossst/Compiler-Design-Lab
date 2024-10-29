%{
    #include "y.tab.h"
%}

%%
a       { return A; }
b       { return B; }
c       { return C; }
"+"     { return PLUS; }
\n      { return 0; }
.       { return yytext[0]; }
%%