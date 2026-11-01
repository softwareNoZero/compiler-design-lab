#include <iostream> 
#include <string> 
using namespace std; 
string generateString(int n) 
{ 
string result = ""; 
for (int i = 0; i < n; i++) 
{ 
} 
result += "aab"; 
result += "aa"; 
return result; 
} 
int main() 
{ 
int n; 
cout << "Enter value of n (n > 0): "; 
cin >> n; 
if (n <= 0) 
{ 
} 
cout << "Invalid value of n. n must be greater than 0."; 
return 0; 
string result = generateString(n); 
cout << "\nCFG:\n"; 
cout << "S -> aabS | aabaa\n"; 
cout << "\nLanguage Pattern:\n"; 
cout << "L = { (aab)^n aa | n > 0 }\n"; 
cout << "\nGenerated string for n = " << n << ":\n"; 
cout << result << endl; 
return 0; 
}
