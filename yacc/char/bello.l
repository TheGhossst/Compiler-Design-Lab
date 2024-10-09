%{
#include "bello.tab.h"
%}

%%
[a-zA-Z0-9]	{ return L; }
.			{ return 0; }
\n		{ return 0; }
%%
