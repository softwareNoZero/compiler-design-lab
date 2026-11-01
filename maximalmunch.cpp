#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Structure to store token information
struct Token
{
    string type;
    string lexeme;
};

// List of keywords
vector<string> keywords = {
    "if", "else", "while", "for",
    "int", "float", "char", "return"
};

// Function to check keywords
bool isKeyword(const string &s)
{
    for (const string &k : keywords)
    {
        if (s == k)
            return true;
    }

    return false;
}

// List of operators in descending order of length
string operators[] = {
    "==", "!=", "<=", ">=", "++", "--",
    "+=", "-=", "*=", "/=", "&&", "||",
    "+", "-", "*", "/", "=", "<", ">"
};

// Function to check operators
bool isOperator(const string &s)
{
    for (string op : operators)
    {
        if (s == op)
            return true;
    }

    return false;
}

int main()
{
    string input;

    cout << "Enter input: ";
    getline(cin, input);

    vector<Token> tokens;

    int i = 0;

    while (i < (int)input.length())
    {
        // Ignore whitespace
        if (isspace(static_cast<unsigned char>(input[i])))
        {
            i++;
            continue;
        }

        // Identify keywords and identifiers
        if (isalpha(static_cast<unsigned char>(input[i])) ||
            input[i] == '_')
        {
            int start = i;

            while (i < (int)input.length() &&
                   (isalnum(static_cast<unsigned char>(input[i])) ||
                    input[i] == '_'))
            {
                i++;
            }

            string lexeme = input.substr(start, i - start);

            if (isKeyword(lexeme))
                tokens.push_back({"Keyword", lexeme});
            else
                tokens.push_back({"Identifier", lexeme});
        }

        // Identify numbers
        else if (isdigit(static_cast<unsigned char>(input[i])))
        {
            int start = i;

            while (i < (int)input.length() &&
                   isdigit(static_cast<unsigned char>(input[i])))
            {
                i++;
            }

            string lexeme = input.substr(start, i - start);

            tokens.push_back({"Number", lexeme});
        }

        // Apply Maximal Munch rule to operators
        else
        {
            string bestMatch = "";

            // Try matching a two-character operator first
            if (i + 1 < (int)input.length())
            {
                string twoChar = input.substr(i, 2);

                if (isOperator(twoChar))
                {
                    bestMatch = twoChar;
                }
            }

            // If no two-character operator matches, try one character
            if (bestMatch.empty())
            {
                string oneChar(1, input[i]);

                if (isOperator(oneChar))
                {
                    bestMatch = oneChar;
                }
            }

            // Store the longest matching operator
            if (!bestMatch.empty())
            {
                tokens.push_back({"Operator", bestMatch});
                i += bestMatch.length();
            }

            // Identify symbols and delimiters
            else if (input[i] == ';' || input[i] == ',' ||
                     input[i] == '(' || input[i] == ')' ||
                     input[i] == '{' || input[i] == '}' ||
                     input[i] == '[' || input[i] == ']')
            {
                tokens.push_back({"Symbol", string(1, input[i])});
                i++;
            }

            // Identify unrecognized characters
            else
            {
                tokens.push_back({"Unknown", string(1, input[i])});
                i++;
            }
        }
    }

    // Display tokens in tabular form
    cout << "\n";
    cout << "TOKEN TYPE\t\tLEXEME\n";
    cout << "-----------------------------------\n";

    for (const Token &token : tokens)
    {
        cout << token.type << "\t\t\t"
             << token.lexeme << endl;
    }

    return 0;
}
