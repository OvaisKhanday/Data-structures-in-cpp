// WAP to convert sparse matrix into non-zero form and vice versa.
// I'm going to use the coordinate list/3-column representation.

#include <iostream>
using namespace std;


template <class U>
class Element {
public:
    int i; // for row
    int j; // for col
    U data;
};

template <class T>
class SparseMatrix {
    int rows;
    int cols;
    int totalElements; // total non-zero elements.
    Element<T>* elements;

    int getValidRowDimensions();
    void enterData();
public:
    SparseMatrix() {
        this->rows = 0;
        this->cols = 0;
        this->totalElements = 0;
        this->elements = NULL;
    }
    ~SparseMatrix() {
        delete[] elements;
    }
    void createSparse();
    void displaySparse();
};




int main() {

    SparseMatrix<int> matrix;
    matrix.createSparse();
    matrix.displaySparse();

    SparseMatrix<char> matrix2;
    matrix2.createSparse();
    matrix2.displaySparse();

    SparseMatrix<float> matrix3;
    matrix3.createSparse();
    matrix3.displaySparse();
    return 0;
}

// !Create Sparse
template <class T>
void SparseMatrix<T>::createSparse() {

    cout << "ENTER DATA FOR SPARSE MATRIX" << endl;
    cout << "Enter the number of rows: ";
    this->rows = getValidRowDimensions();
    cout << "Enter the number of columns: ";
    this->cols = getValidRowDimensions();
    int max_possible_elements = this->rows * this->cols;
    do
    {
        cout << "Enter the number of non-zero elements [1 - " << max_possible_elements << " ]: ";
        this->totalElements = getValidRowDimensions();
    } while (this->totalElements <= 0 || this->totalElements > max_possible_elements);

    this->elements = new Element<T>[this->totalElements];
    this->enterData();
}

// !enter data
template <class T>
void SparseMatrix<T>::enterData() {

    cout << "ENTER DATA OF SPARSE MATRIX" << endl;
    cout << "|----------------------------------------------------------------|" << endl;
    cout << "REMEMBER TO ENTER DATA IN ORDER OF TOP TO BOTTOM AND LEFT TO RIGHT" << endl;
    for (int i = 0; i < this->totalElements; i++) {
        cout << "|--------------------------------------------|" << endl;
        cout << "----------Enter data for " << i + 1 << " element----------" << endl;
        cout << "Enter data: ";
        // getting valid data
        while (!(cin >> this->elements[i].data)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, please re-enter: ";
        }

        // getting valid row no.
        cout << "Enter row number for " << this->elements[i].data << " in range of [1 - " << this->rows << "]: ";
        while (1) {
            if (!(cin >> this->elements[i].i)) { // <-- if input is not of valid data type.
                cout << "Bad input, please re-enter in range of [1 - " << this->rows << "]: ";
                continue;
            }
            if (this->elements[i].i >= 1 && this->elements[i].i <= this->rows) break;
            cout << "Bad input, please re-enter in range of [1 - " << this->rows << "]: ";
        }
        (this->elements[i].i)--;

        // getting valid col no.
        cout << "Enter column number for " << this->elements[i].data << " in range of [1 - " << this->cols << "]: ";
        while (1) {
            if (!(cin >> this->elements[i].j)) { // <-- if input is not of valid data type.
                cout << "Bad input, please re-enter in range of [1 - " << this->cols << "]: ";
                continue;
            }
            if (this->elements[i].j >= 1 && this->elements[i].j <= this->cols) break;
            cout << "Bad input, please re-enter in range of [1 - " << this->cols << "]: ";
        }
        (this->elements[i].j)--;
    }

}

// !display sparse
template <class T>
void SparseMatrix<T>::displaySparse() {
    if (this->rows <= 0) return;
    cout << endl << "PRINTING SPARSE MATRIX" << endl;
    int index = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->elements[index].i == i && this->elements[index].j == j) {
                cout << this->elements[index].data << "\t";
                index++;
            } else cout << "0\t";
        }
        cout << endl;
    }
}



template <class T>
int SparseMatrix<T>::getValidRowDimensions() {

    int intData = 0;
    while (!(cin >> intData) || intData <= 0) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Bad input, Please re-enter: ";
    }
    return intData;
}