#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
    string input;

    cout << "Enter input string: ";
    cin >> input;

    input += "$";

    int action[5][3] = {0};

    action[0][0] = 3;
    action[1][2] = 999;
    action[2][1] = 4;
    action[2][2] = -1;

    action[3][0] = -3;
    action[3][1] = -3;
    action[3][2] = -3;

    action[4][0] = -2;
    action[4][1] = -2;
    action[4][2] = -2;

    stack<int> stateStack;
    stack<char> symbolStack;

    stateStack.push(0);

    int ip = 0;

    cout << "\nParsing Steps:\n";

    while (true)
    {
        int state = stateStack.top();
        char current = input[ip];

        int column;

        if (current == 'a')
            column = 0;
        else if (current == 'b')
            column = 1;
        else
            column = 2;

        int act = action[state][column];

        if (act == 999)
        {
            cout << "Input: " << input.substr(ip) << endl;
            cout << "Action: ACCEPT\n";
            cout << "\nString Accepted!\n";
            break;
        }

        else if (act > 0)
        {
            int nextState = act;

            cout << "State " << state
                 << " : Shift " << current
                 << " and go to state "
                 << nextState << endl;

            symbolStack.push(current);
            stateStack.push(nextState);

            ip++;
        }

        else if (act < 0)
        {
            int production = -act;

            if (production == 1)
            {
                cout << "State " << state
                     << " : Reduce S -> A" << endl;

                symbolStack.pop();
                stateStack.pop();

                symbolStack.push('S');

                int previousState = stateStack.top();

                if (previousState == 0)
                {
                    stateStack.push(1);
                }
                else
                {
                    cout << "Error!" << endl;
                    cout << "String Rejected!\n";
                    break;
                }
            }

            else if (production == 2)
            {
                cout << "State " << state
                     << " : Reduce A -> Ab" << endl;

                symbolStack.pop();
                stateStack.pop();

                symbolStack.pop();
                stateStack.pop();

                symbolStack.push('A');

                int previousState = stateStack.top();

                if (previousState == 0)
                {
                    stateStack.push(2);
                }
                else
                {
                    cout << "Error!" << endl;
                    cout << "String Rejected!\n";
                    break;
                }
            }

            else if (production == 3)
            {
                cout << "State " << state
                     << " : Reduce A -> a" << endl;

                symbolStack.pop();
                stateStack.pop();

                symbolStack.push('A');

                int previousState = stateStack.top();

                if (previousState == 0)
                {
                    stateStack.push(2);
                }
                else
                {
                    cout << "Error!" << endl;
                    cout << "String Rejected!\n";
                    break;
                }
            }
        }

        else
        {
            cout << "State " << state
                 << " : Error with input symbol "
                 << current << endl;

            cout << "\nString Rejected!\n";
            break;
        }
    }

    return 0;
}
