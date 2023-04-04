// linked list in c++

#include <iostream>
#include <stdlib.h>
using namespace std;

// Node
class node {
public:
    int data;
    node* next;

    // constructor for default value of 0
    node() {
        data = 0;
        next = NULL;
    }

    // parametrized constructor for given value of data
    node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// Linked List

class linkedList {
public:
    node* head;
    node* tail;
    int totalNodes;
    linkedList() {
        head = NULL;
        tail = NULL;
        totalNodes = 0;
    }

    void insertNode(int);
    void insertNodeFront(int);
    void insertNodeAt(int, int);
    bool searchList(int);
    void printList();
    void deleteNode();
    void deleteNode(int);
    void reverseList();
    linkedList concatList(linkedList);
    void operator = (linkedList);
    // res = list1;
    linkedList operator + (linkedList);
    // res = list1 + list2;

private:
    void copyList(linkedList);

};

int main() {
    linkedList list1;
    linkedList list2;

    list2.insertNode(10);
    list2.insertNode(20);
    list2.insertNode(30);
    list2.insertNode(40);
    list2.insertNode(50);


    cout << "I : insert node at end" << endl;
    cout << "F : insert node at front" << endl;
    cout << "A : insert node at location" << endl;
    cout << "S : search node in list" << endl;
    cout << "P : print list" << endl;
    cout << "D : delete at end" << endl;
    cout << "X : delete node at location" << endl;
    cout << "R : reverse list" << endl;
    cout << "+ : concat two list" << endl;

    while (1) {
        char input = ' ';
        cout << endl << "Enter : ";
        cin >> input;
        int data = 0;
        int location = 0;
        switch (input)
        {
        case 'I':
            cout << "Enter data for node: ";
            cin >> data;
            list1.insertNode(data);
            break;
        case 'F':
            cout << "Enter data for node: ";
            cin >> data;
            list1.insertNodeFront(data);
            break;
        case 'A':
            cout << "Enter data for node: ";
            cin >> data;
            cout << "Enter location for insertion: ";
            cin >> location;
            list1.insertNodeAt(data, location);
            break;
        case 'S':
            cout << "What you want to search in list: ";
            cin >> data;
            list1.searchList(data) ? cout << "found\n" : cout << "not found\n";
            break;
        case 'P':
            list1.printList();
            break;
        case 'D':
            list1.deleteNode();
            list1.printList();
            break;
        case 'X':
            cout << "Location where you want to delete: ";
            cin >> location;
            list1.deleteNode(location);
            list1.printList();
            break;
        case 'R':
            list1.reverseList();
            list1.printList();
            break;
        case '+':
            cout << "The second list is : " << endl;
            list2.printList();
            list1 = list1 + list2;
            cout << "After concatenation: " << endl;
            list1.printList();
            break;
        default:
            cout << "##### TRY AGAIN ####\n";
            break;
        }
    }

    delete list1.head;
    delete list2.head;

    return 0;
}

// !adding a node
void linkedList::insertNode(int data) {
    // creating new node
    node* newNode = new node(data);
    if (newNode == NULL) return;

    // adding node to head if head was previously empty
    if (head == NULL) {
        head = newNode;
        // there is only a node in the list then tail is also
        // addressing the same node to which head is addressing.
        tail = head;
        // incrementing the count of nodes
        totalNodes++;
        return;
    }
    // adding node to the tail 
    tail->next = newNode;

    // updatting tail
    tail = newNode;

    // incrementing the count of nodes
    totalNodes++;

    // // adding node to tail if head
    // node* temp = head;
    // while (temp->next != NULL) temp = temp->next;

    // // assigning newNode location to temp->next
    // temp->next = newNode;

    // // saving the tail of list
    // this->tail = newNode;
}

// !insert node at front of list
void linkedList::insertNodeFront(int data) {
    node* newNode = new node(data);
    if (newNode == NULL)return;
    newNode->next = this->head;
    this->head = newNode;
    totalNodes++;
}

// !insert node at specified index
void linkedList::insertNodeAt(int data, int index) {

    // return from function if index is negative or zero
    if (index <= 0)return;

    // if total nodes are less than the index
    if (index > totalNodes + 1)return;

    // if index == 1 and total nodes == 0
    if (index == 1 && totalNodes == 0) {
        insertNode(data);
        return;
    }

    // if index == 1 it means that node to be inserted will be in front.
    if (index == 1) {
        insertNodeFront(data);
        return;
    }

    // if index == totalNodes+1 means node to be inserted will be at end.
    if (index == totalNodes + 1) {
        insertNode(data);
        return;
    }

    node* current = head;
    node* newNode = new node(data);
    if (newNode == NULL) return;
    while (--index != 1) current = current->next;
    newNode->next = current->next;
    current->next = newNode;
    totalNodes++;
    return;
}
// !printing a list
void linkedList::printList() {
    // check if the list is empty
    if (head == NULL) {
        cout << "List is Empty" << endl;
        return;
    }
    // if list is not empty then
    // copy the address of head to temp
    // traverse through all next values
    // until you hit NULL
    cout << "head -> ";
    for (node* temp = head; temp != NULL; temp = temp->next) {
        cout << " " << temp->data << " -> ";
    }
    cout << "NULL" << endl;
    return;
}

// !search in list
bool linkedList::searchList(int data) {
    // check if the list is empty
    if (head == NULL) {
        // cout << "List is Empty" << endl;
        return false;
    }

    // traverse through all next values
    // and see if the data in each node
    // matches data parameter of function
    for (node* temp = head; temp != NULL; temp = temp->next) {
        if (temp->data == data) return true;
    }
    return false;
}

// !reversing a list
void linkedList::reverseList() {

    // check if the list has one or no nodes
    if (head == NULL || head->next == NULL) return;

    // reversing the list
    // storing the tail of list
    tail = head;
    node* prev = NULL;
    node* current = head;
    while (current != NULL) {
        node* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
        // printList();
        //      N          1           3          5          8            N
        //    prev        current     next
        //                prev        current    next
        //                            prev       current     next
        //                                       prev        current     next
    }
    head = prev;
}

// !deleting a node
void linkedList::deleteNode(int index) {

    // check for positive value and zero of index
    if (index <= 0) return;

    // return if the totalNodes are less than index asked of
    if (index > totalNodes) return;

    // check if the list is empty
    if (head == NULL) return;

    // if the first node is to be deleted
    if (index == 1) {
        // if there is only one node in the list
        // then make the head = NULL;
        // else if there are more than 1 nodes in the list
        // then make the head = head->next;
        int count = 0;
        node* temp = head;
        while (temp != NULL) {
            if (++count == 2)  break;
            temp = temp->next;
        }
        if (count == 1) {
            delete head;
            head = NULL;
            tail = NULL;
        } else if (count == 2) {
            head = head->next;
        }
        totalNodes--;
        return;
    }

    // check if the index is within the range of list
    node* current = head;
    node* prev = NULL;
    int count = 0;
    while (current != NULL) {
        if (++count == index)break;
        prev = current;
        current = current->next;
    }
    // if (count < index) return;
    prev->next = current->next;
    if (index == totalNodes) tail = prev;
    totalNodes--;
    return;
}

// !delete last node
void linkedList::deleteNode() {
    deleteNode(totalNodes);
}

// !concatanation of two linked lists
linkedList linkedList::concatList(linkedList list) {

    // result list
    linkedList result;

    // if this.list is empty
    if (this->head == NULL) {
        // copy list = op overload
        result = list;
        return result;
    }

    // if list2 is Empty
    if (list.head == NULL) {
        result.copyList(*(this));
        return result;
    }

    // both lists are not NULL
    // copy first list to result
    result.copyList(*(this));
    // append second list to the tail of result
    result.tail->next = list.head;
    // changing the tail of result to the tail of second list
    result.tail = list.tail;
    // totalNodes will be sum of nodes of both;
    result.totalNodes = this->totalNodes + list.totalNodes;
    return result;
}

// !concatenation of two lists with operator overloading
linkedList linkedList::operator +(linkedList list) {
    return concatList(list);
}

// !private
// !copy list
void linkedList::copyList(linkedList list) {
    // traversing through whole list and find the data 
    // use insertNode function to insert that node to
    // the list that called the function.
    delete this->head;
    this->head = NULL;
    this->tail = list.tail;
    while (list.head != NULL) {
        insertNode(list.head->data);
        list.head = list.head->next;
    }
    this->totalNodes = list.totalNodes;
}

// !operator overloading = for concatenation of lists
void linkedList::operator = (linkedList list) {
    copyList(list);
}
// KHANDAY OVAIS