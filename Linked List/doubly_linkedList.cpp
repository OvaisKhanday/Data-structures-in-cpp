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
class DoublyLinkedList {
public:

    node<T>* head;
    node<T>* tail;
    unsigned int totalNodes;

    DoublyLinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->totalNodes = 0;
        this->is_list_returned_from_concatenation_overload = false;
    }

    void push(T);
    void push(T, int);
    void pop();
    void pop(int);

    bool searchNode(T);
    void printList();
    void printReverse();
    void reverseList();

    void operator = (DoublyLinkedList);
    DoublyLinkedList operator + (DoublyLinkedList);

    void freeList();
private:
    bool is_list_returned_from_concatenation_overload;
};

int main() {


    DoublyLinkedList<int> list1;
    list1.push(1);
    list1.push(2);
    list1.push(3);
    list1.push(4);
    list1.push(5);
    list1.push(10, 4);

    // list1.printList();
    // cout << "print reverse" << endl;
    // list1.printReverse();
    list1.pop();
    // list1.printList();
    list1.pop();
    // list1.printList();
    list1.push(234);

    // list1.printList();
    list1.pop(3);
    // list1.printList();
    // list1.printReverse();
    list1.reverseList();
    list1.push(468);
    cout << "list1 is : ";
    list1.printList();

    DoublyLinkedList<int> list2 = list1;
    cout << "copied list1 into list2 : ";
    list2.printList();

    list2 = list1 + list2;
    cout << "list2 = list1 + list2" << endl;
    cout << "list2 is: ";
    list2.printList();

    cout << "list 1 again \n";
    list1.printList();

    list1.freeList();
    list2.freeList();
    return 0;
}


//! push node at the end of list.
template <class T>
void DoublyLinkedList<T>::push(T data) {

    // make a node and store the address of the node
    // inside the newNode pointer.
    node<T>* newNode = new node<T>(data);
    // if memory is not allocated.
    if (newNode == NULL) return;

    // if this is going to be the first node in the list.
    if (this->tail == NULL) {
        this->head = newNode;
        this->tail = newNode;
        (this->totalNodes)++;
        return;
    }

    // it is not the first node
    // there exists one or more nodes
    // --connecting the next of current node to the newNode
    this->tail->next = newNode;
    // --connecting the newNode back to the Next part of this node.
    newNode->prev = this->tail;
    // --Updating the tail to the newNode.
    this->tail = newNode;
    // incrementing the totalNodes.
    (this->totalNodes)++;
}

// !push at location
template <class T>
void DoublyLinkedList<T>::push(T data, int index) {

    // check if the index is > 0.
    // or if the index is greater than the
    // total nodes available.
    if (index <= 0 || index > (this->totalNodes) + 1) return;

    // Head --> NULL
    // Head --> node --> node --> (newNode).
    // and if we want to add node at end.
    if (this->totalNodes == 0 || index == (this->totalNodes) + 1) {
        push(data);
        return;
    }

    // -- create newNode.
    node<T>* newNode = new node<T>(data);
    if (newNode == NULL) return;
    // Head --> (NewNode) --> ...
    // if we want to add node on front, i.e., index = 1.
    if (index == 1) {
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
        (this->totalNodes)++;
        return;
    }

    // Head --> Node --> Node -> (newNode) -> Node ->..
    // newNode between two nodes.
    // ---- creating a current pointer to the desired location.
    node<T>* current = this->head;
    while (--index != 1)
        current = current->next;

    // temp is now pointing toward the node before the location of newNode.
    newNode->next = current->next;
    current->next->prev = newNode;
    newNode->prev = current;
    current->next = newNode;
    (this->totalNodes)++;
}

// !printing the list.
template <class T>
void DoublyLinkedList<T>::printList() {

    // check if the list is empty.
    if (this->totalNodes == 0) return;

    // iterate over the list using a dummy pointer.
    node<T>* current = this->head;

    cout << "Head: -> ";
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << ":Tail" << endl;
}

