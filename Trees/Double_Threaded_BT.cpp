#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool isLT;
    bool isRT;

    Node(int data) {
        this->data = data;
        this->left = this->right = NULL;
        this->isLT = this->isRT = false;
    }
    Node* getLeftMost();
    Node* getRightMost();
    Node* successor();
    Node* predecessor();
};

class DoubleTBT {
public:
    Node* root;
    void deleteTree();
    DoubleTBT() {
        this->root = NULL;
    }

    ~DoubleTBT() {
        this->deleteTree();
    }
    void insert(int);
    void deleteElement(int);
    void deleteLeafNode(Node*, Node*);
    void deleteOneChildNode(Node*, Node*);
    void deleteTwoChildrenNode(Node*, Node*);
    void inorder();
    int successor(int);
    int predecessor(int);
    bool search(int);
};

int main() {
    DoubleTBT tree;
    tree.insert(15);
    tree.insert(8);
    tree.insert(25);
    tree.insert(4);
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);
    tree.insert(2);
    tree.insert(21);
    tree.insert(11);

    tree.inorder();
    int n = 11;
    // cout << "Finding " << n << ":\t\t";
    // if (tree.search(n)) cout << "Found\n";
    // else cout << "Not Found\n";
    cout << "Successor of " << n << " is:\t" << tree.successor(n) << endl;
    cout << "Predecessor of " << n << " is:\t" << tree.predecessor(n) << endl;
    tree.deleteElement(n);
    tree.inorder();
    return 0;
}

void DoubleTBT::deleteElement(int delete_data) {
    if (this->root == NULL) return;
    // If tree is empty.

    Node* parent = this->root;
    Node* current = this->root;

    while (current != NULL) {
        if (delete_data == current->data) {
            break;
        } else if (delete_data < current->data) {
            if (current->isLT == true) break;
            parent = current;
            current = current->left;
        } else {
            if (current->isRT == true) break;
            parent = current;
            current = current->right;
        }
    }

    // if data is not found
    if (current == NULL || current->data != delete_data) return;

    // current is pointing to the node that is supposed to get deleted.
    // there might be cases like
    // 1. current node is a leaf node.
    // 2. current node has only one child.
    // 3. current node has 2 children.
    // let's create separate functions for either cases.
    if (current->isLT && current->isRT || current->isLT && current->right == NULL || current->isRT && current->left == NULL || current->left == NULL && current->right == NULL) {
        // This means it is leaf node.
        deleteLeafNode(current, parent);
    } else if (current->isLT == false && current->isRT == false && current->left != NULL && current->right != NULL) {
        // has 2 children
        deleteTwoChildrenNode(current, parent);
    } else {
        // has 1 child
        deleteOneChildNode(current, parent);
    }
}
void DoubleTBT::deleteTwoChildrenNode(Node* current, Node* parent) {
    if (current == NULL) return;
    // Find the inorder successor 
    Node* parent_of_replacement = current;
    Node* replacement_rights_leftMost = current->right;

    // Find the leftmost child 
    while (replacement_rights_leftMost->isLT == false) {
        parent_of_replacement = replacement_rights_leftMost;
        replacement_rights_leftMost = replacement_rights_leftMost->left;
    }
    current->data = replacement_rights_leftMost->data;

    if (replacement_rights_leftMost->isRT == true) {
        deleteLeafNode(replacement_rights_leftMost, parent_of_replacement);
    } else {
        deleteOneChildNode(replacement_rights_leftMost, parent_of_replacement);
    }
}
void DoubleTBT::deleteOneChildNode(Node* current, Node* parent) {
    if (current == NULL) return;

    if (this->root == current) {
        // current is root and has only one child.
        // parent is also root.
        // If root has RIGHT child.
        // then go to right's left-most node and make its left node pointer as NULL
        if (current->left == NULL) {
            // RIGHT
            this->root = current->right;
            this->root->isLT = false;
            this->root->isRT = false;
            Node* leftMost = current->right->getLeftMost();
            leftMost->left = NULL;
            leftMost->isLT = false;
        } else {
            // LEFT
            this->root = current->left;
            this->root->isLT = false;
            this->root->isRT = false;
            Node* rightMost = current->left->getRightMost();
            rightMost->right = NULL;
            rightMost->isRT = false;
        }
        free(current);
    } else {
        // current is not a root and has obviously a parent 
        if (current->isLT == true) {
            // RIGHT
            // current has right child
            if (parent->right == current)
                parent->right = current->right;
            else parent->left = current->right;

            if (current->right != NULL) {

                Node* leftMost = current->right->getLeftMost();
                leftMost->left = current->left;
                if (leftMost->left != NULL) leftMost->isLT = true;
                else leftMost->isLT = false;
            }

        } else {
            // LEFT
            if (parent->right == current)
                parent->right = current->left;
            else parent->left = current->left;

            Node* rightMost = current->left->getRightMost();
            rightMost->right = current->right;
            if (rightMost->right != NULL) rightMost->isRT = true;
            else rightMost->isRT = false;
        }
        free(current);
    }
}
void DoubleTBT::deleteLeafNode(Node* current, Node* parent) {
    if (current == NULL) return;

    if (this->root == current) {
        // current is leaf as well as root, i.e., root is the only 
        // simply delete root and give it a NULL value.
        free(current);
        this->root = NULL;
        return;
    }

    // else it is a leaf node.
    // Now it could be either left or right of its parent.

    // current is a leaf node and, if it is right node of parent then,
    // its left node is pointing to the parent. and its right node is pointing
    // to either NULL or inorder successor.

    // else if the current is left node of parent then,
    // its right node is pointing to the parent. and its left node
    // is either NULL or pointing to its predecessor.

    if (parent->left == current) {
        // It is left child.
        parent->left = current->left;
        if (current->left != NULL)  parent->isLT = true;
    } else {
        // It is right child.
        parent->right = current->right;
        if (current->right != NULL) parent->isRT = true;
    }
    free(current);
}

