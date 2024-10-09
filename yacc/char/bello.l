%{
#include "bello.tab.h"
%}

%%
[a-zA-Z0-9]	{ return L; }
.			{ return O; }
\n		{ return 0; }
%%
