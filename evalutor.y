%{
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

int yylex();
void yyerror(const char *s);

map<string, int> variables;
%}

%union
{
    int num;
    char *str;
}

%token <num> NUMBER
%token <str> ID

%left '+' '-'
%left '*' '/'

%type <num> expression term factor

%%

program:
    statements
    ;

statements:
    statements statement
    | statement
    ;

statement:
    ID '=' expression ';'
    {
        variables[$1] = $3;

        cout << $1 << " = " << $3 << endl;

        free($1);
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
    | ID
    {
        if (variables.find($1) == variables.end())
        {
            cout << "Error: Undefined variable "
                 << $1 << endl;

            $$ = 0;
        }
        else
        {
            $$ = variables[$1];
        }

        free($1);
    }
    | '(' expression ')'
    {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s)
{
    cout << "Syntax Error: " << s << endl;
}

int main()
{
    cout << "Enter configuration statements:\n";
    cout << "Example:\n";
    cout << "x = 10;\n";
    cout << "y = 20;\n";
    cout << "z = x + y * 2;\n\n";

    yyparse();

    return 0;
}
