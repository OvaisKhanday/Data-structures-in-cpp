#include <iostream>
using namespace std;

// in separate chaining we use links between nodes and the hast table.
template <typename V>
class node {
public:
    V value;
    node<V>* next;

    node(V value) {
        this->value = value;
        this->next = NULL;
    }
};

// let key be integer type.
template <typename V>
class HashTable {
    // in each hash table we need an array to store pointer to nodes.
    // that means pointer to pointer and array of pointers.
    node<V>** array;
    const int default_size_of_array = 13;
    const float max_load_factor = 0.75f;
    int total_elements;
    int size_of_array;
    float load_factor;
    // load factor = total_elements / size_of_array;
    void initArray(node<V>* [], int);
    node<V>** rehash();
    void insert(node<V>* [], V);
public:
    HashTable() {
        this->size_of_array = default_size_of_array;
        this->total_elements = 0;
        this->load_factor = 0;
        this->array = new node<V>*[this->size_of_array];
        this->initArray(array, size_of_array);
    }
    HashTable(int array_size) {
        if (array_size < 1)
            this->size_of_array = this->default_size_of_array;
        else this->size_of_array = array_size;

        this->total_elements = 0;
        this->load_factor = 0;
        this->array = new node<V>*[size_of_array];
        this->initArray(this->array, size_of_array);
    }
    ~HashTable() {
        this->deleteTable();
        delete[] this->array;
    }

    bool isEmptyTable(); //
    int getHash(V); //
    float getLoadFactor(); //
    void insert(V); //
    bool search(V); //
    void deleteValue(V); //
    void display(); //
    void deleteTable(); //
};


int main() {
    HashTable<int> table;
    table.insert(10);
    table.insert(458);
    table.insert(786);
    table.insert(713);
    // table.insert(11);
    table.insert(12);
    table.insert(1474);
    table.insert(4555);
    table.display();
    table.insert(6547);
    table.insert(6548);
    table.insert(6549);
    table.insert(60);
    table.insert(1420);
    table.insert(142);
    table.insert(145);
    table.display();
    table.insert(144);
    table.insert(147);
    table.insert(148);
    table.insert(149);
    table.insert(1494);
    table.display();

    return 0;
}

