//  Adelson-Velsky and Landis Tree
#include <iostream>
#include <stack>
#include "QueueLL.h"
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    // height of each node.
    int height;

    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->height = 0;
    }
};

class AVL {
    Node* root;

    Node* LLRotation(Node*);
    Node* RRRotation(Node*);
    Node* LRRotation(Node*);
    Node* RLRotation(Node*);

    int getNodeHeight(Node*);
    int getBalanceFactor(Node*);
    Node* insert(Node*, int);
    void freeTree();
    void freeNode(Node*);
public:
    AVL() {
        this->root = NULL;
    }
    ~AVL() {
        // this->freeTree();
    }
    void insert(int);
    void inorder();
    void levelOrder();
    int getRoot();

};

int main()
{
    AVL tree;
    for (int i = 10;i <= 100; i = i + 5) {
        tree.insert(i);
        tree.levelOrder();

    }
    // tree.insert(60);
    // tree.insert(70);
    // tree.insert(80);
    // tree.levelOrder();
    return 0;
}

void AVL::insert(int insert_data) {
    // Node* newNode = new Node(insert_data);
    // if (newNode == NULL) return;
    // // memory full

    // // if this is going to be the first node of the tree...
    // if (this->root == NULL) {
    //     this->root = newNode;
    //     // left is null, right is null, height is 0, perfect.
    //     return;
    // }

    // find its appropriate position
    // Node* prev = this->root;
    // Node* current = this->root;
    // while (current != NULL) {
    //     if (insert_data == current->data) {
    //         // duplicate no allowed.
    //         free(newNode);
    //         return;
    //     } else if (insert_data < current->data) {
    //         // LEFT
    //         prev = current;
    //         current = current->left;
    //     } else {
    //         // RIGHT
    //         prev = current;
    //         current = current->right;
    //     }
    // }
    this->root = insert(this->root, insert_data);

}
Node* AVL::insert(Node* current, int insert_data) {
    if (current == NULL) {
        current = new Node(insert_data);
        return current;
    }

    if (insert_data < current->data) {
        current->left = insert(current->left, insert_data);
    } else if (insert_data > current->data) {
        current->right = insert(current->right, insert_data);
    } else return current; // duplicate.

    current->height = getNodeHeight(current);
    int balance = getBalanceFactor(current);
    int balance_left = getBalanceFactor(current->left);
    int balance_right = getBalanceFactor(current->right);

    if (balance == 2 && balance_left == 1) return LLRotation(current);
    else if (balance == 2 && balance_left == -1) return LRRotation(current);
    else if (balance == -2 && balance_right == -1) return RRRotation(current);
    else if (balance == -2 && balance_right == 1) return RLRotation(current);

    return current;
}
Node* AVL::RLRotation(Node* current) {
    if (current == NULL) return NULL;

    Node* right_of_current = current->right;
    Node* future_parent = right_of_current->left;
    Node* left_of_parent = future_parent->left;
    Node* right_of_parent = future_parent->right;

    future_parent->right = right_of_current;
    future_parent->left = current;
    right_of_current->left = right_of_parent;
    current->right = left_of_parent;

    right_of_current->height = getNodeHeight(right_of_current);
    current->height = getNodeHeight(current);
    future_parent->height = getNodeHeight(future_parent);

    if (current = this->root) this->root = future_parent;
    return future_parent;
}


Node* AVL::LRRotation(Node* current) {
    if (current == NULL) return NULL;

    Node* left_of_current = current->left;
    Node* future_parent = left_of_current->right;
    Node* left_of_parent = future_parent->left;
    Node* right_of_parent = future_parent->right;

    future_parent->right = current;
    future_parent->left = left_of_current;
    left_of_current->right = left_of_parent;
    current->left = right_of_parent;

    current->height = getNodeHeight(current);
    left_of_current->height = getNodeHeight(left_of_current);
    future_parent->height = getNodeHeight(future_parent);
    if (current = this->root) this->root = future_parent;

    return future_parent;
}

Node* AVL::RRRotation(Node* current) {
    if (current == NULL) return NULL;

    Node* future_parent = current->right;
    Node* left_of_parent = future_parent->left;

    future_parent->left = current;
    current->right = left_of_parent;

    current->height = getNodeHeight(current);
    future_parent->right->height = getNodeHeight(future_parent->right);//
    future_parent->height = getNodeHeight(future_parent);
    if (current = this->root) this->root = future_parent;

    return future_parent;
}

Node* AVL::LLRotation(Node* current) {
    if (current == NULL) return NULL;

    Node* future_parent = current->left;
    Node* right_of_parent = future_parent->right;

    future_parent->right = current;
    current->left = right_of_parent;

    current->height = getNodeHeight(current);
    future_parent->left->height = getNodeHeight(future_parent->left);//
    future_parent->height = getNodeHeight(future_parent);
    if (current = this->root) this->root = future_parent;

    return future_parent;
}

int AVL::getBalanceFactor(Node* current) {
    if (current == NULL) return 0;

    int lh, rh;
    lh = current->left != NULL ? current->left->height + 1 : 0;
    rh = current->right != NULL ? current->right->height + 1 : 0;
    return lh - rh;
}
int AVL::getNodeHeight(Node* current) {
    if (current == NULL) return 0;

    int lh, rh;
    lh = current->left != NULL ? current->left->height + 1 : 0;
    rh = current->right != NULL ? current->right->height + 1 : 0;

    // if (lh == 0 && rh == 0) return 0;
    return lh > rh ? lh : rh;
}
int AVL::getRoot() {
    if (this->root == NULL) {
        cout << " Empty Tree!";
        return -1;
    }
    return this->root->data;
}

void AVL::levelOrder() {
    cout << "Level by level:\t\t";
    if (this->root == NULL) {
        cout << "Empty tree!" << endl;
        return;
    }
    Queue<Node*> queue;
    Node* current = this->root;
    cout << "( " << current->data << " ";
    queue.enqueue(current);
    while (!queue.isEmpty()) {
        current = queue.dequeue();
        cout << ")-( ";
        if (current->left != NULL) {
            cout << current->left->data << ", ";
            queue.enqueue(current->left);
        }
        if (current->right != NULL) {
            cout << current->right->data << ", ";
            queue.enqueue(current->right);
        }
    }
    cout << ")" << endl;
}

void AVL::inorder() {
    cout << "Inorder Iterative:\t";
    if (this->root == NULL) {
        cout << "Empty tree!" << endl;
        return;
    }

    stack <Node*> stk;
    Node* current = this->root;
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

//*######################### Free tree #########################
void AVL::freeTree() {

    if (this->root == NULL) return;
    this->freeNode(this->root);
    this->root = NULL;
}
//*######################### Free Node #########################
void AVL::freeNode(Node* root_node) {
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