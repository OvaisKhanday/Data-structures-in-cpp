#include <iostream>
using namespace std;


template <class T>
class node {
public:
    T data;
    int priority;
    node<T>* next;

    node(T data, int priority) {
        this->data = data;
        this->priority = priority;
        this->next = NULL;
    }
};

template <class T>
class PQueue {

    node<T>* head;
    int total_nodes;
public:
    PQueue() {
        this->total_nodes = 0;
        this->head = NULL;
    }

    ~PQueue() {
        this->freeQueue();
    }

    void freeQueue();

    void push(T, int);
    void pop();

    T peek();

    bool isEmpty();

    void displayQueue();
};

int main() {

    PQueue<int> queue;


    int break_loop = 1;
    cout << "================================\n";
    cout << "1. push\t\t2. pop\n3. peek\t\t4. display\n0. exit\n";
    cout << "================================\n";
    while (break_loop) {
        int input = 0;
        cout << "Enter: ";
        cin >> input;

        switch (input) {

        case 1:
            int data, pri;
            cout << "Enter data to push: ";
            cin >> data;
            cout << "Enter priority of " << data << ": ";
            cin >> pri;
            queue.push(data, pri);
            break;

        case 2:
            cout << queue.peek() << " popped\n";
            queue.pop();
            break;

        case 3:
            cout << queue.peek() << " is the element with highest priority\n";
            break;

        case 4:
            queue.displayQueue();
            break;

        case 0:
            break_loop = 0;
            break;

        default:
            cout << "Try again\n";
            break;
        }
    }




    return 0;
}

template <class T>
void PQueue<T>::push(T push_data, int push_priority) {

    node<T>* newNode = new node<T>(push_data, push_priority);
    if (newNode == NULL)return;

    this->total_nodes++;

    if (this->isEmpty()) {
        this->head = newNode;
        return;
    }

    node<T>* prev = NULL;
    node<T>* current = this->head;
    while (current != NULL && current->priority >= newNode->priority) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        newNode->next = this->head;
        this->head = newNode;
        return;
    }

    newNode->next = current;
    prev->next = newNode;
}

template <class T>
T PQueue<T>::peek() {
    if (this->isEmpty()) {
        cout << "Empty Queue\n";
        return (int)-1;
    }

    return this->head->data;
}

template <class T>
void PQueue<T>::pop() {

    if (this->isEmpty()) {
        cout << "Empty Queue\n";
        return;
    }

    node<T>* current = this->head;
    this->head = this->head->next;
    this->total_nodes--;
    free(current);
}


template <class T>
bool PQueue<T>::isEmpty() {
    return this->head == NULL;
}

template <class T>
void PQueue<T>::freeQueue() {

    node<T>* current = this->head;
    while (current != NULL) {
        this->head = this->head->next;
        free(current);
        current = this->head;
    }
}

template <class T>
void PQueue<T>::displayQueue() {

    cout << "\n---------------------------------------------\n";
    if (this->isEmpty()) {
        cout << "Empty Queue\n";
        cout << "---------------------------------------------\n";
        return;
    }

    cout << "Head: -> " << this->head->data << "(" << this->head->priority << ")";
    node<T>* current = this->head->next;
    while (current != NULL) {
        cout << " -> " << current->data << "(" << current->priority << ")";
        current = current->next;
    }
    cout << endl;
    cout << "Peek: -> " << this->peek() << endl;
    cout << "Total Nodes: -> " << this->total_nodes << endl;
    cout << "---------------------------------------------\n";
}