template <typename T>
void HashTable<T>::initArray(node<T>* array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = NULL;
    }
}
template <typename T>
void HashTable<T>::insert(T insert_value) {
    // get the index in the array according the value.
    int index = getHash(insert_value);

    // create a node.
    node<T>* newNode = new node<T>(insert_value);
    if (newNode == NULL) return;

    // we have got the index check if the value in array at index is null.
    if (this->array[index] == NULL) {
        this->array[index] = newNode;
    } else {
        // there is at least one node that is pointed by array at specific index.
        // we can add node in a sorted order (int, float, char). 
        // because in these 3 data types we can compare them on the basis of value.
        // like 1<2, 3.4< 4.3 and a<b; and search and delete becomes more efficient, because
        // when we encounter a number greater than the number been searched we can stop
        // search immediately, as now there is no chance of find it.

        // We know there is at least one node present.
        // There could be 3 possibilities here, like 
        // 1. node is inserted before all other node. i.e., array will point to that node.
        // 2. node between 2 nodes. here we have to relink the nodes.
        // 3. the easiest one, node is inserted at the end of all other nodes.

        // let us find the location of node.
        node<T>* prev = NULL;
        node<T>* current = array[index];
        while (current != NULL && current->value < insert_value) {
            prev = current;
            current = current->next;
        }

        // if data is already present, current will be on the same value, as X < X is false.
        if (current != NULL && current->value == insert_value) {
            free(newNode);
            return;
        }

        // 1 case can be identified, if prev is NULL.
        // 2 case can be identified, if current and prev both are not NULL.
        // 3 case can be identified, if current is NULL.

        if (prev == NULL) {
            // case 1
            this->array[index] = newNode;
            newNode->next = current;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
    // Either it is first node or last node, we have to update some attributes.
    // increment the total_elements count and find the new Load factor.
    this->total_elements++;
    this->load_factor = total_elements / (float)size_of_array;

    if (load_factor > max_load_factor) {
        this->array = this->rehash();
    }

}
template <typename T>
void HashTable<T>::display() {

    for (int i = 0; i < this->size_of_array; i++) {
        cout << i << " :";
        if (this->array[i] == NULL)
            cout << "\t" << "NULL";
        else {
            node<T>* current = this->array[i];
            while (current != NULL) {
                cout << "  -->  " << current->value;
                current = current->next;
            }
        }
        cout << endl;
    }
}

template <>
int HashTable<int>::getHash(int value) {
    return (value % this->size_of_array);
}
template <>
int HashTable<float>::getHash(float value) {
    return((int)value % this->size_of_array);
}
template <>
int HashTable<char>::getHash(char value) {
    return ((int)value % this->size_of_array);
}

template <typename T>
float HashTable<T>::getLoadFactor() {
    return this->load_factor;
}
template <typename T>
bool HashTable<T>::isEmptyTable() {
    return this->total_elements == 0;
}

template <typename T>
void HashTable<T>::deleteTable() {
    if (isEmptyTable()) return;
    for (int index = 0; index < this->size_of_array; index++) {
        node<T>* current = this->array[index];
        while (current != NULL) {
            node<T>* current_delete = current;
            current = current->next;
            free(current_delete);
        }
        this->array[index] = NULL;
    }
    this->load_factor = 0;
    this->total_elements = 0;
}

template <typename T>
bool HashTable<T>::search(T search_value) {
    if (isEmptyTable()) return false;

    int index = getHash(search_value);
    node<T>* current = this->array[index];
    while (current != NULL && current->value <= search_value) {
        if (search_value == current->value) return true;
        current = current->next;
    }
    return false;
}

template <typename T>
void HashTable<T>::deleteValue(T delete_value) {
    if (isEmptyTable()) return;

    int index = getHash(delete_value);
    node<T>* prev = NULL;
    node<T>* current = this->array[index];
    while (current != NULL && current->value <= delete_value) {
        if (delete_value == current->value) {
            if (prev == NULL) {
                // array[index] need to be changed.
                // we know current's next may be NULL but current is not null,
                // so it is safe to use current->next;
                array[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            this->total_elements--;
            // we will recalculate the loading factor while inserting new value.
            // because that is dependent on total_elements in the hast table, so the 
            // only think we should update is total_elements count.
            return;
        }
        prev = current;
        current = current->next;
    }
}

template <typename T>
node<T>** HashTable<T>::rehash() {
    int size_of_prev_array = this->size_of_array;
    this->size_of_array = size_of_prev_array * 2;

    node<T>** newArray;
    newArray = new node<T>*[size_of_array];
    initArray(newArray, size_of_array);

    for (int i = 0;i < size_of_prev_array; i++) {
        node<T>* current = this->array[i];
        while (current != NULL) {
            // insert data to the new array.
            insert(newArray, current->value);
            node<T>* current_delete = current;
            current = current->next;
            // delete data here in array.
            free(current_delete);
        }
    }
    delete[] this->array;
    return newArray;
}

template <typename T>
void HashTable<T>::insert(node<T>* new_array[], T insert_value) {
    // get the index in the new_array according the value.
    int index = getHash(insert_value);

    // create a node.
    node<T>* newNode = new node<T>(insert_value);
    if (newNode == NULL) return;

    // we have got the index check if the value in new_array at index is null.
    if (new_array[index] == NULL) {
        new_array[index] = newNode;
    } else {

        node<T>* prev = NULL;
        node<T>* current = new_array[index];
        while (current != NULL && current->value < insert_value) {
            prev = current;
            current = current->next;
        }

        // if data is already present, current will be on the same value, as X < X is false.
        if (current != NULL && current->value == insert_value) {
            free(newNode);
            return;
        }

        // 1 case can be identified, if prev is NULL.
        // 2 case can be identified, if current and prev both are not NULL.
        // 3 case can be identified, if current is NULL.

        if (prev == NULL) {
            // case 1
            new_array[index] = newNode;
            newNode->next = current;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }

}