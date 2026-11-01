#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <stdexcept>
using namespace std;

struct Token
{
  string type;
  string value;
};

struct TAC
{
  string result;
  string arg1;
  string op;
  string arg2;
};

vector<Token> tokens;
vector<TAC> code;
int pos = 0;
int tempCount = 0;

void lexer(string input)
{
  tokens.clear();

  for (int i = 0; i < (int)input.size();)
  {
    if (isspace((unsigned char)input[i]))
    {
      i++;
    }
    else if (isalnum((unsigned char)input[i]) ||
             input[i] == '_')
    {
      string word;

      while (i < (int)input.size() &&
             (isalnum((unsigned char)input[i]) || input[i] == '_'))
      {
        word += input[i++];
      }
      tokens.push_back({isdigit((unsigned char)word[0]) ? "Number" : "Identifier", word});
    }

    else if (string("+-*/=()").find(input[i]) != string::npos)
    {
      string op(1, input[i++]);
      tokens.push_back({"Operator", op});
    }

    else
    {
      throw runtime_error("Invalid character in expression");
    }
  }

  tokens.push_back({"END", "$"});
}

Token currentToken()
{
  return tokens[pos];
}

bool match(string value)
{
  if (currentToken().value == value)
  {
    pos++;
    return true;
  }
  return false;
}

void expect(string value)
{
  if (!match(value))
  {
    throw runtime_error(
        "Expected '" + value + "'");
  }
}

string newTemp()
{
  return "t" + to_string(++tempCount);
}

void emit(string result, string arg1,
          string op, string arg2)
{
  code.push_back({result, arg1, op, arg2});
}

string factor()
{
  if (match("("))
  {
    string result = [&]()
    {
      return string("");
    }();
    (void)result;
    extern string expression();
    string value = expression();
    expect(")");
    return value;
  }

  Token t = currentToken();

  if (t.type == "Identifier" ||
      t.type == "Number")
  {
    pos++;
    return t.value;
  }

  throw runtime_error(
      "Expected identifier, number, or '('");
}

string term()
{
  string left = factor();

  while (currentToken().value == "*" || currentToken().value == "/")
  {
    string op = currentToken().value;
    pos++;
    string right = factor();
    string temp = newTemp();
    emit(temp, left, op, right);
    left = temp;
  }
  return left;
}
string expression()
{
  string left = term();

  while (currentToken().value == "+" || currentToken().value == "-")
  {
    string op = currentToken().value;
    pos++;
    string right = term();
    string temp = newTemp();
    emit(temp, left, op, right);
    left = temp;
  }
  return left;
}

void parse()
{
  pos = 0;
  code.clear();
  tempCount = 0;

  string lhs = "";
  if (currentToken().type == "Identifier" &&
      tokens.size() > 2 &&
      tokens[1].value == "=")
  {
    lhs = currentToken().value;
    pos += 2;
  }
  string result = expression();
  if (currentToken().type != "END")
  {
    throw runtime_error(
        "Unexpected token: " +
        currentToken().value);
  }
  if (lhs != "")
  {
    emit(lhs, result, "=", "");
  }
  else
  {
    emit("result", result, "=", "");
  }
}
void displayTAC()
{
  cout << "\nThree-Address Code:\n";
  for (const TAC &t : code)
  {
    if (t.op == "=" && t.arg2 == "")
    {
      cout << t.result << " = "
           << t.arg1 << "\n";
    }
    else
    {
      cout << t.result << " = "
           << t.arg1 << " " << t.op
           << " " << t.arg2 << "\n";
    }
  }
}
void displayQuadruples()
{
  cout << "\nQuadruple Representation:\n";
  cout << left << setw(12) << "Operator"
       << setw(12) << "Arg1" << setw(12) << "Arg2"
       << setw(12) << "Result" << "\n";
  for (const TAC &t : code)
  {
    cout << left << setw(12) << t.op
         << setw(12) << t.arg1 << setw(12) << t.arg2
         << setw(12) << t.result << "\n";
  }
}

void displayTriples()
{
  cout << "\nTriple Representation:\n";
  cout << left << setw(10) << "Index"
       << setw(12) << "Operator" << setw(12) << "Arg1"
       << setw(12) << "Arg2" << "\n";

  for (int i = 0; i < (int)code.size(); i++)
  {
    string a = code[i].arg1;
    string b = code[i].arg2;
    for (int j = 0; j < i; j++)
    {
      if (code[j].result == a &&
          a.length() > 1 && a[0] == 't')
      {
        a = "(" + to_string(j) + ")";
      }
      if (code[j].result == b &&
          b.length() > 1 && b[0] == 't')
      {
        b = "(" + to_string(j) + ")";
      }
    }
    cout << left << setw(10) << i
         << setw(12) << code[i].op << setw(12) << a
         << setw(12) << b << "\n";
  }
}

int main()
{
  string input;

  cout << "Enter an arithmetic expression "
          "or assignment statement:\n";
  getline(cin, input);

  try
  {
    lexer(input);

    cout << "\nTokens:\n";
    for (const Token &t : tokens)
    {
      if (t.type != "END")
      {
        cout << t.type << " : "
             << t.value << "\n";
      }
    }
    parse();
    cout << "\nParsing successful!\n";
    displayTAC();
    displayQuadruples();
    displayTriples();
  }
  catch (const exception &e)
  {
    cout << "\nError: " << e.what() << "\n";
  }
  return 0;
}
