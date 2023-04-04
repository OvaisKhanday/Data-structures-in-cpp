#include <iostream>
#include "QueueLL.h"
#include <stack>

using namespace std;


template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T data) {
        // constructor for creating a node with value of data, as data,
        // in heap memory
        this->data = data;
        // making its left and right pointers to NULL
        this->left = this->right = NULL;
    }
};

template <typename T>
class BST {
    // Every tree object must have a pointer to the root of the tree.
    Node<T>* root;

    // function to be called by destructor, ==GarbageCollection
    void freeTree();
    // this function is used by freeTree to recursively perform delete operations.
    void freeNode(Node<T>*);
    // this function is used by addArrayElements() function.
    Node<T>* nodeFromArray(T*, int, int);

    void insert(Node<T>**, T);
    void inorder(Node<T>*);
    void preorder(Node<T>*);
    void postorder(Node<T>*);
    int getHeight(Node<T>*);
    int getCount(Node<T>*);
    int getLeafCount(Node<T>*);
    int getNonLeafCount(Node<T>*);
    bool areEqualNodes(Node<T>*, Node<T>*);
    void mirrorTree(Node<T>*);
public:
    BST() {
        this->root = NULL;
    }
    ~BST() {
        // calling it when the object is about to be get destroyed.
        this->freeTree();
    }

    bool isEmpty();

    // Returns true if the data is found else false.
    bool search(T);

    // returns true if this and argument tree are same.
    bool areSameTrees(BST<T>*);

    // converting the caller tree to its mirror image.
    void mirrorTree();
    // converting the caller tree to its mirror image iteratively.
    void mirrorTreeIterative();

    // returns the height of the tree.
    int getHeight();
    // return the total nodes in the tree.
    int getCount();
    // returns the total leaf nodes of the tree.
    int getLeafCount();
    // return the total non-leaf nodes of the tree.
    int getNonLeafCount();

    bool deleteByCopying(T);
    bool deleteByMerging(T);

    // inserting a new element in the tree recursively
    void insert(T);
    // inserting a new element in the tree iteratively.
    void insertIterative(T);

    // This function generates the tree on the basis on elements in the array,
    // before proceding to the insertion process this function, clears the 
    // tree and deletes its content. If the passed array is empty you would not lose
    // the tree. If the array size is >=1 then tree is cleared and elements are added.
    void generateFromArray(T[], int);
    // This function appends the elements of the array to the tree without deleting the 
    // existing tree. Duplicated are not inserted.
    void addArrayElements(T[], int);

    // tree traversals recursive and iterative.
    void preorder();
    void inorder();
    void postorder();
    void preorderIterative();
    void inorderIterative();
    void postorderIterative();
    void levelByLevel();
};



int main() {
    BST<int> tree;
    BST<int> tree2;
    int array[] = { 5,9,3,7 };
    // int array2[] = { 10,20,30,40,50,60,70,80,90,100,110,120,130,140,150 };

    // tree.insertIterative(100);
    tree.generateFromArray(array, sizeof(array) / sizeof(int));
    tree2.generateFromArray(array, sizeof(array) / sizeof(int));
    tree2.deleteByCopying(5);
    tree.deleteByCopying(5);
    cout << "Tree1 == Tree2: " << tree.areSameTrees(&tree2) << endl;

    tree.insertIterative(1);
    tree.insertIterative(10);
    tree.insertIterative(8);
    tree.insertIterative(4);
    tree.inorderIterative();
    tree.levelByLevel();
    tree.mirrorTreeIterative();
    tree.levelByLevel();
    tree.inorderIterative();

    // // tree.inorder();
    // tree.insert(10);
    // tree.insert(20);
    // tree.insert(5);
    // tree.insert(4);
    // tree.insert(7);
    // tree.insert(15);
    // // tree.inorder();
    // tree.insertIterative(200);
    // tree.insertIterative(150);
    // tree.insertIterative(110);
    // // tree.addArrayElements(array2, sizeof(array2) / sizeof(int));
    // cout << "--------------------------------\n";
    // tree.preorder();
    // tree.preorderIterative();
    // cout << "--------------------------------\n";
    // tree.inorder();
    // tree.inorderIterative();
    // cout << "--------------------------------\n";
    // tree.postorder();
    // tree.postorderIterative();
    // cout << "--------------------------------\n";
    // tree.levelByLevel();
    // cout << "--------------------------------\n";
    // cout << "Height of tree is:\t" << tree.getHeight() << endl;
    // cout << "Total nodes in tree:\t" << tree.getCount() << endl;
    // cout << "Total Leaf nodes:\t" << tree.getLeafCount() << endl;
    // cout << "Total non-leaf nodes:\t" << tree.getNonLeafCount() << endl;
    // cout << "--------------------------------\n";
    // // cout << "Is 45 present: " << tree.search(45) << "\n";
    // // cout << "Is 50 present: " << tree.search(50) << "\n";
    // // cout << "Is 60 present: " << tree.search(60) << "\n";
    // // cout << "Is 9 present: " << tree.search(9) << "\n";
    // // cout << "Is 200 present: " << tree.search(200) << "\n";
    // // cout << "Is 4 present: " << tree.search(4) << "\n";
    // // cout << "Is 15 present: " << tree.search(15) << "\n";
    // cout << "--------------------------------\n";
    // tree.inorder();
    // int del = 200;
    // cout << "Deleting " << del << ":\t\t" << tree.deleteByCopying(del) << endl;
    // tree.inorder();
    // tree.levelByLevel();
    return 0;
}

