// A diagonal matrix is defined as a square matrix in which all off-diagonal
// entries are zero. (Note that a diagonal matrix is necessarily symmetric.)
// Entries on the main diagonal may or may not be zero.If all entries on the
// main diagonal are equal scalars, then the diagonal matrix is called a scalar matrix.
//   1   0   0,     5   0   0,     1   5   0
//   0   2   0,     0   5   0,     0   8   0
//   0   0   3,     0   0   5,     0   0   9
//   Diagonal       Scalar         Non-Diagonal

#include <iostream>
using namespace std;
template <class T>
void ArrayToDiagonalMatrix(int, T[]);

template <class T>
T* diagonalMatrixToArray(T*, int);

int main() {
    int arr[3][3] = { { 34, 0, 0 }, { 0,43,0 }, { 0,0, 23 } };
    int arr2[5] = { 1,23,345,47899,503 };

    ArrayToDiagonalMatrix(5, arr2);
    cout << endl;

    int* ptr = diagonalMatrixToArray((int*)arr, 3);
    for (int i = 0; i < 3; i++) {
        cout << ptr[i] << "\t";
    }

    delete[] ptr;
    return 0;
};

template <class T>
void ArrayToDiagonalMatrix(int length_of_array, T arr[]) {

    // check if the array is empty...
    if (length_of_array == 0) return;

    for (int i = 0; i < length_of_array; i++) {
        for (int j = 0; j < i; j++) cout << "0\t";
        cout << arr[i];
        for (int j = length_of_array - i - 1; j > 0; j--) cout << "\t0";
        cout << endl;
    }
}

template <class T>
T* diagonalMatrixToArray(T* array, int rows) {

    T* result_1D = NULL;
    if (rows == 0) return result_1D;

    // giving the number of rows in matrix the size of array.
    result_1D = new T[rows];

    for (int i = 0; i < rows; i++)
        // *((arr+i*n) + j)
        result_1D[i] = *((array + i * rows) + i);

    return result_1D;
}