void DoubleTBT::insert(int insert_data) {
    Node* newNode = new Node(insert_data);
    if (newNode == NULL) return;

    if (this->root == NULL) {
        // if this node is the first node to be inserted in the tree.
        // then it must be root node.
        this->root = newNode;
        return;
    }

    // Otherwise, we have to find its location in the tree
    // and make adjustments accordingly.

    // Conclusions after studying the tree.
    // 1. current root's left's right-most node's right is threaded node(if not root of tree) 
    // and thread is followed to current root.
    // 2. current root's right's left-most node's left is threaded node(if not root of tree)
    // and thread is followed to current root.

    Node* parent = this->root;
    Node* current = this->root;

    while (current != NULL) {
        if (insert_data == current->data) {
            // duplicate found.
            free(newNode);
            return;
        } else if (insert_data < current->data) {
            parent = current;
            if (parent->isLT == true) current = NULL;
            else current = current->left;
        } else {
            parent = current;
            if (parent->isRT == true) current = NULL;
            else current = current->right;
        }
    }
    // far now parent node is the pointer to the parent of the newNode.

    if (parent == this->root) {
        // if root is the parent of the child.
        //- now there are 2 possibilities either newNode could be left or right node of parent.
        if (insert_data < parent->data) {
            // it means newNode is going to be left node of parent
            this->root->left = newNode;
            // now newNode becomes the left child of parent.
            newNode->right = this->root;
            // we gave the thread to the newNode's right pointer to the parent.
            // now obviously it becomes now right threaded
            newNode->isRT = true;
        } else {
            // else newNode becomes the right child of parent.
            this->root->right = newNode;
            newNode->left = this->root;
            newNode->isLT = true;
        }
    } else {
        // now parent is the threaded leaf node.
        if (insert_data < parent->data) {
            // left child.
            // storing the thread of the parent.
            Node* left_thread_of_parent = parent->left;
            // giving parent's left pointer the address of the newNode.
            parent->left = newNode;
            // making connection to the same thread that was followed by parent.
            newNode->left = left_thread_of_parent;
            // making newNode's right pointer point to its parent.
            newNode->right = parent;
            newNode->isRT = true;
            if (newNode->left != NULL) newNode->isLT = true;
            parent->isLT = false;
        } else {
            // right child.
            Node* right_thread_of_parent = parent->right;
            parent->right = newNode;
            newNode->right = right_thread_of_parent;
            newNode->left = parent;
            newNode->isLT = true;
            if (newNode->right != NULL) newNode->isRT = true;
            parent->isRT = false;
        }
    }

}

void DoubleTBT::inorder() {
    cout << "Inorder:\t\t";
    if (this->root == NULL) {
        cout << "Tree is Empty!" << endl;
        return;
    }

    Node* current = this->root->getLeftMost();
    while (current != NULL) {
        cout << current->data << ", ";
        if (current->isRT == true) current = current->right;
        else current = current->right->getLeftMost();
    }
    cout << endl;
}

Node* Node::getLeftMost() {
    if (this == NULL) return NULL;

    Node* current = this;
    while (current->left != NULL && current->isLT == false)
        current = current->left;

    return current;
}
Node* Node::getRightMost() {
    if (this == NULL) return NULL;

    Node* current = this;
    while (current->right != NULL && current->isRT == false)
        current = current->right;

    return current;
}

void DoubleTBT::deleteTree() {
    if (this->root == NULL) return;

    Node* current = this->root->getLeftMost();
    while (current != NULL) {
        Node* temp = current;
        if (current->isRT == true) current = current->right;
        else current = current->right->getLeftMost();
        free(temp);
    }
}

bool DoubleTBT::search(int search_data) {
    if (this->root == NULL) return false;

    Node* current = this->root;
    while (current != NULL) {
        if (search_data == current->data) return true;
        else if (search_data < current->data) {
            if (current->isLT == true) return false;
            current = current->left;
        } else {
            if (current->isRT == true) return false;
            current = current->right;
        }
    }
    return false;
}
int DoubleTBT::successor(int element) {
    if (this->root == NULL) {
        cout << "Tree is empty! ";
        return element;
    }

    // if (this->search(element) == false) {
    //     cout << "Element Not found ";
    //     return element;
    // }
    Node* current = this->root;
    while (current != NULL) {
        if (element == current->data) {
            if (current->right != NULL) {
                return current->right->data;
            } else {
                cout << "Last element of Tree is ";
                return element;
            }
        } else if (element < current->data) {
            if (current->isLT == true) break;
            current = current->left;
        } else {
            if (current->isRT == true) break;
            current = current->right;
        }
    }

    cout << element << " Not Found ";
    return element;
}

int DoubleTBT::predecessor(int element) {
    if (this->root == NULL) {
        cout << "Tree is empty! ";
        return element;
    }

    Node* current = this->root;
    while (current != NULL) {
        if (element == current->data) {
            if (current->isLT == true) return current->left->data;
            Node* temp = current->left->getRightMost();
            if (temp != NULL) return temp->data;
            else {
                cout << current->data << " is the first element ";
                return current->data;
            }
        } else if (element < current->data) {
            if (current->isLT == true) break;
            current = current->left;
        } else {
            if (current->isRT == true) break;
            current = current->right;
        }
    }
    cout << element << " Not Found ";
    return element;
}