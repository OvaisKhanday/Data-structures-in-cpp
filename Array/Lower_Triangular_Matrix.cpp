// A triangular matrix is a special kind of square matrix.
// if there are n rows in the matrix, then the size of 1D 
// triangular matrix is half of n(n+1).

#include <iostream>
using namespace std;


template <class T>
void ArrayToMatrix(T[], int);

template <class T>
T* MatrixToArray(T*, int);

int MatrixRowsToArraySize(int);
int ArraySizeToMatrixRows(int);

int main() {

    // let the lower triangular matrix be,
    float mat[][5] = {
        {1.2, 0, 0, 0, 0},
        {2.15, 3.3, 0, 0, 0},
        {4, 0.5, 6, 0, 0},
        {7, 8, 9.23, 10, 0},
        {11, 1.2, 1.3, 14, 15.15}
    };

    int array[6] = { 1, 56, 84, 45, 78, 97 };
    ArrayToMatrix<int>(array, 6);

    float* ptr = MatrixToArray((float*)mat, 5);
    for (int i = 0; i < MatrixRowsToArraySize(5); i++) {
        cout << *(ptr + i) << "  ";
    }
    cout << endl << endl;
    ArrayToMatrix(ptr, 15);


    delete[] ptr;
    return 0;
}

template <class T>
void ArrayToMatrix(T array[], int size) {

    size = ArraySizeToMatrixRows(size);
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) cout << array[index++] << "\t";
        for (int j = size - 1; j > i; j--) cout << "0\t";
        cout << endl;
    }
}


template <class T>
T* MatrixToArray(T* array, int rows) {

    int size_of_Array = MatrixRowsToArraySize(rows);

    if (size_of_Array == 0) return NULL;

    T* one_D_Array = new T[size_of_Array];

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            // *((arr+i*n) + j)
            one_D_Array[index++] = *((array + i * rows) + j);
        }
    }
    return one_D_Array;
}

int MatrixRowsToArraySize(int matSize) {

    int arraySize = 0;
    if (matSize <= 0) return arraySize;

    arraySize = (matSize * (matSize + 1)) / 2;
    return arraySize;
}

int ArraySizeToMatrixRows(int arrSize) {

    int cumulative_sum = 1;
    int result = 0;
    int total_sum = 0;

    while (total_sum < arrSize) {
        total_sum = total_sum + (cumulative_sum++);
        result++;
    }
    return result;
}