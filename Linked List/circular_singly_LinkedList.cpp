#include <iostream>
using namespace std;

template <class U>
class node {
public:
    U data;
    node* next;

    node() {
        this->data = 0;
        this->next = NULL;
    }

    node(U data) {
        this->data = data;
        this->next = NULL;
    }
};

template <class T>
class CircurlarSinglyLinkedList {
private:
    node<T>* head;
    node<T>* tail;
    int totalNodes;
public:
    CircurlarSinglyLinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->totalNodes = 0;
    }

    void push(T);
    void push(T, int);
    T pop();
    T pop(int);

    void printList();
    bool searchList(T);

    // reverse the parametered list  and store it in this.
    void reverseList(CircurlarSinglyLinkedList);

    void freeList();

};

int main() {

    CircurlarSinglyLinkedList<int> list;
    list.pop();
    list.push(1);
    list.push(4);
    list.push(5);
    list.push(6);
    list.push(2, 2);
    list.push(3, 3);
    cout << "pop: " << list.pop() << endl;
    list.push(3, 3);
    cout << "pop: " << list.pop(1) << endl;
    list.printList();
    cout << "pop: " << list.pop(1) << endl;
    list.printList();
    int x = 3;
    cout << x << " ";
    list.searchList(x) == true ? cout << "found\n" : cout << "not found\n";


    CircurlarSinglyLinkedList<int> list2;
    list2.reverseList(list);

    list2.printList();
    list2.push(1, 1);
    list2.printList();
    list2.push(2, 2);
    list2.printList();
    list2.push(3, 3);
    cout << "list2 is: ";
    list2.printList();

    cout << "list1 again: ";
    list.printList();
    return 0;
}

// !push
template <class T>
void CircurlarSinglyLinkedList<T>::push(T data) {

    // creating a node in heap and storing the address
    // in the pointer called newNode.
    node<T>* newNode = new node<T>(data);

    // check if the memory is allocated or not.
    // if not return from the function.
    if (newNode == NULL) return;

    // check if the newNode is the first node to be
    // linked with the list.
    if (this->totalNodes == 0) {
        newNode->next = newNode;
        this->head = newNode;
        this->tail = newNode;
        (this->totalNodes)++;
        return;
    }

    // if there is a node or more than one node in the list
    // and we are trying to insert the node at the end then,
    // the address of the newNode->next should be the first
    // node's address that is stored in head.
    newNode->next = this->head;
    this->tail->next = newNode;
    this->tail = this->tail->next;
    (this->totalNodes)++;
}

// !push at some index.
template <class T>
void CircurlarSinglyLinkedList<T>::push(T data, int index) {

    // check if the index is 0 or less than 0 or
    // check if the index is larger than the actual size of list.
    if (index <= 0 || index - 1 > this->totalNodes) return;

    // check if the list is empty
    // or check if we want to add the node at last of the list.
    if (this->totalNodes == 0 || index - 1 == this->totalNodes) {
        push(data);
        return;
    }

    // creating a node.
    node<T>* newNode = new node<T>(data);
    if (newNode == NULL) return;
    // check if the index is 1 and there is only one node in the list.
    if (index == 1 && this->totalNodes == 1) {
        this->head = newNode;
        newNode->next = this->tail;
        this->tail->next = this->head;
        (this->totalNodes)++;
        return;
    }

    // else if the index is 1 and there is more than one node in the list
    if (index == 1) {
        this->tail->next = newNode;
        newNode->next = this->head;
        this->head = newNode;
        (this->totalNodes)++;
        return;
    }

    // if we want to insert somewhere between two node.
    // first go to the index.
    node<T>* current = this->head;
    while (--index != 1) current = current->next;

    newNode->next = current->next;
    current->next = newNode;
    (this->totalNodes)++;
}

