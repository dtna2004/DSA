#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    void insert(int p, int x) {
        Node* new_node = new Node(x);
        if (p == 0 || head == nullptr) {
            new_node->next = head;
            head = new_node;
        }
        else {
            Node* prev = nullptr;
            Node* curr = head;
            int pos = 0;

            while (pos < p && curr != nullptr) {
                prev = curr;
                curr = curr->next;
                pos++;
            }

            if (prev != nullptr) {
                prev->next = new_node;
                new_node->next = curr;
            }
        }
    }

    void remove(int p) {
        if (p == 0 || head == nullptr) {
            if (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        else {
            Node* prev = nullptr;
            Node* curr = head;
            int pos = 0;

            while (pos < p && curr != nullptr) {
                prev = curr;
                curr = curr->next;
                pos++;
            }

            if (curr != nullptr) {
                prev->next = curr->next;
                delete curr;
            }
        }
    }

    void display() {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;

    LinkedList linkedList;

    for (int i = 0; i < n; i++) {
        string operation;
        int p, x;
        cin >> operation;

        if (operation == "insert") {
            cin >> p >> x;
            linkedList.insert(p, x);
        }
        else if (operation == "delete") {
            cin >> p;
            linkedList.remove(p);
        }
    }

    linkedList.display();

    return 0;
}
