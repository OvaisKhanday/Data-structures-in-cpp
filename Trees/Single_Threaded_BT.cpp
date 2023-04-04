#include <iostream>
using namespace std;


template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;
    bool isRightThreaded;

    Node(T data) {
        this->data = data;
        this->left = this->right = NULL;
        this->isRightThreaded = false;
    }

    // this function will be returning the leftmost node of (this) node,
    // if (this) has no left children then (this) will be returned.
    Node<T>* getLeftMostNode();
    // this function will be returning the rightmost node of (this) node,
    // if (this) has no right children then (this) will be returned.
    Node<T>* getRightMostNode();
};
template <typename T>
class SingleTBT {
    Node<T>* root;

    void freeTree();
public:
    SingleTBT() {
        this->root = NULL;
    }
    ~SingleTBT() {
        this->freeTree();
    }
    bool isEmpty();
    void insert(T);
    void inorder();
    void deleteNode(T);
};



int main() {
    SingleTBT<int> tree;
    tree.insert(6);
    tree.insert(3);
    tree.insert(8);
    tree.insert(15);
    tree.insert(7);
    tree.insert(2);
    tree.insert(5);
    tree.insert(10);
    tree.insert(9);
    tree.insert(18);

    tree.inorder();
    tree.deleteNode(10);
    tree.inorder();

    return 0;
}
//*######################### Delete #########################
template <typename T>
void SingleTBT<T>::deleteNode(T del_data) {
    if (isEmpty()) return;

    Node<T>* prev = NULL;
    Node<T>* current = this->root;
    while (current != NULL) {
        if (del_data == current->data) break;
        else if (del_data < current->data) {
            prev = current;
            current = current->left;
        } else {
            prev = current;
            current = current->right;
        }
    }

    if (current == NULL) return; // element not found.

    if (current->isRightThreaded == true || current->right == NULL) {
        // it is a leaf node.
        if (current == this->root) {
            // it means only one node is present in tree.
            delete current;
            this->root = NULL;
        } else {
            // else it could be either a left or right leaf.
            if (prev->left == current) {
                // if it is left leaf node.
                prev->left = NULL;
                delete current;
            } else {
                // it is right node.
                prev->right = current->right;
                delete current;
                prev->isRightThreaded = true;
            }
        }
    } else if (current->left != NULL && current->right != NULL) {
        // current node has both left and right children.
        Node<T>* lefts_rightMost = current->left->getRightMostNode();
        Node<T>* rights_leftMost = current->right->getLeftMostNode();

        if (rights_leftMost->right != NULL) rights_leftMost->right->left = NULL;
        else current->right = NULL;

        lefts_rightMost->right = rights_leftMost;
        rights_leftMost->left = current->left;
        rights_leftMost->right = current->right;
        if (current == this->root) {
            this->root = rights_leftMost;
            rights_leftMost->isRightThreaded = false;
        } else {
            prev = rights_leftMost;
            rights_leftMost->isRightThreaded = false;
        }
        delete current;
    } else {
        // current node has either left or right children.
        if (this->root == current) {
            // if current node is root of the tree.
            if (current->left == NULL) {
                // means current is obviously of degree 1, but it has its left child
                // as null, which means it has its right child as not null.
                this->root = current->right;
                delete current;
            } else {
                // Left
                this->root = current->left;
                if (current->isRightThreaded == true) {
                    this->root->right = NULL;
                    this->root->isRightThreaded = false;
                } else {
                    Node<T>* temp = root->right;
                    while (temp->right != current) temp = temp->right;
                    temp->right = NULL;
                    temp->isRightThreaded = false;
                }
                delete current;
            }
        } else {
            // is not root.
            if (prev->left == NULL) {
                //Right
                if (prev->left == current) prev->left = current->right;
                else prev->right = current->right;
            } else {
                // Left
                if (prev->left == current) prev->left = current->left;
                else prev->right = current->left;
                Node<T>* temp = current->left;
                while (temp->right != current) temp = temp->right;
                temp->right = current->right;
                if (temp->right == NULL) temp->isRightThreaded = false;// rightmost
            }
            delete current;
        }
    }
}
//*######################### Insert #########################
template <typename T>
void SingleTBT<T>::insert(T insert_data) {
    Node<T>* newNode = new Node<T>(insert_data);
    if (newNode == NULL) return;

    if (isEmpty()) {
        this->root = newNode;
        return;
    }

    Node<T>* prev = NULL;
    Node<T>* current = this->root;
    while (current != NULL) {
        if (current->data == insert_data) {
            // duplicate data.
            delete newNode;
            return;
        } else if (insert_data < current->data) {
            prev = current;
            current = current->left;
            if (current != NULL && current->isRightThreaded == true) current = NULL;
        } else {
            prev = current;
            if (current->isRightThreaded == true) current = NULL;
            else current = current->right;
        }
    }

    // By now prev pointer will be pointing to the parent of the newNode
    //
    // If newNode is the left node of the parent then newNode's right pointer
    // will be pointing to the parent.
    //
    // Otherwise, if the newNode is the right node of the parent then newNode's
    // right pointer will be pointing to the same node, which was being pointing
    // by the newNode's parent a while ago.

    if (insert_data < prev->data) {
        // newNode is the left node of the parent.
        // -> giving parent the newNode as a left child.
        prev->left = newNode;
        // -> Making connection of newNode's right to its parent.
        newNode->right = prev;
        // -> NewNode now becomes right threaded node.
        // -> and parent is also a right threaded tree we need to remove the 
        // -> thread from parent.
        prev->isRightThreaded = false;
        newNode->isRightThreaded = true;
    } else {
        // newNode is the right node of the parent.
        // -> Making the newNode's right pointer pointing to the the same 
        // node that is being pointed by the newNode's parent.
        bool isRightMostNode = false;
        if (prev->right == NULL) isRightMostNode = true;
        newNode->right = prev->right;
        // giving prev the child, newNode.
        prev->right = newNode;
        prev->isRightThreaded = false;
        if (isRightMostNode == false)
            newNode->isRightThreaded = true;
    }

}

