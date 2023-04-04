#include <iostream>
using namespace std;


template <class T>
class Element {
public:
    T data;
    int priority;

    // Element(T data, int priority) {
    //     this->data = data;
    //     this->priority = priority;
    // }
};

template <class T>
class PQueue {
    Element<T>* array;
    int min_priority;
    int max_size;
    int count;
    int returnIndexOfMaxPriority();
public:
    PQueue(int max_size) {
        this->max_size = max_size;
        this->min_priority = INT_MIN;
        this->count = 0;
        this->array = new Element<T>[max_size];
    }
    ~PQueue() {
        delete[] array;
    }

    void push(T, int);

    void pop();
    T peek();
    int getSize();

    bool isEmpty();
    bool isFull();

    void displayQueue();
};

int main() {
    PQueue<int> queue(5);
    int break_loop = 1;
    cout << "================================\n";
    cout << "1. push\t2. pop\n3. peek\t4. display\n0. exit\n";
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
            cout << "Item with highest priority popped\n";
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
    if (this->isFull()) {
        cout << "Queue is full\n";
        return;
    }
    this->array[count].data = push_data;
    this->array[count].priority = push_priority;
    this->count++;
}

template <class T>
void PQueue<T>::pop() {
    if (this->isEmpty()) return;

    int maxPriorityIndex = this->returnIndexOfMaxPriority();

    for (int i = maxPriorityIndex; i < this->count - 1; i++) {
        this->array[i].data = this->array[i + 1].data;
        this->array[i].priority = this->array[i + 1].priority;
    }
    this->count--;
}

template <class T>
T PQueue<T>::peek() {
    int maxPriorityIndex = this->returnIndexOfMaxPriority();

    if (maxPriorityIndex == -1) return (int)-1;

    return this->array[maxPriorityIndex].data;
}

template <class T>
int PQueue<T>::returnIndexOfMaxPriority() {
    if (this->isEmpty()) {
        cout << "Queue is Empty!";
        return -1;
    }

    int index = -1;
    int max_priority = this->min_priority;
    for (int i = 0; i < this->count; i++) {
        if (this->array[i].priority > max_priority) {
            max_priority = this->array[i].priority;
            index = i;
        }
    }

    return index;
}


template <class T>
bool PQueue<T>::isFull() {
    return this->count == this->max_size;
}

template <class T>
bool PQueue<T>::isEmpty() {
    return this->count == 0;
}

template <class T>
int PQueue<T>::getSize() {
    return this->count;
}

template <class T>
void PQueue<T>::displayQueue() {

    if (isEmpty()) {
        cout << "Empty queue\n";
        return;
    }

    cout << "\n--------------------------------\n";
    for (int i = 0; i < this->count; i++) {
        cout << this->array[i].data << "(" << this->array[i].priority << "), ";
    }
    cout << endl;

    cout << "Peek is: " << this->peek() << endl;
    cout << "isFull: " << this->isFull() << endl;
    cout << "isEmpty: " << this->isEmpty() << endl;
    cout << "getSize: " << this->getSize() << endl;
    cout << "--------------------------------\n";
}