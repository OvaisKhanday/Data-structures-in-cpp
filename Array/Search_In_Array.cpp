#include <iostream>
using namespace std;

void driverCode();

// (array, size_of_array, search_element);
template <typename T>
int linearSearch(T[], int, T);

template <typename T>
int binarySearch(T[], int, T);

template <typename T>
int binarySearchRecursive(T[], int, T);

// internally recursive function is:
template <typename T>
int binarySearchRec(T[], int, int, T);

template <typename T>
void display(T[], int);

template <typename T>
void createArray(T, int);

template <typename T>
void searching(T[], int, bool);


int main() {

    driverCode();

    return 0;
}

void driverCode() {
    cout << "What type of array you want to create.\n";
    cout << "1. int\t\t2. float\n3. char\t\t0. exit\n";
    cout << "Enter [0,1,2,3]: ";
    int choice = 0;
    while (!(cin >> choice) || choice < 0 || choice > 3) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter [0,1,2,3]: ";
    }
    int size_of_array = 0;
    if (choice == 0) return;

    cout << "Enter size of array: ";
    while (!(cin >> size_of_array) || size_of_array < 1) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter valid size: ";
    }

    if (choice == 1) {
        int int_type;
        createArray(int_type, size_of_array);
    } else if (choice == 2) {
        float float_type;
        createArray(float_type, size_of_array);
    } else if (choice == 3) {
        char char_type;
        createArray(char_type, size_of_array);
    } else return;
}

template <typename T>
int linearSearch(T array[], int size_of_array, T search_data) {
    for (int i = 0; i < size_of_array; i++) {
        if (array[i] == search_data) return i;
    }
    return -1;
}

template <typename T>
void display(T array[], int size_of_array) {
    if (size_of_array >= 0) cout << array[0];
    for (int i = 1; i < size_of_array; i++) {
        cout << ", " << array[i];
    }
    cout << endl;
}

template <typename T>
void createArray(T type, int size_of_array) {
    T* ptr_to_array = new T[size_of_array];


    // before entering data in array we must prompt user to choose either of them,
    // because if user choose the binary search then we don't allow the user to enter
    // the data in array in random order.
    cout << "Select either of them: \n";
    cout << "1. Linear Search\n2. Binary Search\n";
    cout << "Enter [1,2]: ";
    int search_choice = 0;
    while (!(cin >> search_choice) || search_choice < 1 || search_choice >2) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter [1,2]: ";
    }


    T insert_data;
    if (search_choice == 1) {
        cout << "You have choosen Linear Search\n";
        // isPresent = linearSearch(ptr_to_array, size_of_array, search_element) == true ? true : false;
        for (int i = 0;i < size_of_array;i++) {
            cout << "Enter in " << i << " index: ";
            while (!(cin >> insert_data)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, try again for " << i << " index: ";
            }
            ptr_to_array[i] = insert_data;
        }


    } else {
        // User has choosen the binary search
        cout << "You have choosen Binary Search\n";
        T previous_data;
        cout << "Enter in 0 index: ";
        while (!(cin >> insert_data)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, try again for 0 index: ";
        }
        previous_data = insert_data;
        ptr_to_array[0] = insert_data;

        for (int i = 1; i < size_of_array; i++) {
            cout << "Enter in " << i << " index: ";
            while (!(cin >> insert_data) || previous_data > insert_data) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Bad input, try again for " << i << " index: ";
            }
            previous_data = insert_data;
            ptr_to_array[i] = insert_data;
        }
        // now we have a stored array, we can now perform binary search.

    }

    cout << "COMPLETED INSERTION OF DATA" << endl;
    display(ptr_to_array, size_of_array);
    bool isBinary = search_choice == 2 ? true : false;
    searching(ptr_to_array, size_of_array, isBinary);
}

template <typename T>
void searching(T ptr_to_array[], int size_of_array, bool isBinary) {
    cout << "Enter element you want to search: ";
    T search_element;
    while (!(cin >> search_element)) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Bad input, try again: ";
    }

    int isPresent;
    if (isBinary == false) {
        cout << "You have choosen Linear Search\n";
        isPresent = linearSearch(ptr_to_array, size_of_array, search_element);
    } else {
        cout << "You have choosen Binary Search\n";
        cout << "Choose\n1. Iterative\n2. Recursive\n";
        cout << "Enter [1,2]: ";
        int search_choice = 0;
        while (!(cin >> search_choice) || search_choice < 1 || search_choice >2) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter [1,2]: ";
        }
        if (search_choice == 1) {
            isPresent = binarySearch(ptr_to_array, size_of_array, search_element);
        } else isPresent = binarySearchRecursive(ptr_to_array, size_of_array, search_element);
    }

    if (isPresent > -1)cout << search_element << " Found on " << isPresent << " index\n";
    else cout << search_element << " Not Found\n";
    delete ptr_to_array;
}

template <typename T>
int binarySearch(T ptr_to_array[], int size_of_array, T search_element) {
    int start = 0;
    int end = size_of_array - 1;
    int mid;
    while (start <= end) {
        mid = start + (end - start) / 2;
        if (ptr_to_array[mid] == search_element) return mid;
        else if (search_element < ptr_to_array[mid]) {
            end = mid - 1;
        } else start = mid + 1;
    }
    return -1;
}

template <typename T>
int binarySearchRecursive(T ptr_to_array[], int size_of_array, T search_element) {
    if (size_of_array < 1) return -1;
    return binarySearchRec(ptr_to_array, 0, size_of_array - 1, search_element);
}
template <typename T>
int binarySearchRec(T ptr_to_array[], int start, int end, T search_element) {
    if (start > end) return -1;
    int mid = start + (end - start) / 2;
    if (ptr_to_array[mid] == search_element) return mid;
    else if (search_element < ptr_to_array[start])
        return binarySearchRec(ptr_to_array, start, mid - 1, search_element);
    else return binarySearchRec(ptr_to_array, mid + 1, end, search_element);
}