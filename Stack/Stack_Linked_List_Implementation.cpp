// Perform stack_obj operations using Linked List implementation.
// (optional--and use Template)

#include <iostream>
using namespace std;


template <class T>
class node {
public:
    T data;
    node* down;

    node() {
        this->data = 0;
        this->down = NULL;
    }

    node(T data) {
        this->data = data;
        this->down = NULL;
    }
};

template <class T>
class stack_obj {
    int stack_size;
    node<T>* tos;
    bool isEmpty();
    void freeStack();
    void copyStack(node<T>*);
public:
    stack_obj() {
        this->stack_size = 0;
        this->tos = NULL;
    }

    ~stack_obj() {
        this->freeStack();
    }


    void push(T);
    void pop();
    void operator=(stack_obj<T>);
    T peek();
    void displayStack();
    int getStackSize();
};


int main() {
    stack_obj<int> s1;

    cout << "--------STACK OPERATIONS--------" << endl;
    cout << "1. push" << endl;
    cout << "2. pop" << endl;
    cout << "3. peek" << endl;
    cout << "4. size of stack_obj" << endl;
    cout << "0. Quit" << endl;
    int input = 4;

    while (input) {
        cout << "Enter Option [1,2,3,4,0]: ";
        while (!(cin >> input) || input < 0 || input > 4) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, Enter either [1,2,3,4,0]: ";
        }
        switch (input)
        {
        case 1:
            cout << "Enter data to be pushed on stack_obj: ";
            int data;
            while (!(cin >> data)) {
                cin.clear();
                cin.ignore(data, '\n');
                cout << "Bad input, please re-enter: ";
            }
            s1.push(data);
            break;

        case 2:
            s1.pop();
            cout << "Item popped" << endl;
            break;

        case 3:
            cout << "Peeking:->  " << s1.peek() << endl;
            break;

        case 4:
            cout << "The size of stack_obj is " << s1.getStackSize() << endl;
            break;
        case 0:
            input = 0;
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }

    return 0;
}

//!is emtpy
template <class T>
bool stack_obj<T>::isEmpty() {
    if (this->tos == NULL) return true;
    return false;
}

// !get stack_obj size
template <class T>
int stack_obj<T>::getStackSize() {
    return this->stack_size;
}

//!push stack_obj
template <class T>
void stack_obj<T>::push(T push_data) {

    node<T>* newNode = new node<T>(push_data);
    if (newNode == NULL) return;


    newNode->down = this->tos;
    this->tos = newNode;
    this->stack_size++;
}

//!pop stack_obj
template <class T>
void stack_obj<T>::pop() {

    if (this->isEmpty()) {
        cout << endl << "STACK UNDERFLOW!" << endl;
        return;
    }

    node<T>* current_tos = this->tos;
    this->tos = this->tos->down;
    delete current_tos;
    this->stack_size--;
}

//!peek stack_obj
template <class T>
T stack_obj<T>::peek() {

    if (this->isEmpty()) {
        cout << "STACK IS EMPTY! ";
        return (int)0;
    }

    return this->tos->data;
}

//!free stack_obj
template <class T>
void stack_obj<T>::freeStack() {

    if (this->isEmpty()) return;

    node<T>* current_tos = this->tos;
    while (current_tos != NULL) {
        this->tos = this->tos->down;
        delete current_tos;
        current_tos = this->tos;
    }
    this->stack_size = 0;

}


template <class T>
void stack_obj<T>::operator=(stack_obj<T> stack_obj) {

    this->freeStack();
    if (stack_obj.stack_size == 0) return;

    node<T>* current = stack_obj.tos;
    this->copyStack(current);
}

template <class T>
void stack_obj<T>::copyStack(node<T>* current) {
    if (current == NULL) return;
    this->copyStack(current->down);
    this->push(current->data);
}


template <class T>
void stack_obj<T>::displayStack() {

    if (this->getStackSize() == 0) return;

    cout << "\n----------------------------------\n";
    cout << "TOS:-> " << this->peek();

    node<T>* current = this->tos->down;
    while (current != NULL) {
        cout << " -> " << current->data;
        current = current->down;
    }
    cout << "\n----------------------------------\n";
}