%{
#include "q1.tab.h"
#include <cstdlib>
#include <cstring>
%}

%%

[ \t]+                  ;

\n                      ;

[0-9]+                  {
                            yylval.num = atoi(yytext);
                            return NUMBER;
                        }

[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.str = strdup(yytext);
                            return ID;
                        }

"="                     { return '='; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"("                     { return '('; }
")"                     { return ')'; }
";"                     { return ';'; }

.                       { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}