//*######################### is Empty #########################
template <typename T>
bool SingleTBT<T>::isEmpty() {
    return this->root == NULL;
}
//*######################### Inorder Traversal #########################
template <typename T>
void SingleTBT<T>::inorder() {
    cout << "Inorder Traversal:\t";
    if (this->isEmpty()) {
        cout << "Tree is empty." << endl;
        return;
    }

    Node<T>* current = this->root;
    current = current->getLeftMostNode();
    while (current != NULL) {
        cout << current->data << ", ";
        if (current->isRightThreaded) current = current->right;
        else current = current->right->getLeftMostNode();
    }
    cout << endl;
}
//*######################### return leftMost node #########################
template <typename T>
Node<T>* Node<T>::getLeftMostNode() {
    if (this == NULL) return NULL;

    Node<T>* prev = NULL;
    Node<T>* current = this;
    while (current != NULL) {
        prev = current;
        current = current->left;
    }
    return prev;
}
//*######################### return rightMost node #########################
template <typename T>
Node<T>* Node<T>::getRightMostNode() {
    if (this == NULL) return NULL;

    Node<T>* current = this;
    while (current->right != NULL && current->isRightThreaded == false) {
        current = current->right;
    }
    return current;
}
//*######################### Free tree #########################
template <typename T>
void SingleTBT<T>::freeTree() {
    if (this->isEmpty()) return;

    Node<T>* current = this->root;
    Node<T>* temp = NULL;
    while (current != NULL) {
        current = current->getLeftMostNode();
        temp = current->right;
        delete current;
        if (temp == NULL) return;
        current = temp->right;
        delete temp;
        if (current == this->root) current = current->right;
    }
}