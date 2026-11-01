%{
#include "q2.tab.h"
#include <cstdlib>
%}

%%

[ \t]+                  ;

\n                      return '\n';

[0-9]+                  {
                            yylval.num = atoi(yytext);
                            return NUMBER;
                        }

"+"                     return '+';
"-"                     return '-';
"*"                     return '*';
"/"                     return '/';

"("                     return '(';
")"                     return ')';

.                       return yytext[0];

%%

int yywrap()
{
    return 1;
}