//*######################### Insert #########################
template <typename T>
void BST<T>::insert(T insert_data) {
    // This function uses another function internally,
    // the main aim of using another function is, that user has to enter
    // data only without giving the reference to the root of the tree.
    insert(&root, insert_data);
}
//*######################### Insert Recursive #########################
template <typename T>
void BST<T>::insert(Node<T>** current_root, T insert_data) {
    // double pointer is used here, because root in the upper function is also a pointer.
    // if we pass directly root then this function will created copy of it and before exiting 
    // from the function that copy will be deleted.
    if (*current_root == NULL)
        *current_root = new Node<T>(insert_data);
    else if (insert_data < (*current_root)->data)
        insert(&((*current_root)->left), insert_data);
    else if (insert_data > (*current_root)->data)
        insert(&((*current_root)->right), insert_data);
    else return; // duplicate found.

}
//*######################### Insert Iterative #########################
template <typename T>
void BST<T>::insertIterative(T insert_data) {
    // creating a new node in the heap memory.
    Node<T>* newNode = new Node<T>(insert_data);
    // check if the memory allocation succeeded
    if (newNode == NULL) return;

    // if this newNode is gonna be first node of  the tree.
    if (this->isEmpty()) {
        this->root = newNode;
        return;
    }

    //else go to the desired location.
    Node<T>* prev = NULL;
    Node<T>* current = this->root;
    while (current != NULL) {
        if (insert_data < current->data) {
            prev = current;
            current = current->left;
        } else if (insert_data > current->data) {
            prev = current;
            current = current->right;
        } else {
            // duplicate ==
            free(newNode);
            prev = NULL;
            break;
        }
    }
    if (prev != NULL) {
        if (insert_data > prev->data) prev->right = newNode;
        else prev->left = newNode;
    }
}
//*######################### Deleting by Copying #########################
template <typename T>
bool BST<T>::deleteByCopying(T delete_node_data) {
    if (this->isEmpty()) return false;

    // Find the desired node.
    // While finding the node, we will be storing its predecessor because that
    // is going to be used while updating the pointers. 
    Node<T>* prev = NULL;
    Node<T>* current = this->root;
    bool node_is_present = false;

    while (current != NULL) {

        // breaking the loop if we find the node.
        if (current->data == delete_node_data) {
            node_is_present = true;
            break;
            // else if, the delete_node_data is smaller than the current node's.
            // move the current to its left.
        } else if (delete_node_data < current->data) {
            // updating the prev to current before moving on.
            prev = current;
            current = current->left;
        }
        // else, if the delete_node_data is not equal or smaller then it is,
        // greater than the current node's data. Hence move to right of current node.
        else {
            // updating the prev to current before moving on.
            prev = current;
            current = current->right;
        }

    }

    // if node is not present in the tree, return false.
    if (node_is_present == false) return false;

    // Now we have prev pointing to the predecessor of the delete_node.
    // current is pointing to the current node that is to be deleted.

    // ?we will be checking if the node is leaf or of degree 1 or 2.
    // if node is a leaf.
    if (current->left == NULL && current->right == NULL) {
        if (prev == NULL) {
            // it means there is only one node present int the tree, root node,
            // and we want to delete that.
            // current is pointing to the root of the tree.
            delete current;
            this->root = NULL;
        } else {
            // else the node is not root node, and it is a leaf node.
            // we have the pointer pointing to the predecessor of the current node,
            // but we don't know is it the left or the right node of the prev.
            if (prev->left == current) prev->left = NULL;
            else prev->right = NULL;
            delete current;
        }
    }
    // if node has degree 2, means it has 2 nodes attached to it, both left and right.
    else if (current->left != NULL && current->right != NULL) {
        // we have to replace the current node with the leftmost node of 
        // current's right node.
        // we also need a predecessor for the left_most node.
        Node<T>* prev_of_left_most = NULL;
        Node<T>* left_most = current->right;

        while (left_most->left != NULL) {
            prev_of_left_most = left_most;
            left_most = left_most->left;
        }
        // Now left_most node is pointing to the substitute of the current node.
        // Now considering left_most node it could have only 2 possible cases,
        // either it is a leaf node or a node with degree one. It can't be a node
        // with degree 2 because if so then the iterator above had gone to the left
        // of the left_most node also.
        // - if it is a leaf node.
        if (left_most->left == NULL && left_most->right == NULL) {
            if (prev_of_left_most == NULL) {
                // There is only one node present to the right of the current,
                // and we can replace that in this way.
                if (prev == NULL) {
                    // current is pointing to the root of the tree and we need to update the
                    // root value after deleting.
                    left_most->left = current->left;
                    this->root = left_most;
                    delete current;
                } else {
                    left_most->left = current->left;
                    if (prev->left == current) prev->left = left_most;
                    else prev->right = left_most;
                    delete current;
                }
            } else {
                // if prev_of_left_most != NULL
                // it means prev_of_left_most is pointing to the node before
                // left_most node and we have to make it null later on.

                // - we know the prev_of_left_most is before the left_most,
                // - and left_most is the left node of prev_of_left_most.
                prev_of_left_most->left = NULL;

                // making connections of left_most node.
                left_most->left = current->left;
                left_most->right = current->right;

                if (prev == NULL) {
                    // current is root of the tree.
                    delete current;
                    this->root = left_most;
                } else {
                    if (prev->left == current) prev->left = left_most;
                    else prev->right = left_most;
                    delete(current);
                }
            }
        } else {
            // If the left_most node has degree 1.
            // simply make connection of prev_of_left_most to the right of left_most node.
            if (prev_of_left_most == NULL) {
                // left_most is the direct right node of current.
                if (prev == NULL) {
                    // current is the root of the tree
                    left_most->left = current->left;
                    this->root = left_most;
                    delete(current);
                } else {
                    // if the current is not pointing to the root.
                    left_most->left = current->left;
                    if (prev->right == current) prev->right = left_most;
                    else prev->left = left_most;
                    delete current;
                }
            } else {
                // prev_of_left_most is not NULL
                prev_of_left_most->left = NULL;
                left_most->left = current->left;
                left_most->right = current->right;

                if (prev == NULL) {
                    // current is root.
                    delete current;
                    this->root = left_most;
                } else {
                    if (prev->left == current) prev->left = left_most;
                    prev->right = left_most;
                    delete current;
                }
            }
        }
    }
    // if node has degree 1, means it has only one node attached to it.
    else {
        // here current is pointing to the node to be removed.
        // prev is pointing to the node before current.
        // we have to make a connection between the prev's left/right to the
        // current's left/right.
        // before making connection to the next, we may be intrested in finding
        // actually is the next node the left child or right.
        Node<T>* next = NULL;
        if (current->left == NULL) {
            // means it has only one node and if the left is null, then the next node
            // is right child of current.
            next = current->right;
        } else next = current->left;

        // finding the relation between current and prev.
        // is current the left node of prev or right node.

        if (prev == NULL) {
            // current is pointing to the root of the tree and we need to update the
            // root value of the root after deleting.
            // we know there is only one child of root, we can simply delete the root,
            // and make the next the new value of the root.
            this->root = next;
            delete current;
        } else {
            // current is pointing to the node that is not root.
            // Find is current the left or right child of prev.
            // And make connections accordingly.
            if (prev->left == current) prev->left = next;
            else prev->right = next;
            delete current;
        }
    }
    return true;
}
//*######################### Deleting by Merging #########################
//*######################### Are 2 BST's equal? #########################
template <typename T>
bool BST<T>::areSameTrees(BST<T>* tree) {
    return areEqualNodes(this->root, tree->root);
}
//*######################### Are 2 BST's equal? Recursive #########################
template <typename T>
bool BST<T>::areEqualNodes(Node<T>* root1, Node<T>* root2) {

    if (root1 == NULL && root2 == NULL) return true;
    if (root1 == NULL) return false;
    if (root2 == NULL) return false;
    if (root1->data != root2->data) return false;
    return areEqualNodes(root1->left, root2->left) && areEqualNodes(root1->right, root2->right);
}
//*######################### Mirror Tree #########################
template<typename T>
void BST<T>::mirrorTree() {
    if (this->isEmpty()) return;
    this->mirrorTree(this->root);
}
//*######################### Mirror Tree Recursive #########################
template<typename T>
void BST<T>::mirrorTree(Node<T>* current_root) {
    if (current_root == NULL) return;
    mirrorTree(current_root->left);
    mirrorTree(current_root->right);
    Node<T>* swap_temp = current_root->left;
    current_root->left = current_root->right;
    current_root->right = swap_temp;

}
//*######################### Mirror Tree Iterative #########################
template <typename T>
void BST<T>::mirrorTreeIterative() {
    if (this->isEmpty()) return;

    // I can traverse level by level, and keep swapping the nodes' left and right.
    // we can use queue to traverse level by level.
    Queue<Node<T>*> queue;
    queue.enqueue(this->root);
    Node<T>* current = NULL;
    while (!queue.isEmpty()) {
        current = queue.dequeue();

        // if both are null then no need to swap the nodes.
        if (current->left != NULL && current->right != NULL) {
            Node<T>* swap_temp = current->left;
            current->left = current->right;
            current->right = swap_temp;
        }

        if (current->right != NULL)
            queue.enqueue(current->right);
        if (current->left != NULL)
            queue.enqueue(current->left);
    }
}
//*######################### Generate new tree from Array #########################
template <typename T>
void BST<T>::generateFromArray(T* array, int sizeof_array) {
    if (sizeof_array == 0) return;
    this->freeTree();
    for (int i = 0; i < sizeof_array; i++) {
        this->insert(array[i]);
    }
}
//*######################### Add array elements to tree #########################
template <typename T>
void BST<T>::addArrayElements(T* array, int sizeof_array) {
    if (sizeof_array == 0) return;

    for (int i = 0; i < sizeof_array; i++) {
        this->insert(array[i]);
    }
}
//*######################### Preorder #########################
template <typename T>
void BST<T>::preorder() {
    cout << "Preorder Recursive:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    this->preorder(this->root);
    cout << endl;

}
//*######################### Inorder #########################
template <typename T>
void BST<T>::inorder() {
    cout << "Inorder Recursive:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    this->inorder(this->root);
    cout << endl;
}
//*######################### Postorder #########################
template <typename T>
void BST<T>::postorder() {
    cout << "Postorder Recursive:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    this->postorder(this->root);
    cout << endl;
}
//*######################### Level order traversal #########################
template <typename T>
void BST<T>::levelByLevel() {
    cout << "Level by level:\t\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    Queue<Node<T>*> queue;
    Node<T>* current = this->root;
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
//*######################### Inorder Iterative #########################
template <typename T>
void BST<T>::inorderIterative() {
    cout << "Inorder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }

    stack <Node<T>*> stk;
    Node<T>* current = this->root;
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
//*######################### Preorder Iterative #########################
template <typename T>
void BST<T>::preorderIterative() {
    cout << "Preorder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }
    Node<T>* current = this->root;
    stack<Node<T>*> stk;
    stk.push(current);

    while (!stk.empty()) {
        current = stk.top();
        stk.pop();

        cout << current->data << ", ";

        if (current->right != NULL) stk.push(current->right);
        if (current->left != NULL) stk.push(current->left);
    }
    cout << endl;
}
//*######################### Postorder Iterative #########################
template <typename T>
void BST<T>::postorderIterative() {
    cout << "Postorder Iterative:\t";
    if (this->isEmpty()) {
        cout << "Empty tree!" << endl;
        return;
    }

    Node<T>* current = this->root;
    Node<T>* prev = NULL;
    stack<Node<T>*> stk;

    while (current != NULL || !stk.empty()) {
        if (current != NULL) {
            stk.push(current);
            current = current->left;
        } else {
            current = stk.top();
            if (current->right == NULL || current->right == prev) {
                cout << current->data << ", ";
                stk.pop();
                prev = current;
                current = NULL;
            } else current = current->right;
        }
    }
    cout << endl;

    // ?USING 2 STACKS
    /* Node<T>* current = this->root;
    /* stack<Node<T>*>  stk1, stk2;
    /* stk1.push(current);
    /* while (!stk1.empty()) {
    /*     current = stk1.top();
    /*     stk1.pop();
    /*     stk2.push(current);
    /*     if (current->left != NULL) stk1.push(current->left);
    /*     if (current->right != NULL) stk1.push(current->right);
    /* }
    /* while (!stk2.empty()) {
    /*     current = stk2.top();
    /*     stk2.pop();
    /*     cout << current->data << ", ";
    /* }*/
}
//*######################### search #########################
template <typename T>
bool BST<T>::search(T search_data) {
    if (this->isEmpty()) return false;

    Node<T>* current = this->root;
    while (current != NULL) {
        if (current->data == search_data) return true;
        if (search_data < current->data) current = current->left;
        else if (search_data > current->data) current = current->right;
    }
    return false;
}
//*######################### getHeight #########################
template <typename T>
int BST<T>::getHeight() {
    // return -1 if the tree is empty
    // return 0 if the tree has only one node.
    return getHeight(this->root);
}
//*######################### getHeight Recursive #########################
template <typename T>
int BST<T>::getHeight(Node<T>* current_root) {
    if (current_root == NULL) return -1;
    int l, r;
    l = getHeight(current_root->left);
    r = getHeight(current_root->right);
    return l > r ? l + 1 : r + 1;
}
//*######################### get total nodes #########################
template <typename T>
int BST<T>::getCount() {
    if (this->isEmpty()) return 0;
    return getCount(this->root);
}
//*######################### get total nodes Recursive #########################
template <typename T>
int BST<T>::getCount(Node<T>* current_root) {
    int l, r;
    if (current_root != NULL) {
        l = getCount(current_root->left);
        r = getCount(current_root->right);
        return l + r + 1;
    }
    return 0;
}
//*######################### get Leaf nodes count #########################
template <typename T>
int BST<T>::getLeafCount() {
    if (this->isEmpty()) return 0;
    return getLeafCount(this->root);
}
//*######################### get Leaf nodes count Recursive #########################
template <typename T>
int BST<T>::getLeafCount(Node<T>* current_root) {
    if (current_root == NULL) return 0;
    if (current_root->left == NULL && current_root->right == NULL) return 1;
    int l, r;
    l = getLeafCount(current_root->left);
    r = getLeafCount(current_root->right);
    return l + r;
}
//*######################### get non-leaf nodes count #########################
template <typename T>
int BST<T>::getNonLeafCount() {
    if (this->isEmpty()) return 0;
    return getNonLeafCount(this->root);
}
//*######################### get non-leaf nodes count Recursive #########################
template <typename T>
int BST<T>::getNonLeafCount(Node<T>* current_root) {
    if (current_root == NULL) return 0;
    if (current_root->left == NULL && current_root->right == NULL) return 0;
    int l, r;
    l = getNonLeafCount(current_root->left);
    r = getNonLeafCount(current_root->right);
    return l + r + 1;
}
//*######################### Preorder Recursive #########################
template <typename T>
void BST<T>::preorder(Node<T>* root_node) {
    // NLR
    if (root_node == NULL) return;
    cout << root_node->data << ", ";
    preorder(root_node->left);
    preorder(root_node->right);
}
//*######################### Inorder Recursive #########################
template <typename T>
void BST<T>::inorder(Node<T>* root_node) {
    // LNR
    if (root_node == NULL) return;
    inorder(root_node->left);
    cout << root_node->data << ", ";
    inorder(root_node->right);
}
//*######################### Postorder Recursive #########################
template <typename T>
void BST<T>::postorder(Node<T>* root_node) {
    // LRN
    if (root_node == NULL) return;
    postorder(root_node->left);
    postorder(root_node->right);
    cout << root_node->data << ", ";
}

//*######################### Free tree #########################
template <typename T>
void BST<T>::freeTree() {

    if (this->root == NULL) return;
    this->freeNode(this->root);
    this->root = NULL;
}
//*######################### Free Node #########################
template <typename T>
void BST<T>::freeNode(Node<T>* root_node) {
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
//*######################### IsEmpty #########################
template <typename T>
bool BST<T>::isEmpty() {
    return this->root == NULL;
}

