#include <iostream>
#include<algorithm>
#include<queue>
#include <cstdlib>
#include <ctime>
using namespace std;

// Một Node trong cây
class Node {
    // Chứa thông tin của Node đó
    int data;
    // Con trỏ đến Node cha
    Node* fatherNode;

    // Con trỏ đến các Node con
    // Đây là một danh sách liên kết (con trỏ đến con đầu tiên)
    // Thứ tự ưu tiên từ nhỏ đến lớn (con nhỏ được duyệt trước)
    Node* firstChild;

public:
    Node(int val) : data(val),fatherNode(nullptr), firstChild(nullptr) {
        // ...
    }
    // Các hàm khởi tạo khác nếu cần thiết
    int getData() const {
        return data;
    }

    friend class Tree;
};

// Lớp Cây
class Tree {
    // Chứa một Node gốc
    Node* root;

public:
    Tree() : root(nullptr){
        // ...
    }
    Node* getRoot() const {
        return root;
    }
    // Các hàm khởi tạo khác nếu cần thiết

    // Hàm thêm một Node vào cây
    // Hàm trả về false nếu Node cha không tồn tại trên cây
    // hoặc Node father đã có con là data
    bool insert(int father, int data){
        Node* newNode = new Node(data);

        if(!root){
            root = newNode;
            return true;
        }
        queue<Node*> q;
        q.push(root);

        while(!q.empty()){
            Node* current = q.front();
            q.pop();

            if(current->data == father){
                Node* child = current->firstChild;
                while(child){
                    if(child->data == data){
                        delete newNode;
                        return false;
                    }
                    child = child->firstChild;
                }
                newNode->fatherNode = current;
                newNode->firstChild = current->firstChild;
                current->firstChild = newNode;

                return true;
            }
            Node* child = current->firstChild;
            while(child){
                q.push(child);
                child = child->firstChild;
            }
        }
        delete newNode;
        return false;
    }

    // Hàm xoá một Node trên cây
    // Nếu không phải Node lá xoá Node đó và toàn bộ các Node con của nó
    // Hàm trả về số lượng Node đã xoá
    // Nếu Node data không tồn tại trả về 0 (zero)
    int remove(int data) {
    int deletedCount = 0;
    vector<Node*> nodeToRemove;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->data == data) {
            nodeToRemove.push_back(current);
        }
        Node* child = current->firstChild;
        while (child) {
            q.push(child);
            child = child->firstChild;
        }
    }

    for (Node* node : nodeToRemove) {
        if (node->fatherNode) {
            Node* child = node->fatherNode->firstChild;
            Node* prev = nullptr;
            while (child) {
                if (child == node) {
                    if (prev) {
                        prev->firstChild = child->firstChild;
                    }
                    else {
                        node->fatherNode->firstChild = child->firstChild;
                    }
                    break;
                }
                prev = child;
                child = child->firstChild;
            }
        }
        else {
            root = node->firstChild;
        }
        delete node;
        deletedCount++;
    }

    return deletedCount;
}

    // Hàm in ra các Node theo thứ tự preorder

    void preorder(Node* node){
        if(node){
            cout << node->data << " ";

            Node* child = node->firstChild;
            while(child){
                preorder(child);
                child = child->firstChild;
            }
        }
    }
    void preorder(){
        preorder(root);
    }

    // Hàm in ra các Node theo thứ tự postorder
    void postorder(Node* node){
        if(node){
            Node* child = node->firstChild;
            while(child){
                postorder(child);
                child = child->firstChild;
            }
            cout << node->data << " ";
        }
    }
    void postorder(){
        postorder(root);
    }

    // Hàm kiểm tra cây nhị phân
    bool isBinaryTree(){
        return isBinaryTree(root);
    }
    bool isBinaryTree(Node* node){
        if(!node){
            return true;
        }
        Node* child = node->firstChild;
        int childCount = 0;
        while(child){
            childCount++;
            child = child->firstChild;
        }
        if(childCount > 2){
            return false;
        }
        child = node->firstChild;
        while(child){
            if(!isBinaryTree(child)){
                return false;
            }
            child = child->firstChild;
        }
        return true;
    }

    // Hàm kiểm tra cây tìm kiếm nhị phân
    bool isBinarySearchTree(){
        return isBinarySearchTree(root, INT_MIN, INT_MAX);
    }
    bool isBinarySearchTree(Node* node, int min, int max){
        if (!node) {
        return true;
    }

    int data = node->data;


    if (data <= min || data >= max) {
        return false;
    }


    Node* child = node->firstChild;
    while (child) {
        if (!isBinarySearchTree(child, min, data) || !isBinarySearchTree(child, data, max)) {
            return false;
        }
        child = child->firstChild;
    }

    return true;
    }

    // Hàm kiểm tra cây max-heap
    bool isMaxHeapTree(){
        return isMaxHeapTree(root);
    }
    bool isMaxHeapTree(Node* node) {
    if (!node) {
        return true;
    }

    Node* child = node->firstChild;
    while (child) {
        if (child->data > node->data) {
            return false;
        }
        child = child->firstChild;
    }

    child = node->firstChild;
    while (child) {
        if (!isMaxHeapTree(child)) {
            return false;
        }
        child = child->firstChild;
    }
    return true;
}

    // Hàm in ra các Node theo thứ tự inorder nếu là cây nhị phân
    void inorder(Node* node) {
    if (node) {

        inorder(node->firstChild);
        cout << node->data << " ";
        inorder(node->firstChild ? node->firstChild->firstChild : nullptr);
    }
}
    void inorder(){
        inorder(root);
    }

    // Hàm trả về độ cao của cây
    int height(){
        return height(root);
    }
    int height(Node* node) {
    if (!node) {
        return -1;
    }

    int leftHeight = height(node->firstChild);
    int rightHeight = height(node->firstChild ? node->firstChild->firstChild : nullptr);

    return 1 + max(leftHeight, rightHeight);
}

    // Hàm trả về độ sâu của một Node
    int depth(int data){
        return depth(root, data, 0);
    }
    int depth(Node* node, int data, int currentDepth) {
    if (!node) {
        return -1;
    }

    if (node->data == data) {
        return currentDepth;
    }


    int leftDepth = depth(node->firstChild, data, currentDepth + 1);
    int rightDepth = depth(node->firstChild ? node->firstChild->firstChild : nullptr, data, currentDepth + 1);


    if (leftDepth != -1) {
        return leftDepth;
    }
    return rightDepth;
}

    // Hàm đếm số lượng lá
    int numOfLeaves(){
        return numOfLeaves(root);
    }
    int numOfLeaves(Node* node) {
    if (!node) {
        return 0;
    }

    if (!node->firstChild) {
        return 1;
    }

    int leafCount = 0;

    Node* child = node->firstChild;
    while (child) {
        leafCount += numOfLeaves(child);
        child = child->firstChild;
    }

    return leafCount;
}

    // Hàm trả về Node có giá trị lớn nhất
    int findMax(){
    Node* maxNode = findMax(root);
    return maxNode ? maxNode->data : INT_MIN;
}
    Node* findMax(Node* node) {
    if (!node) {
        return nullptr;
    }

    Node* maxNode = node;
    Node* child = node->firstChild;

    while (child) {
        Node* maxChild = findMax(child);
        if (maxChild && maxChild->data > maxNode->data) {
            maxNode = maxChild;
        }
        child = child->firstChild;
    }

    return maxNode;
}

    // Hàm trả về Node có nhiều con nhất
    Node* findMaxChild(Node* node) {
    if (!node) {
        return nullptr;
    }

    Node* maxNode = node;
    int maxChildCount = 0;

    Node* child = node->firstChild;

    while (child) {
        int childCount = countChildren(child);
        if (childCount > maxChildCount) {
            maxChildCount = childCount;
            maxNode = child;
        }
        child = child->firstChild;
    }

    return maxNode;
}

