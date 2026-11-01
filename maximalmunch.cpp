#include <iostream> 
#include <string> 
#include <vector> 
#include <cctype> 
using namespace std; 
struct Token 
{ 
}; 
string type; 
string lexeme; 
vector<string> keywords = { 
"if", "else", "while", "for", 
"int", "float", "char", "return"}; 
bool isKeyword(const string &s) 
{ 
for (const string &k : keywords) 
{ 
} 
if (s == k) 
return true; 
return false; 
} 
bool isOperator(const string &s) 
{ 
} 
string operators[] = { 
"==", "!=", "<=", ">=", "++", "--", 
"+", "-", "*", "/", "=", "<", ">"}; 
for (string op : operators) 
{ 
} 
if (s == op) 
return true; 
return false; 
int main() 
{ 
string input; 
cout << "Enter input: "; 
getline(cin, input); 
vector<Token> tokens; 
 
  int i = 0; 
 
  while (i < input.length()) 
  { 
 
    if (isspace(input[i])) 
    { 
      i++; 
      continue; 
    } 
 
    if (isalpha(input[i]) || input[i] == '_') 
    { 
      int start = i; 
 
      while (i < input.length() && 
             (isalnum(input[i]) || input[i] == '_')) 
      { 
        i++; 
      } 
 
      string lexeme = input.substr(start, i - start); 
 
      if (isKeyword(lexeme)) 
        tokens.push_back({"Keyword", lexeme}); 
      else 
        tokens.push_back({"Identifier", lexeme}); 
    } 
 
    else if (isdigit(input[i])) 
    { 
      int start = i; 
 
      while (i < input.length() && isdigit(input[i])) 
      { 
        i++; 
      } 
 
      string lexeme = input.substr(start, i - start); 
 
      tokens.push_back({"Number", lexeme}); 
    } 
 
    else 
    { 
      string bestMatch = ""; 
 
      if (i + 1 < input.length()) 
      { 
        string twoChar = input.substr(i, 2); 
 
        if (isOperator(twoChar)) 
        { 
          bestMatch = twoChar; 
        } 
      } 
 
      if (bestMatch.empty()) 
      { 
        string oneChar(1, input[i]); 
 
        if (isOperator(oneChar)) 
        { 
          bestMatch = oneChar; 
        } 
      } 
 
      if (!bestMatch.empty()) 
      { 
        tokens.push_back({"Operator", bestMatch}); 
        i += bestMatch.length(); 
      } 
 
      else if (input[i] == ';' || input[i] == ',' || 
               input[i] == '(' || input[i] == ')' || 
               input[i] == '{' || input[i] == '}') 
      { 
 
        tokens.push_back({"Symbol", 
                          string(1, input[i])}); 
 
        i++; 
      } 
 
      else 
      { 
        tokens.push_back({"Unknown", 
                          string(1, input[i])}); 
 
        i++; 
      } 
    } 
  } 
 
  cout << "\nTOKEN TYPE\t\tLEXEME\n"; 
 
  for (const Token &token : tokens) 
  { 
    cout << token.type << "\t\t" << token.lexeme << endl; 
  } 
 
  return 0; 
}
