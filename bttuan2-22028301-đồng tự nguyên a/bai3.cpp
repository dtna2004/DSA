#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void append(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
};

int count_triplets(DoublyLinkedList& dllist) {
    int count = 0;
    Node* current = dllist.head;

    if (dllist.head == nullptr) {
        return 0;  
    }

    if (dllist.head->next == nullptr) {
        return 0;  
    }

    while (current->next != nullptr) {
        int prev_data = (current->prev != nullptr) ? current->prev->data : 0;
        int current_data = current->data;
        int next_data = (current->next != nullptr) ? current->next->data : 0;

        if (prev_data + current_data + next_data == 0) {
            count++;
        }

        current = current->next;
    }

    return count;
}

int main() {
    int n;
    cin >> n;

    DoublyLinkedList dllist;

    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        dllist.append(num);
    }

    int result = count_triplets(dllist);

    cout << result << endl;

    return 0;
}
