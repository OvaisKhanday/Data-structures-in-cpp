#include <iostream>
#include <windows.h>
using namespace std;

// each node would contain its own count data.
class node {
public:
    int data;
    int repeat_count;
    node* next;

    node() {
        this->data = 0;
        this->repeat_count = 0;
        this->next = NULL;
    }
    node(int data) {
        this->data = data;
        this->repeat_count = 0;
        this->next = NULL;
    }
};

class LinkedList {
    node* head;
    node* tail;

    void freeList();
    void createList();
public:
    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->createList();
    }
    int searchList(int);
    void printList();
};



int main() {

    system("Color 70");
    LinkedList l1;
    int input = 0;
    while (1) {
        int search_data = 0;
        l1.printList();
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
                (current->repeat_count)++;
                return counter;
            }
            (current->repeat_count)++;
            node* goto_prev_count = NULL;
            node* goto_current_count = this->head;
            while (goto_current_count->repeat_count > current->repeat_count) {
                goto_prev_count = goto_current_count;
                goto_current_count = goto_current_count->next;
            }
            if (goto_current_count == current) return counter;
            // means current is on right position.
            if (goto_prev_count == NULL) {
                // meaning, head should be pointing to this.
                prev->next = current->next;
                current->next = this->head;
                this->head = current;
                return counter;
            }
            prev->next = current->next;
            goto_prev_count->next = current;
            current->next = goto_current_count;
            return counter;
        }
        counter++;
        prev = current;
        current = current->next;
    }
    return 0;

}

void LinkedList::printList() {

    if (this->head == NULL) {
        cout << "Empty list" << endl;
        return;
    }

    cout << endl << "Head: -> " << this->head->data << " (" << this->head->repeat_count << ")";
    node* current = this->head->next;
    while (current != NULL) {
        cout << " -> " << current->data << " (" << current->repeat_count << ")";
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