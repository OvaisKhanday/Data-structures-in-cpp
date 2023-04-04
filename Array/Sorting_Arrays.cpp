#include <iostream>
#define INSERTION_SIZE 2
using namespace std;

// utility functions.
template <typename T>
void swapValues(T*, T*);
template <typename T>
void display(T[], int);
template <typename T>
// array, size, start, end
int indexOfLargestValue(T[], int, int, int);
template <typename T>
// utility function for quick sort.
// @param (array, left, right);
void medianLeft(T[], int, int);


// sorting functions.
// pointer to array, size of array.
template <typename T>
void bubbleSort(T[], int);
template <typename T>
void selectionSort(T[], int);
template <typename T>
void insertionSort(T[], int);
template <typename T>
// this function will be used internally by quick sort
// @param (array, left, right); // left, right -- inclusive
void insertionSort(T[], int, int);
template <typename T>
void shellSort(T[], int);
template <typename T>
void quickSort(T[], int);
template <typename T>
void quickSort(T[], int, int);

void cyclicSort(int[], int);

template <typename T>
void driverCode(T[], int);

int main() {

    int int_array[] = { 8,6,4,2,0, 90, -1, 12, 21, 75 ,12,42,45,32,65,69,0,87,54,12,34,567,87,345,689,98,88,78,67,56,45,34,23,123,345,567,890,1234,12345,567,87654,345,2 };
    // bubbleSort(int_array, sizeof(int_array) / sizeof(int));
    // selectionSort(int_array, sizeof(int_array) / sizeof(int));
    // insertionSort(int_array, sizeof(int_array) / sizeof(int));
    // insertionSort(int_array, 0, 2);
    // shellSort(int_array, sizeof(int_array) / sizeof(int));
    // quickSort(int_array, sizeof(int_array) / sizeof(int));
    // display(int_array, sizeof(int_array) / sizeof(int));

    float float_array[] = { 2.1, 4.2, 8.2, 70.8, 45.1, 89.35, 12.01, 54.2 };
    // bubbleSort(float_array, sizeof(float_array) / sizeof(float));
    // selectionSort(float_array, sizeof(float_array) / sizeof(float));
    // display(float_array, sizeof(float_array) / sizeof(float));

    char char_array[] = { 'f', 'e', 'd', 'c','b', 'a' };
    // bubbleSort(char_array, sizeof(char_array) / sizeof(char));
    // selectionSort(char_array, sizeof(char_array) / sizeof(char));
    // display(char_array, sizeof(char_array) / sizeof(char));

    // int cyclic_array[] = { 1,5,3,9,7,18,6,4,2,10 };
    // cyclicSort(cyclic_array, sizeof(cyclic_array) / sizeof(int));
    // display(cyclic_array, sizeof(cyclic_array) / sizeof(int));


    driverCode(int_array, sizeof(int_array) / sizeof(int));

    return 0;
}

template <typename T>
void bubbleSort(T array[], int size) {
    if (size < 1) return;

    cout << "=============== STEPS ===============\n";
    // the outer loop will run (size-1) times.
    for (int i = 1; i <= size - 1; i++) {
        bool swapHappended = false;
        for (int j = 1; j <= size - i; j++) {
            if (array[j - 1] > array[j]) {
                swapValues(&array[j], &array[j - 1]);
                swapHappended = true;
                display(array, size);
            }
        }
        if (swapHappended == false) break;
    }
    cout << "============ STEPS ENDED ============\n";


}

