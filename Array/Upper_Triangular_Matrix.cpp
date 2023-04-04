#include <iostream>
using namespace std;

int rowsToArraySize(int);
void enterDataInArray(int[], int rows);
void printMatrixFromArray(int[], int rows);
int getValidRowCount();
int getValidIntType();

int main() {

    unsigned int rows = 0;
    cout << "UPPER TRIANGULAR MATRIX USING 1-D ARRAY" << endl;
    cout << "Enter the dimensions of matrix (row): ";

    rows = getValidRowCount();

    cout << "You had entered " << rows << ", so there must be at maximum ";
    cout << rowsToArraySize(rows) << " elements to be inserted." << endl;
    cout << "Enter in the order of top to bottom and left to right." << endl;

    int array[rowsToArraySize(rows)];

    enterDataInArray(array, rows);

    cout << "\n\tTHE MATRIX" << endl;
    printMatrixFromArray(array, rows);


    return 0;
}

int rowsToArraySize(int rows) {
    int arraySize = 0;
    if (rows <= 0) return arraySize;

    arraySize = (rows * (rows + 1)) / 2;
    return arraySize;
}

void enterDataInArray(int array[], int rows) {
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < rows; j++) {
            cout << "Enter " << i + 1 << ", " << j + 1 << " element: ";
            array[index++] = getValidIntType();
        }
    }
}

void printMatrixFromArray(int array[], int rows) {

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < i; j++) cout << "0\t";
        for (int j = i; j < rows; j++) cout << array[index++] << "\t";
        cout << endl;
    }
    cout << endl;
}

int getValidRowCount() {

    int rows = 0;
    while (!(cin >> rows) || rows <= 0) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Bad input, Please re-enter: ";
    }
    return rows;
}

int getValidIntType() {
    int intData = 0;
    while (!(cin >> intData)) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Bad input, Please re-enter: ";
    }
    return intData;
}