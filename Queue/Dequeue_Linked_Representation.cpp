#include <iostream>
using namespace std;

template <class T>
class node {
public:
    T data;
    node<T>* next;
    node<T>* prev;

    node() {
        this.data = 0;
        this->next = NULL;
        this->prev = NULL;
    }
    node(T data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

template <class T>
class Dequeue {
    node<T>* front;
    node<T>* rear;
    int total_nodes;
public:
    Dequeue() {
        this->front = NULL;
        this->rear = NULL;
        this->total_nodes = 0;
    }
    ~Dequeue() {
        this->freeQueue();
    }

    void freeQueue();

    void pushFront(T);
    void pushRear(T);

    void popFront();
    void popRear();

    bool isEmpty();

    T getFront();
    T getRear();

    void displayQueue();
};

int main() {

    Dequeue<int> queue;

    //******************************************************************************\\*
    int break_loop = 1;
    cout << "1. insertFront\t2. insertRear\n3. deleteFront\t4. deleteLast\n5. display\t0. exit\n";
    while (break_loop) {
        int option = 0;
        cout << "Enter: [0,1,2,3,4,5]: ";
        while (!(cin >> option) || option < 0 || option > 5) {
            cin.clear();
            cin.ignore();
            cout << "Enter: [0,1,2,3,4,5]: ";
        }

        switch (option)
        {
        case 1:
            cout << "Enter data to be inserted on Front: ";
            int data;
            while (!(cin >> data)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, please re-enter: ";
            }
            queue.pushFront(data);
            break;

        case 2:
            cout << "Enter data to be inserted on Rear: ";
            // int data;
            while (!(cin >> data)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, please re-enter: ";
            }
            queue.pushRear(data);
            break;

        case 3:
            queue.popFront();
            cout << "Deleted from Front: " << endl;
            break;

        case 4:
            queue.popRear();
            cout << "Deleted from Rear: " << endl;
            break;

        case 5:
            queue.displayQueue();
            break;

        default:
            break_loop = 0;
            break;
        }
    }
    //******************************************************************************\\*
    return 0;
}

template <class T>
void Dequeue<T>::pushFront(T push_data) {

    // creating the node.
    node<T>* newNode = new node<T>(push_data);
    if (newNode == NULL) return;

    if (this->total_nodes == 0) {
        this->front = newNode;
        this->rear = newNode;
        this->total_nodes = 1;
        return;
    }

    this->front->prev = newNode;
    newNode->next = this->front;
    this->front = newNode;
    this->total_nodes++;
}

template <class T>
void Dequeue<T>::pushRear(T push_data) {

    node<T>* newNode = new node<T>(push_data);
    if (newNode == NULL) return;

    if (this->total_nodes == 0) {
        this->front = newNode;
        this->rear = newNode;
        this->total_nodes = 1;
        return;
    }

    this->rear->next = newNode;
    newNode->prev = this->rear;
    this->rear = newNode;
    this->total_nodes++;
}

template <class T>
void Dequeue<T>::popFront() {
    if (this->isEmpty()) return;

    if (this->total_nodes == 1) {
        free(this->front);
        this->front = NULL;
        this->rear = NULL;
        this->total_nodes--;
        return;
    }

    node<T>* current = this->front;
    this->front = this->front->next;
    this->front->prev = NULL;
    this->total_nodes--;
    free(current);
}

template <class T>
void Dequeue<T>::popRear() {
    if (this->isEmpty()) return;

    if (this->total_nodes == 1) {
        free(this->front);
        this->front = NULL;
        this->rear = NULL;
        this->total_nodes--;
        return;
    }

    node<T>* current = this->rear;
    this->rear = this->rear->prev;
    this->rear->next = NULL;
    this->total_nodes--;
    free(current);
}


template <class T>
bool Dequeue<T>::isEmpty() {
    if (this->rear == NULL && this->front == NULL) return true;
    return false;
}

template <class T>
T Dequeue<T>::getFront() {

    if (this->isEmpty()) {
        cout << "Empty queue" << endl;
        return (int)1;
    }

    return this->front->data;
}

template <class T>
T Dequeue<T>::getRear() {

    if (this->isEmpty()) {
        cout << "Empty queue" << endl;
        return (int)1;
    }

    return this->rear->data;
}

template <class T>
void Dequeue<T>::freeQueue() {

    node<T>* current = this->front;
    while (current != NULL) {
        this->front = this->front->next;
        free(current);
        current = this->front;
    }
}

template <class T>
void Dequeue<T>::displayQueue() {

    if (this->total_nodes == 0) {
        cout << "EMPTY QUEUE!\n";
    } else {
        node<T>* current = this->front->next;
        cout << "Front: -> " << this->front->data;
        while (current != NULL) {
            cout << " -> " << current->data;
            current = current->next;
        }
        cout << " -> :Rear\n";
    }
}