// !pop
template <class T>
T CircurlarSinglyLinkedList<T>::pop() {

    T return_data;
    // check if the list is empty.
    if (this->totalNodes == 0) return -1;

    if (this->totalNodes == 1) {
        return_data = this->head->data;
        delete this->head;
        this->head = NULL;
        this->tail = NULL;
        this->totalNodes = 0;
        return return_data;
    }

    node<T>* current = this->head;
    return_data = this->tail->data;
    while (current->next != this->tail)
        current = current->next;

    current->next = this->head;
    this->tail->next = NULL;
    delete this->tail;

    this->tail = current;
    (this->totalNodes)--;
    return return_data;
}

// !pop at index.
template <class T>
T CircurlarSinglyLinkedList<T>::pop(int index) {

    T return_data;
    // check if the index is <= 0 or
    // if the index is > than totalNodes.
    if (index <= 0 || index > this->totalNodes) return -1;

    // if totalNodes == 1 or
    // index == totalNodes go to pop();
    if (index == this->totalNodes || this->totalNodes == 1) {
        return_data = pop();
        return return_data;
    }

    // if total nodes are >=2 and we want to delete the first node.
    if (index == 1) {
        node<T>* current = this->head;
        this->head = this->head->next;
        this->tail->next = this->head;
        return_data = current->data;
        current->next = NULL;
        delete current;
        (this->totalNodes)--;
        return return_data;
    }

    // deleting a node between two nodes.
    // node --> node --> (node) --> node --
    //          prev     current

    node<T>* prev = this->head;
    while (--index != 1) prev = prev->next;

    node<T>* current = prev->next;
    return_data = current->data;
    prev->next = current->next;
    (this->totalNodes)--;
    current->next = NULL;
    delete current;
    return return_data;
}

// !printList.
template<class T>
void CircurlarSinglyLinkedList<T>::printList() {

    // if the list is empty.
    if (this->totalNodes == 0) {
        cout << "List is empty" << endl;
        return;
    }

    // current has the same value as of head initially.
    // the first node is printed before entering the loop.
    // and current is continuously checked against head.
    // If current has same value as head then break;
    cout << "Head: ";
    node<T>* current = this->head;
    cout << current->data;
    current = current->next;
    while (current != this->head) {
        cout << " -> " << current->data;
        current = current->next;
    }
    cout << endl;
}

// !search in list
template<class T>
bool CircurlarSinglyLinkedList<T>::searchList(T data) {

    // return false if the list has no nodes.
    if (this->totalNodes == 0) return false;

    // traverse through the nodes, and check for (data)
    // if found then return true else return false.
    node<T>* current = this->head;
    if (current->data == data) return true;
    current = current->next;
    while (current != this->head) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

// !reverse list.
template<class T>
void CircurlarSinglyLinkedList<T>::reverseList(CircurlarSinglyLinkedList<T> list) {

    // make a linkedlist and give the head, tail, totalNodes attributes to (*this).

    this->freeList();
    // now this list is freed.

    // return if the list is empty.
    if (list.totalNodes == 0) return;

    // pushing the head node to (this) list.
    this->push(list.head->data);
    // check if there is only one node in the list.
    if (list.totalNodes == 1) return;

    // else we know that there are more than one node in the list.
    // we can traverse through the list and add each node at the index
    // of 1 as push(data, 1) in function.
    node<T>* current = list.head->next;
    while (current != list.head) {
        this->push(current->data, 1);
        current = current->next;
    }
}

// !free list.
template <class T>
void CircurlarSinglyLinkedList<T>::freeList() {

    if (this->totalNodes == 0) return;

    // if there is only one node.
    if (this->totalNodes == 1) {
        this->tail = NULL;
        delete this->head;
        this->head = NULL;
        this->totalNodes = 0;
        return;
    }

    // there are more than one node.
    // node ->    | node ->|  node ->|  node -> | node ->|
    // head       | curr   | nextN   |          |        | 
    // head       |        |  curr   |  nextN ..|        |   
    // head/nextN |        |         |          |        | .... curr
    node<T>* current = this->head->next;
    while (current != head) {
        node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    this->tail = NULL;
    delete this->head;
    this->head = NULL;
    this->totalNodes = 0;
}