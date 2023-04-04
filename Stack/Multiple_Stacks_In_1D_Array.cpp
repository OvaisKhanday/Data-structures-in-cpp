// * The idea is to start two stacks from two extreme corners of arr[].
// * stack1 starts from the leftmost element, the first element in stack1
// * is pushed at index 0. The stack2 starts from the rightmost corner,
// * the first element in stack2 is pushed at index(n - 1).Both stacks
// * grow(or shrink) in opposite direction

#include <iostream>
// #include <stack>
using namespace std;

class Stack {

    int max_size;
    int tos1;
    int tos2;
    int* stack;

public:
    Stack(int max_size) {
        this->max_size = max_size;
        stack = new int[max_size];
        this->tos1 = -1;
        this->tos2 = max_size;
    }
    ~Stack() {
        delete[] stack;
    }

    void push1(int);
    void push2(int);

    void pop1();
    void pop2();

    int peek1();
    int peek2();

    bool isEmpty1();
    bool isEmpty2();

    bool isFull();

    // for debugging purpose I'm gonna display the whole array.
    void displayStack();
    void displayStack1();
    void displayStack2();

};
int main() {

    Stack s1(10);

    cout << "1. push1\t2. push2\n3. pop1\t\t4. pop2\n5. display\t0. exit\n";
    cout << "The size of stack is 10\n";
    bool run_loop = true;
    while (run_loop) {
        int input = 6;
        cout << "Enter [1,2,3,4,5,0]: ";
        while (!(cin >> input) || input < 0 || input > 5) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter [1,2,3,4,5,0]: ";
        }

        switch (input)
        {
        case 1:
            if (s1.isFull()) {
                cout << "Stack became full\n";
            } else {
                cout << "Enter stack1 data: ";
                int push_data;
                while (!(cin >> push_data)) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Enter again: ";
                }
                s1.push1(push_data);
            }
            break;

        case 2:
            if (s1.isFull()) {
                cout << "Stack became full\n";
            } else {
                cout << "Enter stack2 data: ";
                int push_data;
                while (!(cin >> push_data)) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Enter again: ";
                }
                s1.push2(push_data);
                break;
            }
        case 3:
            if (s1.isEmpty1()) {
                cout << "Empty stack1\n";
            } else {
                cout << s1.peek1() << " Popped\n";
                s1.pop1();
            }
            break;
        case 4:
            if (s1.isEmpty2()) {
                cout << "Empty stack2\n";
            } else {
                cout << s1.peek2() << " Popped\n";
                s1.pop2();
            }
            break;

        case 5:
            if (s1.isEmpty1() && s1.isEmpty2()) {
                cout << "Stacks are empty!\n";
            } else {
                cout << "\n===========================\n";
                cout << "Stack 1: ";
                if (s1.isEmpty1()) {
                    cout << "EMPTY!\n";
                } else
                    s1.displayStack1();

                cout << "Stack 2: ";
                if (s1.isEmpty2()) {
                    cout << "EMPTY!\n";
                } else
                    s1.displayStack2();
                cout << "Whole stack: ";
                s1.displayStack();
                cout << "===========================\n";
            }
            break;

        default:
            run_loop = false;
            break;
        }
    }
    return 0;
}

// !pushing in the first Stack of array.
void Stack::push1(int push_data) {

    if (this->isFull()) return;
    // STACK OVERFLOW.

    this->tos1++;
    this->stack[tos1] = push_data;
}

// !pushing in the second Stack of array.
void Stack::push2(int push_data) {

    if (this->isFull()) return;
    // STACK OVERFLOW.

    this->tos2--;
    this->stack[tos2] = push_data;
}

// !deleting from the first Stack of array
void Stack::pop1() {

    if (this->isEmpty1()) return;
    // STACK UNDERFLOW.

    this->tos1--;
}

// !deleting from the second Stack of array
void Stack::pop2() {

    if (this->isEmpty2()) return;
    // STACK UNDERFLOW.

    this->tos2++;
}

// !getting the top value of the first Stack.
int Stack::peek1() {

    if (this->isEmpty1()) return (char)0;

    return this->stack[this->tos1];
}

// !getting the top value of the second Stack
int Stack::peek2() {

    if (this->isEmpty2()) return (char)0;

    return this->stack[this->tos2];
}

// !printing the whole array for debugging purposes
void Stack::displayStack() {

    if (this->isEmpty1() && this->isEmpty2()) return;
    cout << this->stack[0];
    for (int i = 1; i < this->max_size; i++) {
        cout << ", " << this->stack[i];
    }
    cout << endl;
}
void Stack::displayStack1() {
    if (this->isEmpty1()) return;
    cout << this->stack[0];
    for (int i = 1; i <= this->tos1; i++) {
        cout << ", " << this->stack[i];
    }
    cout << endl;
}
void Stack::displayStack2() {
    if (this->isEmpty2()) return;
    cout << this->stack[this->max_size - 1];
    for (int i = this->max_size - 2; i >= this->tos2; i--) {
        cout << ", " << this->stack[i];
    }
    cout << endl;
}

// !is the Stack full
bool Stack::isFull() {

    // if the tos of two virtual stacks are just one after another,
    // then we can say the Stack is full.
    if (this->tos1 + 1 == this->tos2) return true;
    return false;

}

// ! is there any element in the first Stack
bool Stack::isEmpty1() {

    if (this->tos1 == -1) return true;
    return false;
}

// !is there any element in the second Stack
bool Stack::isEmpty2() {

    if (this->tos2 == this->max_size) return true;
    return false;
}