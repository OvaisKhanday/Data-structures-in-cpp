#include <iostream>
using namespace std;

template <class T>
class linkedList {
public:
    int toa;
    int size;
    T* list;
    linkedList() {
        this->toa = -1;
        this->size = 0;
        // cout << "default constructor called" << endl;
    }
    linkedList(int size) {
        this->list = new T[size];
        this->toa = -1;
        this->size = size;
    }

    bool push(T);
    bool pop();
    bool searchItem(T);
    bool reverse();
    void printList();
    // linkedList operator = (linkedList);
    void operator = (linkedList);
    // linkedList<T> operator = (linkedList);
    linkedList operator + (linkedList);
    // void copyList(linkedList);

private:
    // copies the list(parameter) to the caller
    void copyList(linkedList);
};

int main() {

    linkedList<int> list1(5);
    list1.push(10);
    list1.push(20);
    list1.push(30);
    list1.push(40);
    list1.push(50);
    list1.push(60);

    linkedList<int> list2(3);
    list2.push(1);
    list2.push(2);
    list2.push(3);

    linkedList<int> list3;
    // list3 = list1;

    list3 = list1 + list2;
    list3.printList();

    linkedList<int> list4 = list2 + list3;
    list4.printList();


    delete[] list1.list;
    delete[] list2.list;
    delete[] list3.list;
    delete[] list4.list;
    return 0;
}

// !Add element to list
template <class T>
bool linkedList<T>::push(T item) {

    // check if the list if full
    if ((this->toa) + 1 >= this->size) return false;

    // far now it is to be meant that 
    // we can add the item in the array
    (this->toa)++;
    this->list[toa] = item;
    return true;
}

// !print list
template <class T>
void linkedList<T>::printList() {

    // check if the list is empty
    if (this->toa == -1) return;

    // else printing till we hit tos
    cout << "Head: -> ";
    for (int i = 0; i <= (this->toa); i++) {
        cout << this->list[i] << " -> ";
    }
    cout << ":Tail" << endl;
}

// !delete last element from list
template <class T>
bool linkedList<T>::pop() {

    // check if the list is empty
    if (this->toa == -1) return false;

    // else toa--;
    (this->toa)--;
    return true;
}

// !Search item in list
template <class T>
bool linkedList<T>::searchItem(T item) {

    // check if the list is empty
    if (this->toa == -1) return false;

    // else traverse through list
    for (int i = 0; i <= this->toa; i++) {
        if (this->list[i] == item) return true;
    }
    return false;
}

// !copy list using = operator
template <class T>
void linkedList<T>::operator = (linkedList list1) {

    // delete all content of this. if there exists.
    if (this->size > 0) {
        delete[] this->list;
        this->toa = -1;
        this->size = 0;
    }

    // return if the list1 is empty.
    if (list1.toa == -1) return;

    // else if the list is not empty
    // allocate the memory for the new list
    // of size the same of as of list1.size.
    this->list = new T[list1.size];

    // and copy the content.
    copyList(list1);

    // return *this;

}

// !copy lists
template <class T>
void linkedList<T>::copyList(linkedList<T> list1) {

    // copy list items from list1 to this
    for (int i = 0; i <= list1.toa; i++) {
        this->list[i] = list1.list[i];
    }
    this->size = list1.size;
    this->toa = list1.toa;
}

// !Concat list
template <class T>
linkedList<T> linkedList<T>::operator + (linkedList<T> list1) {

    linkedList<T> result;

    // if both the lists are empty.
    // -1 === -1
    if (this->toa == -1 && list1.toa == -1) return result;

    // -1 === A
    if (this->toa == -1) {
        result = list1;
        return result;
    }

    // A === -1
    if (this->toa > -1 && list1.toa == -1) {
        result = *(this);
        return result;
    }

    // A === A
    int total_size_of_result = this->size + list1.size;
    result.list = new T[total_size_of_result];
    // --copy items of this list
    for (int i = 0; i <= this->toa; i++) {
        result.list[i] = this->list[i];
    }
    result.toa = this->toa;
    // copy items of list1 list.
    for (int i = 0; i <= list1.toa; i++) {
        result.list[++(result.toa)] = list1.list[i];
    }
    result.size = total_size_of_result;
    return result;
}