int countChildren(Node* node) {
    int count = 0;
    Node* child = node->firstChild;

    while (child) {
        count++;
        child = child->firstChild;
    }

    return count;
}
int numOfNodes(){
    return numOfNodes(root);
}
int numOfNodes(Node* node) {
    if (!node) {
        return 0;
    }

    int count = 1;

    Node* child = node->firstChild;
    while (child) {
        count += numOfNodes(child);
        child = child->firstChild;
    }

    return count;
}

};

int main(int argc, char const *argv[]) {
    srand(static_cast<unsigned>(time(nullptr)));

    // Tạo ra một cây ngẫu nhiên có tối thiểu 30 Node
    Tree randomTree;
    for (int i = 0; i < 30; i++) {
        int father = rand() % 25;
        int data = rand() % 25;
        randomTree.insert(father, data);
    }
    // Test thử các hàm của lớp cây
    cout << "Preorder Traversal: ";
    randomTree.preorder();
    cout << endl;
    cout << "Postorder Traversal: ";
    randomTree.postorder();
    cout << endl;
    cout << "Inorder Traversal: ";
    randomTree.inorder();
    cout << endl;
    cout << "Height of the Tree: " << randomTree.height() << endl;
    cout << "Number of Leaves: " << randomTree.numOfLeaves() << endl;
    cout << "Number of Nodes: " << randomTree.numOfNodes() << endl;
    cout << endl;

    // Tạo ra một cây thoả mãn tính chất là Binary Search Tree và test lại
    Tree bstTree;
    int bstData[] = {50, 30, 70, 20, 40, 60, 80};
    for (int data : bstData) {
        bstTree.insert(-1, data);
    }
    cout << "Is BST: " << (bstTree.isBinarySearchTree() ? "Yes" : "No") << endl;
    cout << endl;

    //Tạo ra một cây thoả mãn tính chất là Max Heap Tree và test lại
    Tree maxHeapTree;
    int maxHeapData[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    for (int data : maxHeapData) {
        maxHeapTree.insert(-1, data);
    }
    cout << "Is Max Heap: " << (maxHeapTree.isMaxHeapTree() ? "Yes" : "No") << endl;
    // Kiểm tra hàm findMax
    int maxData = maxHeapTree.findMax();
    cout << "Max Value in Max Heap Tree: " << maxData << endl;

    // Kiểm tra hàm findMaxChild
    Node* maxChildNode = maxHeapTree.findMaxChild(maxHeapTree.getRoot());
    if (maxChildNode) {
        cout << "node has most child " << maxChildNode->getData() << endl;
    } else {
        cout << "invalid" << endl;
    }

    // Kiểm tra hàm depth
    int depthValue = randomTree.depth(90);
    if (depthValue != -1) {
        cout << "Depth of Node with Value 90: " << depthValue << endl;
    } else {
        cout << "Invalid" << endl;
    }

    // Kiểm tra hàm remove
    int removedCount = randomTree.remove(5);
    cout << "Removed " << removedCount << " nodes with Value 5." << endl;

    return 0;
}







