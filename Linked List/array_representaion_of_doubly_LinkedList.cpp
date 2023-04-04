#include <iostream>
using namespace std;


template <class T>
class DoublyLinkedList_Array {
private:
    int toa;
    int size;
    T* array;

public:
    DoublyLinkedList_Array() {
        this->toa = -1;
        int size = 0;
    }

    DoublyLinkedList_Array(int size) {
        this->toa = -1;
        this->size = size < 0 ? 0 : size;
        array = new T[size];
    }

    void push(T);
    void push(int, T);
    T pop();
    T pop(int);
    bool searchList(T);
    void printList();
    void reverseList();
};
int main() {
    DoublyLinkedList_Array<int> list1(5);
    list1.push(1);
    list1.push(1);
    list1.push(1);
    list1.push(1);
    return 0;
}

// !pushing element in the list at the end.
template <class T>
void DoublyLinkedList_Array<T>::push(T data) {

    // checking if the list is full.
    if (this->toa + 1 == this->size) return;

    // incrementing the toa
    // adding the data in array.
    (this->toa)++;
    this->array[toa] = data;
}