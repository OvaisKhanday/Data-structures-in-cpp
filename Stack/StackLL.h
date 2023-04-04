// Perform Stack operations using Linked List implementation.
// (optional--and use Template)
#pragma once
#ifndef STACKLL_H
#define STACKLL_H

#include <iostream>
using namespace std;


template <class T>
class node {
public:
    T data;
    node<T>* down;

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
class Stack {
public:
    int stack_size;
    node<T>* tos;

    Stack() {
        this->stack_size = 0;
        this->tos = NULL;
    }

    ~Stack() {
        this->freeStack();
    }


    bool isEmpty();
    void freeStack();
    void push(T);
    void pop();
    T peek();
    void operator=(Stack<T>);
    void copyStack(node<T>*);
    int getStackSize();

    void displayStack();
};

//!is emtpy
template <class T>
bool Stack<T>::isEmpty() {
    if (this->tos == NULL) return true;
    return false;
}

// !get Stack size
template <class T>
int Stack<T>::getStackSize() {
    return this->stack_size;
}

//!push Stack
template <class T>
void Stack<T>::push(T push_data) {

    node<T>* newNode = new node<T>(push_data);
    if (newNode == NULL) return;


    newNode->down = this->tos;
    this->tos = newNode;
    this->stack_size++;
}

//!pop Stack
template <class T>
void Stack<T>::pop() {

    if (this->isEmpty()) {
        cout << endl << "STACK UNDERFLOW!" << endl;
        return;
    }

    node<T>* current_tos = this->tos;
    this->tos = this->tos->down;
    delete current_tos;
    this->stack_size--;
}

//!peek Stack
template <class T>
T Stack<T>::peek() {

    if (this->isEmpty()) {
        cout << "STACK IS EMPTY! ";
        return (int)0;
    }

    return this->tos->data;
}

//!free Stack
template <class T>
void Stack<T>::freeStack() {

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
void Stack<T>::displayStack() {

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

template <class T>
void Stack<T>::operator=(Stack<T> stack) {

    this->freeStack();
    if (stack.stack_size == 0) return;

    node<T>* current = stack.tos;
    this->copyStack(current);
}

template <class T>
void Stack<T>::copyStack(node<T>* current) {
    if (current == NULL) return;
    this->copyStack(current->down);
    this->push(current->data);
}

#endif // STACKLL_H