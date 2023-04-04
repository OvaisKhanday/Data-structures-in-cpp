// Deque or Double Ended Queue is a generalized version of Queue
// data structure that allows insert and delete at both ends

#include <iostream>
using namespace std;

template <class T>
class Dequeue {
    int front;
    int rear;
    int count;
    int max_size;
    T* array;
public:
    Dequeue(int max_size) {
        this->front = -1;
        this->rear = -1;
        this->count = 0;
        this->max_size = max_size;
        this->array = new T[max_size];
    }

    ~Dequeue() {
        delete[] array;
    }

    bool isEmpty();
    bool isFull();

    void insertFront(T);
    void insertRear(T);

    void deleteFirst();
    void deleteLast();

    T getFirst();
    T getLast();

    int getSize();

    // for debugging purposes.
    void displayQueue();
};

int main() {
    Dequeue<int> d1(5);

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
            d1.insertFront(data);
            break;

        case 2:
            cout << "Enter data to be inserted on Rear: ";
            // int data;
            while (!(cin >> data)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, please re-enter: ";
            }
            d1.insertRear(data);
            break;

        case 3:
            d1.deleteFirst();
            cout << "Deleted from Front: " << endl;
            break;

        case 4:
            d1.deleteLast();
            cout << "Deleted from Rear: " << endl;
            break;

        case 5:
            d1.displayQueue();
            break;

        default:
            break_loop = 0;
            break;
        }
    }
    return 0;
}

// !is full
template <class T>
bool Dequeue<T>::isFull() {

    // if ((this->front == -1 && this->rear == max_size - 1) || this->rear + 1 == this->front) return true;
    if (this->count == max_size) return true;
    return false;
}

// !is empty
template <class T>
bool Dequeue<T>::isEmpty() {

    // if ((this->front == -1 && this->rear == -1) || this->front == this->rear) return true;
    if (this->count == 0) return true;
    return false;
}

// !insert first
template <class T>
void Dequeue<T>::insertFront(T insert_data) {

    if (this->isFull()) {
        cout << "QUEUE IS FULL" << endl;
        return;
    }

    this->count++;
    if (this->front == -1 && this->rear == -1) {
        this->front = this->rear = 0;
        this->array[this->front] = insert_data;
        return;
    }

    if (this->front == 0) {
        this->front = this->max_size - 1;
        this->array[this->front] = insert_data;
        return;
    }

    this->array[--this->front] = insert_data;
}

// !insert last
template <class T>
void Dequeue<T>::insertRear(T insert_data) {

    if (this->isFull()) {
        cout << "QUEUE IS FULL" << endl;
        return;
    }

    this->count++;

    if (this->front == -1 && this->rear == -1) {
        this->front = this->rear = 0;
        this->array[this->front] = insert_data;
        return;
    }

    if (this->rear == this->max_size - 1) {
        this->rear = 0;
        this->array[this->rear] = insert_data;
        return;
    }

    this->array[++this->rear] = insert_data;
}

// !delete first.
template <class T>
void Dequeue<T>::deleteFirst() {
    if (this->isEmpty()) return;

    this->count--;

    // this->array[this->front] = 0;  --Debugging purposes
    if (this->front == this->max_size - 1) this->front = 0;
    else this->front++;
}

// !delete last.
template <class T>
void Dequeue<T>::deleteLast() {
    if (this->isEmpty()) return;

    this->count--;

    // this->array[this->rear] = 0;  --Debugging purposes
    if (this->rear == 0) this->rear = this->max_size - 1;
    else this->rear--;
}

// !get first.
template <class T>
T Dequeue<T>::getFirst() {
    if (this->isEmpty()) {
        // throw std::runtime_error("Queue is empty!\n");
        cout << "Queue is empty! ";
        return (int)-1;
    }
    if (this->front == -1) return this->array[0];
    return this->array[this->front];
}

// !get last.
template <class T>
T Dequeue<T>::getLast() {
    if (this->isEmpty()) {
        // throw std::runtime_error("Queue is empty!\n");
        cout << "Queue is empty! ";
        return (int)-1;
    }

    if (this->rear == -1) return this->array[max_size - 1];
    return this->array[this->rear];
}
// !displayQueue
template <class T>
void Dequeue<T>::displayQueue() {

    cout << "\n--------------------------------------------------\n";
    cout << "Front: " << this->array[0];
    for (int i = 1; i < this->max_size;i++) {
        cout << ", " << this->array[i];
    }
    cout << endl;
    cout << "isEmpty: " << this->isEmpty() << endl;
    cout << "isFull: " << this->isFull() << endl;
    cout << "size: " << this->count << endl;
    cout << "Front[" << this->front << "]: " << this->getFirst() << endl;
    cout << "Rear[" << this->rear << "]: " << this->getLast() << endl;
    cout << "--------------------------------------------------\n";
}

// !get size
template <class T>
int Dequeue<T>::getSize() {
    return this->count;
}