#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

string input;
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    cout << "String Rejected!" << endl;
    exit(0);
}

void E()
{
    cout << "E -> T E'" << endl;
    T();
    Eprime();
}

void Eprime()
{
    if (input[pos] == '+')
    {
        cout << "E' -> + T E'" << endl;
        pos++;
        T();
        Eprime();
    }
    else
    {
        cout << "E' -> epsilon" << endl;
    }
}

void T()
{
    cout << "T -> F T'" << endl;
    F();
    Tprime();
}

void Tprime()
{
    if (input[pos] == '*')
    {
        cout << "T' -> * F T'" << endl;
        pos++;
        F();
        Tprime();
    }
    else
    {
        cout << "T' -> epsilon" << endl;
    }
}

void F()
{
    if (input[pos] == '(')
    {
        cout << "F -> ( E )" << endl;
        pos++;
        E();

        if (input[pos] == ')')
        {
            pos++;
        }
        else
        {
            error();
        }
    }
    else if (input.substr(pos, 2) == "id")
    {
        cout << "F -> id" << endl;
        pos += 2;
    }
    else
    {
        error();
    }
}

int main()
{
    cout << "Enter input string: ";
    cin >> input;

    input += "$";

    cout << "\nParsing Steps:\n";

    E();

    if (input[pos] == '$')
    {
        cout << "\nString Accepted!" << endl;
    }
    else
    {
        cout << "\nString Rejected!" << endl;
    }

    return 0;
}