// !poping a node from the list.
template <class T>
void DoublyLinkedList<T>::pop() {

    // check if the list is empty
    if (this->totalNodes == 0) return;

    // if there is only one node in the list.
    // Head and Tail must be pointing to the same node.
    if (this->totalNodes == 1) {
        delete this->head;
        // head and tail must be pointing to the same node
        // hence deleting head or tail will remove the same node.
        this->head = NULL;
        this->tail = NULL;
        this->totalNodes = 0;
    }

    // if the are more than one node.
    // --> making the (next) of the node before last to NULL.
    //     and then deleting the tail
    //     then updating the tail.
    node<T>* node_before_delete = this->tail->prev;
    node_before_delete->next = NULL;
    delete this->tail;
    this->tail = node_before_delete;
    (this->totalNodes)--;
}

// !pop at location
template <class T>
void DoublyLinkedList<T>::pop(int index) {

    // check if the list is empty or
    // index is valid natural number or
    // index is greater than the total nodes.
    if (index <= 0 || this->totalNodes == 0 || index > this->totalNodes) return;

    // check if the index specifies the last node.
    if (index == this->totalNodes) {
        pop();
        return;
    }

    // going to the location of node before the node we are gonna pop.
    node<T>* current = this->head;
    while (--index != 0)
        current = current->next;

    current->prev->next = current->next;
    current->next->prev = current->prev;
    current->prev = NULL;
    current->next = NULL;
    delete current;
    (this->totalNodes)--;
}

// !print reverse list.
template <class T>
void DoublyLinkedList<T>::printReverse() {

    // check if the list is empty.
    if (this->totalNodes == 0) return;

    // iterate over the list using a dummy pointer.
    node<T>* current = this->tail;

    cout << "Tail: -> ";
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->prev;
    }
    cout << ":Head" << endl;
}

// !reverse list
template <class T>
void DoublyLinkedList<T>::reverseList() {

    // check if the list is empty or has only one node.
    if (this->totalNodes == 0 || this->totalNodes == 1) return;

    // creating a current node pointer
    node<T>* current = this->head;
    // --> traversing the list to end.
    while (current != NULL) {
        // swapping the next and prev of each node.
        // storing the current->next.
        node<T>* temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        // traversing the list.
        current = current->prev;
    }
    // swapping the head and tail.
    node<T>* temp = this->head;
    this->head = this->tail;
    this->tail = temp;
}

// !free list
template <class T>
void DoublyLinkedList<T>::freeList() {

    if (this->totalNodes == 0) return;

    while (this->head != NULL) {
        node<T>* nextNode = this->head->next;
        delete this->head;
        this->head = nextNode;
    }
    this->head = NULL;
    this->tail = NULL;
    this->totalNodes = 0;
    this->is_list_returned_from_concatenation_overload = false;
}

// != operator overloading
template <class T>
void DoublyLinkedList<T>::operator=(DoublyLinkedList<T> list) {

    freeList();

    // check if the list has no nodes.
    if (list.totalNodes == 0) return;

    // check if the list is returned from concatenation
    // linkedList  <-- list1 + list2
    // updating this->head to the head of list
    // and this->tail to the tail of list
    // and this->totalNodes to the total number of node in list.
    if (list.is_list_returned_from_concatenation_overload == true) {
        this->head = list.head;
        this->tail = list.tail;
        this->totalNodes = list.totalNodes;
        list.is_list_returned_from_concatenation_overload = false;
        return;
    }
    // if there are one or more nodes in the list.
    // push each in (this).
    node<T>* current = list.head;
    while (current != NULL) {
        push(current->data);
        current = current->next;
    }
}

// !concatenation of two DoublyLinkedLists
template <class T>
DoublyLinkedList<T> DoublyLinkedList<T>:: operator+(DoublyLinkedList<T> list) {

    // create the list to be returned.
    DoublyLinkedList<T> result;

    // 0 === 0
    // 0 === A
    // A === 0
    // A === A

    // for 0 === 0 and 0 === A
    if (this->totalNodes == 0) {
        result = list;
        result.is_list_returned_from_concatenation_overload = true;
        return result;
    }

    // for A === 0 and A === A
    // atleast (this) is not empty, so copy (this)
    // then check for list.totalNodes
    result = *(this);

    if (list.totalNodes == 0) {
        result.is_list_returned_from_concatenation_overload = true;
        return result;
    }

    // else push all nodes of list to result.
    node<T>* current = list.head;
    while (current != NULL) {
        result.push(current->data);
        current = current->next;
    }
    result.is_list_returned_from_concatenation_overload = true;
    return result;
}