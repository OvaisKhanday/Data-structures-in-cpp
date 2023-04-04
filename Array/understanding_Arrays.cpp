#include <iostream>
using namespace std;

int* func(int*, int);

int main() {
    int arr[][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
    int no_of_rows_in_matrix = sizeof(arr[0]) / sizeof(int);

    int* diagonal_array = func((int*)arr, no_of_rows_in_matrix);

    for (int i = 0; i < no_of_rows_in_matrix; i++) {
        cout << *(diagonal_array + i) << ", ";
    }
    return 0;
}

int* func(int* arr, int no_of_rows_in_matrix) {

    if (no_of_rows_in_matrix == 0) return NULL;

    int* diagonal_array = new int[no_of_rows_in_matrix];

    // *((arr+i*n) + j)
    for (int i = 0, n = no_of_rows_in_matrix * no_of_rows_in_matrix; i < n; i++) {
        diagonal_array[i] = *((arr + i * no_of_rows_in_matrix) + i);
    }

    return diagonal_array;
}