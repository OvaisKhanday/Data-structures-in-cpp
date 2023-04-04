// Perform stack_obj operations using Array implementation and use Template.

#include <iostream>
// #define MAX_STK 10
using namespace std;

template <class T>
class stack_obj {

    int max_size;
    int tos;
    T* stk;

public:
    stack_obj(int max_size) {
        this->max_size = max_size;
        this->tos = -1;
        this->stk = new T[max_size];
    }
    ~stack_obj() {
        delete[] this->stk;
        cout << "obj destructed\n";
    }
    bool isEmpty();
    bool isFull();

    void push(T);
    T peek();
    void pop();

    // I had added this function just for debugging purpose.
    void displayStack();

};

int main() {
    stack_obj<int> s1(10);
    s1.peek();
    s1.pop();
    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.push(40);
    s1.push(50);
    cout << "Peeking in stack_obj :" << s1.peek() << endl;
    s1.displayStack();
    s1.pop();
    s1.pop();
    s1.pop();
    s1.displayStack();
    s1.push(30);
    s1.push(40);
    s1.push(60);
    s1.push(70);
    s1.push(80);
    s1.push(90);
    s1.push(100);
    s1.push(110);
    s1.push(120);
    s1.displayStack();

    return 0;
}


// !isEmpty
template <class T>
bool stack_obj<T>::isEmpty() {
    if (this->tos == -1) return true;
    return false;
}

// !isFull
template <class T>
bool stack_obj<T>::isFull() {
    if (this->tos + 1 >= this->max_size) return true;
    return false;
}

// !push
template <class T>
void stack_obj<T>::push(T data) {

    if (this->isFull()) {
        cout << "STACK OVERFLOW!" << endl;
        return;
    }

    (this->tos)++;
    this->stk[tos] = data;
}

// !pop
template <class T>
void stack_obj<T>::pop() {

    if (this->isEmpty()) {
        cout << "STACK UNDERFLOW!" << endl;
        return;
    }

    (this->tos)--;
}

// !peek
template <class T>
T stack_obj<T>::peek() {

    if (this->isEmpty()) {
        cout << "STACK IS EMPTY!" << endl;
        return (char)0;
    }

    return this->stk[tos];
}

// !displayStack
template <class T>
void stack_obj<T>::displayStack() {
    if (this->isEmpty()) {
        cout << "STACK IS EMPTY!" << endl;
        return;
    }

    cout << this->stk[0];
    for (int i = 1; i <= tos; i++) {
        cout << ", " << this->stk[i];
    }
    cout << endl;
}