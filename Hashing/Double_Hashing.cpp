#include <iostream>
using namespace std;
bool isPrime(int);
// we need 2 hash functions.
// hash1 - key%M
// hash2 - Prime - (key%Prime)
// index = (hash1(key) + i*hash2(key))%M)

template <typename T>
class DoubleHashing {
    const int default_size_of_array = 13;
    const float max_load_factor = 0.75f;
    int prime;
    int size_of_table;
    int total_elements;
    float load_factor;
    T* array;
    int getPrime(int);
public:
    DoubleHashing() {
        this->size_of_table = this->default_size_of_array;
        this->total_elements = 0;
        this->load_factor = 0.0f;
        this->prime = 7;
        this->array = new T[this->size_of_table];
        this->initArray(this->array, this->size_of_table);
    }
    DoubleHashing(int array_size) {
        if (array_size < 1) this->size_of_table = this->default_size_of_array;
        else this->size_of_table = array_size;
        this->total_elements = 0;
        this->load_factor = 0.0f;
        // we need prime number less than size of array.
        this->prime = getPrime(this->size_of_table);
        this->array = new T[this->size_of_table];
        this->initArray(this->array, this->size_of_table);
    }
    ~DoubleHashing() {
        delete[] this->array;
    }
    void initArray(T[], int);//
    void rehash(bool);
    void insert(T[], T);//
    void insert(T);//
    int getHash1(T);//
    int getHash2(T);//
    int search(T);//
    void deleteValue(T);
    void display();//
};


int main() {
    DoubleHashing<int> dh(5);
    dh.insert(45);
    dh.insert(55);
    dh.insert(17);
    dh.insert(57);
    dh.insert(4);
    dh.insert(51);
    dh.insert(58);
    dh.insert(478);
    dh.insert(47);
    dh.insert(412);
    dh.insert(35);
    dh.insert(378);
    dh.insert(895);
    dh.insert(891);
    dh.insert(8145);
    dh.deleteValue(8145);
    dh.display();
    int find = 51;
    cout << "Finding " << find << " : " << dh.search(find) << endl;
    find = 4;
    cout << "Finding " << find << " : " << dh.search(find) << endl;
    find = 57;
    cout << "Finding " << find << " : " << dh.search(find) << endl;
    find = 55;
    cout << "Finding " << find << " : " << dh.search(find) << endl;
    find = 45;
    cout << "Finding " << find << " : " << dh.search(find) << endl;
    find = 46;
    cout << "Finding " << find << " : " << dh.search(find) << endl;
    return 0;
}
template <typename T>
void DoubleHashing<T>::insert(T insert_value) {
    this->insert(this->array, insert_value);

    this->total_elements++;
    this->load_factor = this->total_elements / (float)this->size_of_table;
    if (this->load_factor > this->max_load_factor) {
        cout << "REHASH REQUIRED" << endl;
        this->rehash(true);
    }
}
template <typename T>
void DoubleHashing<T>::insert(T newArray[], T insert_value) {
    int index;
    int increment = 0;
    do {
        index = (getHash1(insert_value) + increment * getHash2(insert_value)) % this->size_of_table;
        increment++;
    } while (newArray[index] != -1);

    newArray[index] = insert_value;
}
template <typename T>
int DoubleHashing<T>::search(T search_value) {
    int index = 0;
    int increment = 0;
    int hash1 = getHash1(search_value);
    int hash2 = getHash2(search_value);
    do {
        index = (hash1 + increment * hash2) % this->size_of_table;
        increment++;
    } while (this->array[index] != -1 && this->array[index] != search_value);

    if (array[index] == search_value) return index;
    return -1;
}
template <typename T>
void DoubleHashing<T>::deleteValue(T del_value) {
    int index = search(del_value);
    if (index == -1) return;
    array[index] = -1;

    this->total_elements--;
    // we have deleted the element on index in array.
    // we have to rehash the table now.
    this->rehash(false);
}
template <typename T>
void DoubleHashing<T>::rehash(bool is_size_double) {
    // create new array.
    int previous_size_of_table = this->size_of_table;
    if (is_size_double) {
        this->size_of_table = previous_size_of_table * 2;
        this->prime = this->getPrime(this->size_of_table);
    }
    T* newArray = new T[this->size_of_table];
    initArray(newArray, this->size_of_table);

    for (int i = 0; i < previous_size_of_table; i++) {
        if (this->array[i] != -1)
            insert(newArray, this->array[i]);
    }

    delete[] this->array;
    this->array = newArray;
}

template <typename T>
void DoubleHashing<T>::initArray(T array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = -1;
    }
}

template <typename T>
void DoubleHashing<T>::display() {
    for (int i = 0;i < this->size_of_table; i++) {
        cout << i << " :\t" << this->array[i] << endl;
    }
}
template <>
int DoubleHashing<int>::getHash1(int value) {
    return (value % this->size_of_table);
}
template <>
int DoubleHashing<float>::getHash1(float value) {
    return((int)value % this->size_of_table);
}
template <>
int DoubleHashing<char>::getHash1(char value) {
    return ((int)value % this->size_of_table);
}
template <>
int DoubleHashing<int>::getHash2(int value) {
    return (this->prime - (value % this->prime));
}
template <>
int DoubleHashing<float>::getHash2(float value) {
    return (this->prime - ((int)value % this->prime));
}
template <>
int DoubleHashing<char>::getHash2(char value) {
    return (this->prime - ((int)value % this->prime));
}
template <typename T>
int DoubleHashing<T>::getPrime(int max_n) {
    if (max_n == 1) return 1;
    int max_prime = 1;
    for (int i = 2; i < max_n; i++) {
        if (isPrime(i)) max_prime = i;
    }
    return max_prime;
}
bool isPrime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}