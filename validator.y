%{
#include <iostream>

using namespace std;

int yylex();
void yyerror(const char *s);
%}

%union
{
    int num;
}

%token <num> NUMBER

%left '+' '-'
%left '*' '/'

%type <num> expression term factor

%%

input:
    expression '\n'
    {
        cout << "\nValid expression!" << endl;
        cout << "Result = " << $1 << endl;
        cout << "Parentheses are balanced and correctly nested."
             << endl;
    }
    ;

expression:
    expression '+' term
    {
        $$ = $1 + $3;
    }
    | expression '-' term
    {
        $$ = $1 - $3;
    }
    | term
    {
        $$ = $1;
    }
    ;

term:
    term '*' factor
    {
        $$ = $1 * $3;
    }
    | term '/' factor
    {
        if ($3 == 0)
        {
            yyerror("Division by zero");
            $$ = 0;
        }
        else
        {
            $$ = $1 / $3;
        }
    }
    | factor
    {
        $$ = $1;
    }
    ;

factor:
    NUMBER
    {
        $$ = $1;
    }
    | '(' expression ')'
    {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s)
{
    cout << "\nInvalid expression!" << endl;
    cout << "Error: " << s << endl;
}

int main()
{
    cout << "Enter mathematical expression: ";

    yyparse();

    return 0;
}
