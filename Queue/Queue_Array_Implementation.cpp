#include <iostream>
using namespace std;

template <class T>
class Queue {

    T* array;
    int max_size;
    int front;
    int rear;
    int count;
public:
    Queue(int max_size) {
        this->array = new T[max_size];
        this->max_size = max_size;
        this->front = -1;
        this->rear = -1;
        this->count = 0;
    }

    ~Queue() {
        delete[] array;
    }

    void enqueue(T);
    void dequeue();

    T peek();

    int queueSize();
    bool isEmpty();
    bool isFull();

    // for debugging purposes.
    void displayQueue();
};


int main() {
    Queue<int> q1(5);

    int break_loop = 1;
    cout << "1. enqueue\t2. dequeue\n3. display\t4. exit\n";
    while (break_loop) {
        int option = 0;
        cout << "Enter: [1,2,3,4]: ";
        while (!(cin >> option) || option < 1 || option > 4) {
            cin.clear();
            cin.ignore();
            cout << "Enter: [1,2,3,4]: ";
        }

        switch (option)
        {
        case 1:
            if (q1.isFull()) cout << "Queue is full\n";
            else {
                cout << "Enter data to be inserted: ";
                int data;
                while (!(cin >> data)) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Bad input, please re-enter: ";
                }
                q1.enqueue(data);
            }
            break;

        case 2:
            if (q1.isEmpty()) cout << "Queue is Empty\n";
            else cout << q1.peek() << " dequeued\n";
            q1.dequeue();
            break;

        case 3:
            q1.displayQueue();
            break;

        default:
            break_loop = 0;
            break;
        }
    }
    return 0;
}

// !ENQUEUE
template <class T>
void Queue<T>::enqueue(T enqueue_data) {

    if (this->isFull()) return;

    this->count++;

    if (this->rear == this->max_size - 1) {
        this->rear = 0;
        this->array[this->rear] = enqueue_data;
        return;
    }

    this->array[++this->rear] = enqueue_data;
}

// !DEQUEUE
template <class T>
void Queue<T>::dequeue() {

    if (this->isEmpty()) {
        throw std::runtime_error("EMPTY QUEUE\n");
        return;
    }

    this->count--;

    if (this->front == this->max_size - 1) this->front = 0;
    else this->front++;
}

// !peek
template <class T>
T Queue<T>::peek() {
    if (this->isEmpty()) {
        throw std::runtime_error("EMPTY QUEUE\n");
        return -1;
    }
    if (this->front == this->max_size - 1) return this->array[0];
    return this->array[this->front + 1];
}

// !QUEUE COUNT
template <class T>
int Queue<T>::queueSize() {
    return this->count;
}

// !IS EMPTY
template <class T>
bool Queue<T>::isEmpty() {
    return this->count == 0;
}

// !IS FULL
template <class T>
bool Queue<T>::isFull() {
    return this->count == this->max_size;
}

// !DISPLAY QUEUE
template <class T>
void Queue<T>::displayQueue() {

    if (this->max_size <= 0) return;

    cout << "\n--------------------------------------------\n";
    cout << this->array[0];
    for (int i = 1; i < this->max_size; i++) {
        cout << ", " << this->array[i];
    }
    cout << endl;
    cout << "Peek: " << this->peek() << endl;
    cout << "Front is at: " << this->front << endl;
    cout << "Rear is at: " << this->rear << endl;
    cout << "Total count is: " << this->count << endl;
    cout << "Max size is: " << this->max_size << endl;
    cout << "isEmpty: " << this->isEmpty() << endl;
    cout << "isFull: " << this->isFull() << endl;
    cout << "--------------------------------------------\n";
}