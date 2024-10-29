%{
    #include "y.tab.h"
%}

%%
"if"            { return IF; }
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
"EOF"           {return 0;}
[ \t\n]+        { }
.               { }

%%