template <typename T>
void swapValues(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
void display(T array[], int size) {
    if (size < 1) {
        cout << "Empty Array" << endl;
        return;
    }

    cout << array[0];
    for (int i = 1; i < size; i++) {
        cout << ", " << array[i];
    }
    cout << endl;
}

template <typename T>
void selectionSort(T array[], int size) {
    if (size < 1) return;

    // outer loop
    int start = 0;
    int end = size - 1;
    cout << "=============== STEPS ===============\n";
    for (int i = 1; i <= size - 1; i++) {
        int largestValueIndex = indexOfLargestValue(array, size, start, end);
        if (largestValueIndex != end)
            swapValues(&array[largestValueIndex], &array[end]);
        end--;
        display(array, size);
    }
    cout << "============ STEPS ENDED ============\n";
}

template <typename T>
int indexOfLargestValue(T array[], int size, int start, int end) {
    if (start > end || size < 1) return -1;

    int largestValueIndex = 0;
    for (int i = start + 1; i <= end; i++) {
        if (array[i] > array[largestValueIndex]) {
            largestValueIndex = i;
        }
    }
    return largestValueIndex;
}

template <typename T>
void insertionSort(T array[], int size) {
    if (size < 1) return;

    cout << "=============== STEPS ===============\n";
    for (int i = 0; i <= size - 2; i++) {
        // 0, 1,2,3
        for (int j = i + 1; j >= 1; j--) {
            if (array[j - 1] > array[j]) {
                swapValues(&array[j], &array[j - 1]);
                display(array, size);
            } else break;

        }
    }
    cout << "============ STEPS ENDED ============\n";
}

void cyclicSort(int array[], int n) {
    if (n < 1) return;

    int index = 0;
    for (int i = 0; i < n - 1; i++) {
        // check if the value does not violate the property of cyclic sort,
        // that is every element of the array should be <= n;
        if (array[index] < 1 || array[index] > n) {
            cout << "In-valid array, can't perform cyclic sort\n";
            return;
        }
        // check if array[i] is at right index.
        if (array[index] == index + 1) index++;
        else swapValues(&array[index], &array[array[index] - 1]);
    }

}
template <typename T>
void shellSort(T array[], int size) {
    int increment = (size - 1) / 2;
    cout << "=============== STEPS ===============\n";
    while (increment != 0) {
        for (int current = increment;current < size; current++) {
            T temp = array[current];
            int walker = current - increment;
            while (walker >= 0 && temp < array[walker]) {
                array[walker + increment] = array[walker];
                walker = walker - increment;
            }
            array[walker + increment] = temp;
            display(array, size);
        }
        increment /= 2;
    }
    cout << "============ STEPS ENDED ============\n";
}


template <typename T>
void driverCode(T array[], int size) {
    if (size < 1) return;

    cout << "Choose among sorting algorthims: \n";
    cout << "1. Bubble sort\t\t2. Selection sort\n3. Insertion sort\t4. Shell sort\n";
    cout << "Enter [1,2,3,4]: ";
    int sort_choose = 0;
    while (!(cin >> sort_choose) || sort_choose < 1 || sort_choose > 4) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter [1,2,3,4]: ";
    }

    if (sort_choose == 1) {
        cout << "============ BUBBLE SORT ============\n";
        bubbleSort(array, size);
        cout << "bubble sort performed on array!\n";

    } else if (sort_choose == 2) {
        cout << "========== SELECTION SORT ===========\n";
        selectionSort(array, size);
        cout << "selection sort performed on array!\n";

    } else if (sort_choose == 3) {
        cout << "========== INSERTION SORT ===========\n";
        insertionSort(array, size);
        cout << "insertion sort performed on array!\n";
    } else {
        cout << "============ SHELL SORT =============\n";
        shellSort(array, size);
        cout << "shell sort performed on array!\n";
    }
    display(array, size);
}
template <typename T>
void insertionSort(T array[], int first, int last) {
    // [first, last] -- closed interval.
    if (first >= last) return;
    int current = first + 1;
    while (current <= last) {
        T hold = array[current];
        int walker = current - 1;
        while (walker >= first && hold < array[walker]) {
            array[walker + 1] = array[walker];
            walker--;
        }
        array[walker + 1] = hold;
        current++;
    }
}

template <typename T>
void medianLeft(T array[], int left, int right) {
    // [left, right] -- closed interval.
    if (left >= right) return;
    int mid = (left + right) / 2;
    // l - m
    // l - r
    // m - r
    if (array[left] > array[mid])
        swapValues(&array[left], &array[mid]);
    if (array[left] > array[right])
        swapValues(&array[left], &array[right]);
    if (array[mid] > array[right])
        swapValues(&array[mid], &array[right]);

    // before return swap left and middle so pivot is on left index.
    swapValues(&array[left], &array[mid]);
}


template <typename T>
void quickSort(T array[], int size) {
    if (size < 1) return;

    if (size <= INSERTION_SIZE) insertionSort(array, 0, size - 1);
    else quickSort(array, 0, size - 1);
}

template <typename T>
void quickSort(T array[], int first, int last) {
    if (last - first + 1 > INSERTION_SIZE) {

        // finding pivot.
        medianLeft(array, first, last);
        T pivot = array[first];
        int sortLeft = first + 1;
        int sortRight = last;

        while (sortLeft <= sortRight) {

            while (sortLeft <= sortRight && array[sortLeft] < pivot) {
                sortLeft++;
            }
            while (sortLeft <= sortRight && pivot <= array[sortRight]) {
                sortRight--;
            }
            if (sortLeft <= sortRight) {
                swapValues(&array[sortLeft], &array[sortRight]);
                sortLeft++;
                sortRight--;
            }
        }
        swapValues(&array[first], &array[sortLeft - 1]);
        if (first < sortRight) quickSort(array, first, sortRight - 1);
        if (sortLeft < last) quickSort(array, sortLeft, last);

    } else {
        insertionSort(array, first, last);
    }
}