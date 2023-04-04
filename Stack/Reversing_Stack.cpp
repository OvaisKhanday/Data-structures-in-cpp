#include <iostream>
#include <stack>
#include <queue>
// #include "Stack_Linked_List_Implementation.h"
// #include "Queue_Linked_Implementation.h"
using namespace std;



template <class T>
stack<T> reverseStackUsingAnotherStack(stack<T>);

template <class T>
stack<T> reverseStackUsingQueue(stack<T>);

template <class T>
void printStack(stack<T> s) {
    cout << "TOS:";
    while (!s.empty()) {
        cout << " -> " << s.top();
        s.pop();
    }
    cout << endl;
}

int main() {

    stack<int> stack_obj;
    stack_obj.push(50);
    stack_obj.push(45);
    stack_obj.push(20);
    stack_obj.push(10);
    stack_obj.push(5);


    cout << "Reversing the stack_obj using another stack..." << endl;
    cout << "Before reverse the stack_obj is:\n";
    printStack(stack_obj);
    stack<int> result;
    result = reverseStackUsingAnotherStack(stack_obj);
    cout << "The reversed stack is: \n";
    printStack(result);


    cout << "\n####################################\n";

    cout << "Reversing the stack_obj using queue..." << endl;
    cout << "Before reverse the stack_obj is: \n";
    printStack(stack_obj);
    result = reverseStackUsingQueue(stack_obj);
    cout << "The reversed stack is: \n";
    printStack(result);

    return 0;
}


template <class T>
stack<T> reverseStackUsingAnotherStack(stack<T> stack_obj) {

    int sizeOfStack = stack_obj.size();
    if (sizeOfStack == 0 || sizeOfStack == 1) return stack_obj;

    stack<T> result;

    while (sizeOfStack-- != 0) {
        result.push(stack_obj.top());
        stack_obj.pop();
    }
    // result.displayStack();
    // stack_obj.tos = result.tos;
    return result;
}

template <class T>
stack<T> reverseStackUsingQueue(stack<T> stack_obj) {

    int sizeOfStack = stack_obj.size();
    int sizeOfQueue = sizeOfStack;
    if (sizeOfStack == 0 || sizeOfStack == 1) return stack_obj;

    queue<T> temp_queue;

    while (sizeOfStack-- != 0) {
        temp_queue.push(stack_obj.top());
        stack_obj.pop();
    }

    while (sizeOfQueue-- != 0) {
        stack_obj.push(temp_queue.front());
        temp_queue.pop();
    }

    return stack_obj;
}