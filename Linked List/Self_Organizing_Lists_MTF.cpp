#include <iostream>
using namespace std;



class node {
public:
    int data;
    node* next;

    node() {
        this->data = 0;
        this->next = NULL;
    }
    node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

class LinkedList {
    void freeList();
    void createList();
public:
    node* head;
    node* tail;
    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->createList();
    }
    ~LinkedList() {
        freeList();
    }
    // if node is present then return the how many iterations it took,
    // to find the element else if the element is not present return 0;
    int searchList(int);
    void printList();
};


int main() {

    LinkedList l1;

    int input = 0;
    while (1) {
        int search_data = 0;
        cout << "Enter what you want to search: ";
        while (!(cin >> search_data)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, please re-enter: ";
        }
        int search_freq = l1.searchList(search_data);
        if (search_freq == 0)
            cout << "Data not found" << endl;
        else
            cout << "It took algorithm " << search_freq << " iteration(s) to find " << search_data << " in the list." << endl;

        cout << endl << "----------> if you want to exit searching enter 0 else 1: ";
        cin >> input;
        if (input == 0) break;
    }
    return 0;
}

void LinkedList::createList() {

    cout << "Here we are going to create the Linked list." << endl;
    int input = 1;
    int current_data = 0;
    int counter = 1;
    while (input) {
        cout << endl << "Enter " << counter++ << " element: ";
        while (!(cin >> current_data)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, please re-enter: ";
        }
        // is int
        node* newNode = new node(current_data);
        if (newNode == NULL) return;

        if (this->head == NULL) {
            this->head = newNode;
            this->tail = newNode;
            cout << "If you want to enter another node enter (1), else (0): ";
            while (!(cin >> input)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, please re-enter: ";
            }
            continue;
        } else {
            this->tail->next = newNode;
            this->tail = newNode;
            cout << "----------> If you want to enter another node enter (1), else (0): ";
            while (!(cin >> input)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, please re-enter: ";
            }
        }

    }
    this->printList();
    //**** if (counter == 1) {
    //****     prev_data = current_data;
    //****     counter++;
    //**** } else if (prev_data > current_data) {
    //****     cout << "You are not entering data in accessinding order." << endl;
    //****     continue;
    //**** } else 
    //****     prev_data = current_data;

}

int LinkedList::searchList(int search_data) {

    if (this->head == NULL) return 0;

    int counter = 0; // count after how many iterations we found the search_data;
    node* prev = NULL;
    node* current = this->head;

    while (current != NULL) {
        if (current->data == search_data) {
            counter++;
            if (prev == NULL) {
                // means it is the first node.
                return counter;
            }
            prev->next = current->next;
            current->next = this->head;
            this->head = current;
            return counter;
        }
        counter++;
        prev = current;
        current = current->next;
    }

    // if (current->data == search_data) {
    //     counter++;
    //     return counter;
    // }
    // counter++;

    return 0;
}

void LinkedList::printList() {

    if (this->head == NULL) {
        cout << "Empty list" << endl;
        return;
    }

    cout << endl << "Head: -> " << this->head->data;
    node* current = this->head->next;
    while (current != NULL) {
        cout << " -> " << current->data;
        current = current->next;
    }
    cout << " -> :Tail" << endl;
}

void LinkedList::freeList() {

    if (this->head == NULL) return;

    node* current = this->head;
    while (current != NULL) {
        this->head = this->head->next;
        delete current;
        current = this->head;
    }
}