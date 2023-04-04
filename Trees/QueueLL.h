// enQueue() This operation adds a new node after rear and moves rear to the next node.
// deQueue() This operation removes the front node and moves front to the next node.

#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class node {
public:
    T data;
    node<T>* next;

    node() {
        this->data = 0;
        this->next = NULL;
    }
    node(T data) {
        this->data = data;
        this->next = NULL;
    }
};


template <class T>
class Queue {
    node<T>* front;
    node<T>* rear;
    int total_nodes;
public:
    Queue() {
        this->front = NULL;
        this->rear = NULL;
        this->total_nodes = 0;
    }

    ~Queue() {
        freeQueue();
    }
    void freeQueue();

    void enqueue(T);
    T dequeue();

    T getFront();
    T getRear();
    bool isEmpty();

    // for debugging purposes
    void displayQueue();
    int getSize();

};

// !ENQUEUE
template <class T>
void Queue<T>::enqueue(T enqueue_data) {

    // create a node in the heap.
    node<T>* newNode = new node<T>(enqueue_data);
    // check if the memory is allocated or not.
    if (newNode == NULL) return;

    // see if the queue is empty
    if (this->isEmpty()) {
        // give both the rear and front the same new node.
        this->front = newNode;
        this->rear = newNode;
        // update the count of the queue.
        this->total_nodes = 1;
        return;
    }

    // if there is at least one element present in the queue.
    // make a link to the new node via next of rear node.
    this->rear->next = newNode;
    // update the rear node to the new node.
    this->rear = newNode;
    // update the count of total nodes.
    this->total_nodes++;
}

// !DEQUEUE
template <class T>
T Queue<T>::dequeue() {

    T return_data;
    if (this->isEmpty()) {
        // throw std::runtime_error("QUEUE IS EMPTY!\n");
        cout << "QUEUE IS EMPTY!";
        return return_data;
    }

    // in dequeue we will delete the front node.
    return_data = this->front->data;

    // if there is only one node present in the queue,
    // then we also have to set the rear to NULL.
    if (this->total_nodes == 1) {
        free(this->front);
        this->front = NULL;
        this->rear = NULL;
        this->total_nodes = 0;
        return return_data;
    }

    // if there are more than a node.
    // It means rear is pointing towards the distinct node from front.
    // we can use a temp pointer to point to the front,
    // and increment the front and thereafter delete the temp.
    node<T>* current = this->front;
    this->front = this->front->next;
    free(current);
    this->total_nodes--;
    return return_data;
}

// !FRONT NODE
template <class T>
T Queue<T>::getFront() {
    if (this->front == NULL) {
        // throw underflow_error("Queue is empty\n");
        cout << "QUEUE IS EMPTY!";
        return (int)-1;
    }

    return this->front->data;
}

// !REAR NODE
template <class T>
T Queue<T>::getRear() {
    if (this->rear == NULL) {
        // throw underflow_error("Queue is empty\n");
        cout << "QUEUE IS EMPTY!";
        return (int)-1;
    }

    return this->rear->data;
}

// !QUEUE SIZE
template <class T>
int Queue<T>::getSize() {
    return this->total_nodes;
}

// !DISPLAY QUEUE
template <class T>
void Queue<T>::displayQueue() {

    if (this->isEmpty()) {
        cout << "QUEUE IS EMPTY!" << endl;
        return;
    }

    node<T>* current = this->front->next;
    cout << "Front: -> " << this->front->data;
    while (current != NULL) {
        cout << " -> " << current->data;
        current = current->next;
    }
    cout << " -> :Rear\n";
}

// !IS EMPTY
template <class T>
bool Queue<T>::isEmpty() {
    if (this->rear == NULL) return true;
    return false;
}

// !FREE QUEUE
template <class T>
void Queue<T>::freeQueue() {

    if (this->isEmpty()) return;

    // create the temp pointer that stores the current node,
    // while the front node move forward.

    node<T>* current = this->front;
    while (current != NULL) {
        this->front = this->front->next;
        free(current);
        current = this->front;
    }
    this->total_nodes = 0;
    this->rear = NULL;
}