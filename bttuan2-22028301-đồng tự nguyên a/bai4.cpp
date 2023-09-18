#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    queue<int> myQueue;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if (operation == "enqueue") {
            int x;
            cin >> x;
            myQueue.push(x);
        }
        else if (operation == "dequeue") {
            if (!myQueue.empty()) {
                myQueue.pop();
            }
        }
    }
    while (!myQueue.empty()) {
        cout << myQueue.front() << " ";
        myQueue.pop();
    }

    return 0;
}

