#include <iostream>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;

    stack<int> myStack;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if (operation == "push") {
            int x;
            cin >> x;
            myStack.push(x);
        }
        else if (operation == "pop") {
            if (!myStack.empty()) {
                myStack.pop();
            }
        }
    }

    // Print the resulting stack
    stack<int> reversedStack;
    while (!myStack.empty()) {
        reversedStack.push(myStack.top());
        myStack.pop();
    }

    while (!reversedStack.empty()) {
        cout << reversedStack.top() << " ";
        reversedStack.pop();
    }

    return 0;
}

