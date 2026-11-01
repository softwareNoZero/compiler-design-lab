#include <iostream> 
#include <stack> 
#include <string> 
using namespace std; 
 
int main() 
{ 
  string input; 
 
  cout << "Grammar:" << endl; 
  cout << "S -> aABe" << endl; 
  cout << "A -> bAc | d" << endl; 
  cout << "B -> f | epsilon" << endl 
       << endl; 
 
  cout << "Enter input string: "; 
  cin >> input; 
 
  input += "$"; 
 
  stack<char> st; 
  st.push('S'); 
 
  int i = 0; 
 
  cout << "\nParsing Steps:\n"; 
 
  while (!st.empty()) 
  { 
    char top = st.top(); 
    char current = input[i]; 
 
    if (top == current) 
    { 
      cout << "Match: " << current << endl; 
      st.pop(); 
      i++; 
    } 
 
    else if (top == 'S') 
    { 
      if (current == 'a') 
      { 
        st.pop(); 
 
        st.push('e'); 
        st.push('B'); 
        st.push('A'); 
        st.push('a'); 
 
        cout << "S -> aABe" << endl; 
      } 
      else 
      { 
        cout << "Error: No rule for S with " << current << endl; 
        cout << "String Rejected" << endl; 
        return 0; 
      } 
    } 
 
    else if (top == 'A') 
    { 
      if (current == 'b') 
      { 
        st.pop(); 
 
        st.push('c'); 
        st.push('A'); 
        st.push('b'); 
 
        cout << "A -> bAc" << endl; 
      } 
      else if (current == 'd') 
      { 
        st.pop(); 
 
        st.push('d'); 
 
        cout << "A -> d" << endl; 
      } 
      else 
      { 
        cout << "Error: No rule for A with " << current << endl; 
        cout << "String Rejected" << endl; 
        return 0; 
      } 
    } 
 
    else if (top == 'B') 
    { 
      if (current == 'f') 
      { 
        st.pop(); 
        st.push('f'); 
 
        cout << "B -> f" << endl; 
      } 
      else if (current == 'e') 
      { 
 
        st.pop(); 
 
        cout << "B -> epsilon" << endl; 
      } 
      else 
      { 
        cout << "Error: No rule for B with " << current << endl; 
        cout << "String Rejected" << endl; 
        return 0; 
      } 
    } 
 
    else 
    { 
      cout << "Error!" << endl; 
      cout << "String Rejected" << endl; 
      return 0; 
    } 
  } 
 
  if (input[i] == '$') 
  { 
    cout << "String Accepted!" << endl; 
  } 
else 
{
 cout << "String Rejected!" << endl; 
} 
return 0; 
}
