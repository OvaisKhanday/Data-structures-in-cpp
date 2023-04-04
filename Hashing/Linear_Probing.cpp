#include <iostream>
using namespace std;

// In Open Addressing, all elements are stored in the hash table itself.
// So at any point, the size of the table must be greater than or equal to the total
// number of keys(Note that we can increase table size by copying old data if needed).
template <typename T>
class OpenAddressing {
public:
    const int default_size_of_array = 13;
    const float max_load_factor = 0.75f;
    int size_of_table;
    int total_elements;
    float load_factor;
    T* array;
    ~OpenAddressing() {
        delete[] array;
    }
    void initArray(T[], int);
    void rehash(bool);
    void insert(T[], T);
    void insert(T);
    int getHash(T);
    bool search(T);
    void deleteValue(T);
    void display();
    bool isEmptyTable();
    float getLoadFactor();
};

template <typename T>
class LinearProbeHashing :public OpenAddressing<T> {
public:
    LinearProbeHashing() {
        this->size_of_table = this->default_size_of_array;
        this->total_elements = 0;
        this->load_factor = 0.0f;
        this->array = new T[this->size_of_table];
        this->initArray(this->array, this->size_of_table);
    }
    LinearProbeHashing(int array_size) {
        this->size_of_table = array_size;
        this->total_elements = 0;
        this->load_factor = 0.0f;
        this->array = new T[this->size_of_table];
        this->initArray(this->array, this->size_of_table);
    }

};
int main() {
    LinearProbeHashing<int> lp;
    lp.insert(12);
    lp.insert(17);
    lp.insert(19);
    lp.insert(26);
    lp.insert(278);
    lp.insert(111);
    lp.insert(1147);
    lp.insert(10);
    lp.insert(15);
    lp.display();
    lp.deleteValue(111);
    lp.deleteValue(278);
    lp.deleteValue(10);
    lp.deleteValue(17);
    lp.deleteValue(178);
    lp.display();
    cout << "\nSearching 25: " << lp.search(25);
    return 0;
}

template <typename T>
bool OpenAddressing<T>::isEmptyTable() {
    return this->total_elements == 0;
}

template <typename T>
void OpenAddressing<T>::initArray(T array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = -1;
    }
}

template <typename T>
void OpenAddressing<T>::insert(T insert_value) {
    // get the index in the array according the value.
    int index = getHash(insert_value);

    // we have got the index in array, check now if it is free or not.
    // the index is not available for storage then, check while you did'nt find any.
    while (array[index] != -1) {
        if (++index == this->size_of_table) index = 0;
    }
    // now we have found the index;
    array[index] = insert_value;

    this->total_elements++;
    this->load_factor = this->total_elements / (float)this->size_of_table;
    if (this->load_factor > this->max_load_factor) {
        cout << "REHASH REQUIRED" << endl;
        this->rehash(true);
    }
}
template <typename T>
bool OpenAddressing<T>::search(T search_value) {
    if (isEmptyTable()) return false;

    int index = getHash(search_value);

    while (this->array[index] != -1) {
        if (this->array[index] == search_value) return true;
        if (++index == this->size_of_table) index = 0;
    }
    return false;
}
template <typename T>
void OpenAddressing<T>::display() {
    for (int i = 0;i < this->size_of_table; i++) {
        cout << i << " :\t" << this->array[i] << endl;
    }
}

template <typename T>
void OpenAddressing<T>::deleteValue(T del_value) {
    if (isEmptyTable()) return;
    int index = getHash(del_value);
    while (this->array[index] != -1) {
        if (this->array[index] == del_value) {
            // we have found the index.
            array[index] = -1;
            this->total_elements--;
            rehash(false);
            return;
        }
        if (++index == this->size_of_table) index = 0;
    }

}
template <typename T>
void OpenAddressing<T>::rehash(bool sizeDouble) {
    // after deletion rehashing
    // int total_elements_in_current_table = this->total_elements;
    // T* temp_array = new T[total_elements_in_current_table];
    // int index = 0;
    // // storing the table content in anther array.
    // for (int i = 0;i < this->size_of_table;i++) {
    //     if (this->array[i] != -1)
    //         temp_array[index++] = array[i];
    // }
    // // check if we need to resize the array.
    // if (sizeDouble == true) {
    //     delete[] this->array;
    //     this->size_of_table = this->size_of_table * 2;
    //     this->array = new T[this->size_of_table];
    // }
    // // init the array.
    // initArray(this->array, this->size_of_table);
    // this->total_elements = 0;
    // this->load_factor = 0.0f;
    // // put the stored values back in the array.
    // for (int i = 0;i < total_elements_in_current_table;i++) {
    //     this->insert(temp_array[i]);
    // }
    // delete[] temp_array;

    int previous_size_of_table = this->size_of_table;
    // creating new array.
    if (sizeDouble) {
        this->size_of_table = this->size_of_table * 2;
    }
    T* newArray = new T[this->size_of_table];
    initArray(newArray, this->size_of_table);

    // we have to insert the elements from this.array into newArray
    for (int i = 0; i < previous_size_of_table; i++) {
        if (this->array[i] != -1)
            insert(newArray, this->array[i]);
    }
    delete[] this->array;
    this->array = newArray;
}

template <typename T>
void OpenAddressing<T>::insert(T newArray[], T insert_value) {
    // get the index in the array according the value.
    int index = getHash(insert_value);

    // we have got the index in array, check now if it is free or not.
    // the index is not available for storage then, check while you did'nt find any.
    while (newArray[index] != -1) {
        if (++index == this->size_of_table) index = 0;
    }
    // now we have found the index;
    newArray[index] = insert_value;
}


template <>
int OpenAddressing<int>::getHash(int value) {
    return (value % this->size_of_table);
}
template <>
int OpenAddressing<float>::getHash(float value) {
    return((int)value % this->size_of_table);
}
template <>
int OpenAddressing<char>::getHash(char value) {
    return ((int)value % this->size_of_table);
}