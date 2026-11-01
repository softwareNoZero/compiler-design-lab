#include <iostream> 
#include <string> 
#include <cctype> 
using namespace std; 
struct Node 
{ 
string value; 
Node *left; 
Node *right; 
Node(string val) 
{ 
value = val; 
left = nullptr; 
right = nullptr; 
} 
Node(string val, Node *l, Node *r) 
{ 
} 
}; 
value = val; 
left = l; 
right = r; 
string input; 
int pos = 0; 
Node *E(); 
Node *EPrime(Node *left); 
Node *T(); 
Node *TPrime(Node *left); 
Node *F(); 
void skipSpaces() 
{ 
} 
while (pos < input.length() && isspace(input[pos])) 
{ 
} 
pos++; 
bool match(char ch) 
{ 
} 
skipSpaces(); 
if (pos < input.length() && input[pos] == ch) 
{ 
} 
pos++; 
return true; 
return false; 
Node *E() 
{ 
} 
Node *left = T(); 
return EPrime(left); 
Node *EPrime(Node *left) 
{ 
skipSpaces(); 
if (match('+')) 
{ 
Node *right = T(); 
Node *newNode = new Node("+", left, right); 
return EPrime(newNode); 
} 
if (match('-')) 
{ 
} 
Node *right = T(); 
Node *newNode = new Node("-", left, right); 
return EPrime(newNode); 
return left; 
} 
Node *T() 
{ 
} 
Node *left = F(); 
return TPrime(left); 
Node *TPrime(Node *left) 
{ 
 
  skipSpaces(); 
 
  if (match('*')) 
  { 
    Node *right = F(); 
 
    Node *newNode = new Node("*", left, right); 
 
    return TPrime(newNode); 
  } 
 
  if (match('/')) 
  { 
    Node *right = F(); 
 
    Node *newNode = new Node("/", left, right); 
 
    return TPrime(newNode); 
  } 
 
  return left; 
} 
 
Node *F() 
{ 
 
  skipSpaces(); 
 
  if (match('(')) 
  { 
 
    Node *node = E(); 
 
    if (!match(')')) 
    { 
      cout << "Error: Missing ')' \n"; 
      exit(1); 
    } 
 
    return node; 
  } 
 
  if (input.substr(pos, 2) == "id") 
  { 
    pos += 2; 
    return new Node("id"); 
  } 
 
  if (input.substr(pos, 3) == "num") 
  { 
pos += 3; 
return new Node("num"); 
} 
cout << "Syntax Error at position " << pos << endl; 
exit(1); 
} 
double evaluate(Node *root) 
{ 
if (root == nullptr) 
return 0; 
// id = 10 
if (root->value == "id") 
return 10; 
// num = 5 
if (root->value == "num") 
return 5; 
double left = evaluate(root->left); 
double right = evaluate(root->right); 
if (root->value == "+") 
    return left + right; 
 
  if (root->value == "-") 
    return left - right; 
 
  if (root->value == "*") 
    return left * right; 
 
  if (root->value == "/") 
  { 
 
    if (right == 0) 
    { 
      cout << "Error: Division by zero!" << endl; 
      exit(1); 
    } 
 
    return left / right; 
  } 
 
  return 0; 
} 
 
void printAST(Node *root, int level = 0) 
{ 
 
if (root == nullptr) 
return; 
for (int i = 0; i < level; i++) 
cout << "    
"; 
cout << root->value << endl; 
printAST(root->left, level + 1); 
printAST(root->right, level + 1); 
} 
void deleteAST(Node *root) 
{ 
} 
if (root == nullptr) 
return; 
deleteAST(root->left); 
deleteAST(root->right); 
delete root; 
int main() 
{ 
 
  cout << "Enter expression: "; 
  getline(cin, input); 
 
  Node *root = E(); 
 
  skipSpaces(); 
 
  if (pos != input.length()) 
  { 
    cout << "Syntax Error: Invalid expression!" << endl; 
    deleteAST(root); 
    return 1; 
  } 
 
  cout << "\nParsing Successful!" << endl; 
 
  cout << "\nAbstract Syntax Tree (AST):" << endl; 
  printAST(root); 
 
  cout << "\nEvaluation Result: " 
       << evaluate(root) << endl; 
 
  deleteAST(root); 
 
  return 0; 
}
