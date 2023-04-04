#include <iostream>
using namespace std;

template <class U>
class node {
public:
    U data;
    node* next;
    node* prev;
    node() {
        this->data = 0;
        this->next = NULL;
        this->prev = NULL;
    }

    node(U data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

template <class T>
class CircularDoublyLinkedList {
    node<T>* head;
    node<T>* tail;
    int totalNodes;
public:
    CircularDoublyLinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->totalNodes = 0;
    }

    void push(T);
    void push(T, int);
    void pop();
    void pop(int);

    void printList();
    bool searchList(T);

    // store the nodes in (this)list in reversed order.
    void reverseList(CircularDoublyLinkedList);

    void freeList();
};

int main() {

    CircularDoublyLinkedList<int> list1;
    CircularDoublyLinkedList<int> list2;

    list1.push(1);
    list1.push(2);
    list1.push(3);
    list1.push(4);
    list1.push(4, 1);
    list1.push(44, 2);
    list1.push(55, 7);
    list1.push(0, 3);
    list1.printList();
    list2.reverseList(list1);
    list2.printList();
    return 0;
}

// !push
template <class T>
void CircularDoublyLinkedList<T>::push(T data) {

    // creating a node and saving its location in a
    // pointer called newNode.
    node<T>* newNode = new node<T>(data);
    // checking if the memory allocation is successful
    if (newNode == NULL) return;

    // if this is the first node to be inserted in the list.
    // if totalNodes == 0 or this.head == NULL
    if (this->totalNodes == 0) {
        newNode->next = newNode;
        newNode->prev = newNode;
        this->head = newNode;
        this->tail = newNode;
        (this->totalNodes)++;
        return;
    }

    newNode->next = this->head;
    this->head->prev = newNode;
    this->tail->next = newNode;
    newNode->prev = this->tail;
    this->tail = newNode;
    (this->totalNodes)++;
}

// !push at index
template <class T>
void CircularDoublyLinkedList<T>::push(T data, int index) {

    // check if the index is in-bound
    // index > 0 and <= totalNodes + 1
    if (index <= 0 || index - 1 > this->totalNodes) return;

    // check if the list is empty
    // or check if we want to add the node at last of the list.
    if (this->totalNodes == 0 || index - 1 == this->totalNodes) {
        push(data);
        return;
    }

    // creating a node in the memory and storing its address in
    // the pointer called newNode.
    node<T>* newNode = new node<T>(data);
    if (newNode == NULL) return;

    // if we want to add the node at the first and there is only one node in the list.
    // meaning head and tail are both pointing to the same node.
    if (index == 1 && this->totalNodes == 1) {
        newNode->next = this->head;
        this->head->next = newNode;
        this->head->prev = newNode;
        newNode->prev = this->head;
        this->head = newNode;
        (this->totalNodes)++;
        return;
    }

    // if we want to add the node at the first and there is more than a node present
    // in list.
    if (index == 1) {
        this->head->prev = newNode;
        newNode->next = this->head;
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->head = newNode;
        (this->totalNodes)++;
        return;
    }

    // if we want to add the node in between two nodes.
    node<T>* current = this->head;
    // --going to the node before the desired location.
    while (--index != 1) current = current->next;
    newNode->next = current->next;
    current->next->prev = newNode;
    newNode->prev = current;
    current->next = newNode;
    (this->totalNodes)++;
}

//!printing list.
template <class T>
void CircularDoublyLinkedList<T>::printList() {

    if (this->totalNodes == 0) {
        cout << "Empty list" << endl;
        return;
    }

    node<T>* current = this->head->next;
    cout << "Head: -> " << this->head->data;
    while (current != this->head) {
        cout << " -> " << current->data;
        current = current->next;
    }
    cout << " -> :Tail" << endl;
}

//!search in list.
template <class T>
bool CircularDoublyLinkedList<T>::searchList(T data) {

    // check if the list is empty.
    if (this.totalNodes == 0) return false;

    // traverse through whole list using a dummy pointer, current.
    // --check for first node.
    if (this->head->data == data) return true;

    node<T>* current = this->head->next;
    while (current != this->head) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

//!free list.
template <class T>
void CircularDoublyLinkedList<T>::freeList() {

    if (this->totalNodes == 0) return;

    // create a dummy pointer, current which will go-on deleting the nodes.
    // let's preserve the head, as it is must to stop the loop and give
    // current the value of head.next.

    if (this->totalNodes == 1) {
        this->tail = NULL;
        delete this->head;
        this->head = NULL;
        this->totalNodes = 0;
        return;
    }

    // else we know that total nodes are more than one.
    node<T>* current = this->head->next;
    while (current != this->head) {
        node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    this->tail = NULL;
    delete this->head;
    this->head = NULL;
    this->totalNodes = 0;
}

// !reverse a list.
template <class T>
void CircularDoublyLinkedList<T>::reverseList(CircularDoublyLinkedList<T> list) {

    // first of all free the list,
    this->freeList();

    // if the (list) is empty, we have freed the (this), then return (this);
    if (list.totalNodes == 0) return;

    // we can copy two list, and then change every prev and next node.

    // altenate method where we push every-element at the front of list.
    node<T>* current = list.head;
    int total_iterations = list.totalNodes;
    while (total_iterations > 0) {
        this->push(current->data, 1);
        current = current->next;
        total_iterations--;
    }
}