#include <iostream>
#include <stack>
#include "QueueLL.h"
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T>* right;
    Node<T>* left;

    Node(T data) {
        this->data = data;
        this->right = this->left = NULL;
    }
};

template <class T>
class BinaryTree {
    Node<T>* root;
    T getValidInput();
    void freeTree();
    void freeNode(Node<T>*);
    void preorder(Node<T>*);
    void inorder(Node<T>*);
    void postorder(Node<T>*);
public:

    BinaryTree() {
        this->root = NULL;
    }

    ~BinaryTree() {
        this->freeTree();
    }

    bool isEmpty();
    void createTree();

    void preorder();
    void preorderIt();

    void inorder();
    void inorderIt();

    void postorder();
    void postorderIt();

    void levelOrder();
    void generateFromTraversals(T preorder[], T inorder[]);
};

int main() {

    // int arr[] = { 1,2,3,4,5,6 };
    BinaryTree<int> tree;
    tree.createTree();
    // tree.preorderIt();
    // tree.inorderIt();
    // tree.postorderIt();

    // tree.preorder();
    // tree.inorder();
    // tree.postorder();

    tree.levelOrder();

    return 0;
}

template <class T>
void BinaryTree<T>::createTree() {

    T data;
    cout << "Enter the root node's data: ";
    data = getValidInput();

    Node<T>* newNode = new Node<T>(data);
    if (newNode == NULL) return;

    this->root = newNode;

    Queue<Node<T>*> address_queue;
    address_queue.enqueue(newNode);

    while (!address_queue.isEmpty()) {
        Node<T>* current = address_queue.dequeue();

        cout << "Enter Left data of " << current->data << ": ";
        T left_data = getValidInput();
        if (left_data != -1) {
            Node<T>* new_left_node = new Node<T>(left_data);
            if (new_left_node == NULL) return;
            current->left = new_left_node;
            address_queue.enqueue(new_left_node);
        }

        cout << "Enter right data of " << current->data << ": ";
        T right_data = getValidInput();
        if (right_data != -1) {
            Node<T>* new_right_node = new Node<T>(right_data);
            if (new_right_node == NULL) return;
            current->right = new_right_node;
            address_queue.enqueue(new_right_node);
        }
    }

}

template <class T>
T BinaryTree<T>::getValidInput() {
    T data;
    while (!(cin >> data)) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Bad input, please re-enter: ";
    }
    return data;
}

template <class T>
void BinaryTree<T>::freeTree() {

    if (this->root == NULL) return;
    this->freeNode(this->root);
    this->root = NULL;
}

template <class T>
void BinaryTree<T>::freeNode(Node<T>* root_node) {
    if (root_node->left == NULL && root_node->right == NULL) {
        free(root_node);
    } else if (root_node->left == NULL) {
        freeNode(root_node->right);
        free(root_node);
    } else if (root_node->right == NULL) {
        freeNode(root_node->left);
        free(root_node);
    } else {
        freeNode(root_node->left);
        freeNode(root_node->right);
        free(root_node);
    }
}


template <class T>
bool BinaryTree<T>::isEmpty() {
    return this->root == NULL;
}


// !Recursive Traversals
template <class T>
void BinaryTree<T>::preorder() {
    cout << "Preorder Recursive:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    this->preorder(this->root);
    cout << endl;
}
template <class T>
void BinaryTree<T>::inorder() {
    cout << "Inorder Recursive:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    this->inorder(this->root);
    cout << endl;
}
template <class T>
void BinaryTree<T>::postorder() {
    cout << "postorder Recursive:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    this->postorder(this->root);
    cout << endl;

}


template <class T>
void BinaryTree<T>::preorder(Node<T>* root_node) {
    if (root_node == NULL) return;
    cout << root_node->data << ", ";
    preorder(root_node->left);
    preorder(root_node->right);
}

template <class T>
void BinaryTree<T>::inorder(Node<T>* root_node) {
    if (root_node == NULL) return;
    inorder(root_node->left);
    cout << root_node->data << ", ";
    inorder(root_node->right);
}

template <class T>
void BinaryTree<T>::postorder(Node<T>* root_node) {
    if (root_node == NULL) return;
    postorder(root_node->left);
    postorder(root_node->right);
    cout << root_node->data << ", ";
}

// !iterative traversals
template <class T>
void BinaryTree<T>::preorderIt() {
    cout << "Preorder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }

    // create a node that points to the current node.
    Node<T>* current = this->root;
    // preorder: NLR

    // we implement stack for storing the address of the visited roots.
    stack<Node<T>*> stk;

    while (current != NULL) {
        cout << current->data << ", ";
        if (current->left != NULL) {
            stk.push(current);
            current = current->left;
        } else if (current->right != NULL) {
            current = current->right;
        } else {
            // node is a leaf.
            do {
                if (stk.empty()) break;
                current = stk.top();
                stk.pop();
                current = current->right;
            } while (current == NULL);

        }
    }
    cout << endl;
}

template <class T>
void BinaryTree<T>::inorderIt() {
    cout << "Inorder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }

    Node<T>* current = this->root;
    stack<Node<T>*> stk;
    stk.push(current);
    current = current->left;

    while (current != NULL || !stk.empty()) {

        while (current != NULL) {
            stk.push(current);
            current = current->left;
        }

        current = stk.top();
        stk.pop();
        cout << current->data << ", ";
        current = current->right;
    }
    cout << endl;
}

template <class T>
void BinaryTree<T>::postorderIt() {
    cout << "Postorder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    Node<T>* current = this->root;
    stack<Node<T>*>  stk1, stk2;
    stk1.push(current);

    while (!stk1.empty()) {
        current = stk1.top();
        stk1.pop();
        stk2.push(current);

        if (current->left != NULL) stk1.push(current->left);
        if (current->right != NULL) stk1.push(current->right);
    }

    while (!stk2.empty()) {
        current = stk2.top();
        stk2.pop();
        cout << current->data << ", ";
    }
    cout << endl;
}

template <class T>
void BinaryTree<T>::levelOrder() {
    cout << "levelOrder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }

    Queue<Node<T>*> queue;
    Node<T>* current = this->root;
    queue.enqueue(current);
    cout << current->data << ", ";

    while (!queue.isEmpty()) {
        current = queue.dequeue();

        if (current->left != NULL) {
            cout << current->left->data << ", ";
            queue.enqueue(current->left);
        }
        if (current->right != NULL) {
            cout << current->right->data << ", ";
            queue.enqueue(current->right);
        }
    }
    cout << endl;
}

// template <class T>
// void BinaryTree<T>::generateFromTraversals(T preorder[], T inorder[]) {
//     this->freeTree();
//     int sizeof_preorder=sizeof(preorder) / sizeof(T);
//     int sizeof_inorder = sizeof(inorder) / sizeof(T);

//     if (sizeof_preorder == 0) return;
//     if (sizeof_preorder != sizeof_inorder) return;

//     for (int i = 0;i < sizeof_preorder; i++) {
//         Node<T>* newNode = new Node<T>(preorder[i]);
//         if (newNode == NULL) return;


//     }
// }