#include <iostream>
#include <math.h>
using namespace std;

template <class U>
class term {
public:
    U coeff; // coefficient
    int exp; // exponent.
    term<U>* next;

    term() {
        this->coeff = 0;
        this->exp = 0;
        this->next = NULL;
    }

    term(U coeff) {
        this->coeff = coeff;
        this->exp = 0;
        this->next = NULL;
    }

    term(U coeff, int exp) {
        this->coeff = coeff;
        this->exp = exp;
        this->next = NULL;
    }
};

template <class T>
class Poly {
    term<T>* head;
    void freePoly();
    void push(T coeff, int exp);
    term<T>* tail;

public:
    Poly() {
        this->head = NULL;
        this->tail = NULL;
    }
    ~Poly() {
        freePoly();
    }
    void createPoly();
    void displayPoly();
    // add two polynomials and put result in (this).
    void addPoly(Poly, Poly);
    T calcPoly(T);
};
int main() {

    Poly<int> p1;
    p1.createPoly();

    cout << "Polynomial created is: " << endl;
    p1.displayPoly();
    cout << "If x = 3 then the value of polynomial is: " << p1.calcPoly(3) << endl;
    cout << "If x = 0 then the value of polynomial is: " << p1.calcPoly(0) << endl;
    cout << "If x = -3 then the value of polynomial is: " << p1.calcPoly(-3) << endl;


    // Poly<float> p2;
    // p2.createPoly();

    // cout << "Polynomial created is: " << endl;
    // p2.displayPoly();
    // cout << "If x = 3.2 then the value of polynomial is: " << p2.calcPoly(3.2) << endl;
    // cout << "If x = 0 then the value of polynomial is: " << p2.calcPoly(0) << endl;
    // cout << "If x = -3.2 then the value of polynomial is: " << p2.calcPoly(-3.2) << endl;


    // Poly<int> p3;
    // p3.displayPoly();
    // p3.displayPoly();

    // Poly<int> p4;
    // p4.createPoly();
    // p4.displayPoly();

    // Poly<int> p5;
    // p5.addPoly(p3, p4);
    // cout << "added polynomials" << endl;
    // p5.displayPoly();
    return 0;
}

// !create poly
template <class T>
void Poly<T>::createPoly() {

    freePoly();
    T coeff = 0;
    int exp = 0;
    char input = ' ';
    int terms = 0;
    cout << "Here you are going to create a polynomial" << endl;

    while (input != 'S' && input != 's') {
        cout << endl << "Enter coefficient of " << ++terms << " term: ";
        while (!(cin >> coeff) || coeff == 0) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, please re-enter: ";
        }
        cout << "Enter exponent of " << terms << " term: ";
        while (!(cin >> exp) || exp < 0) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, please re-enter: ";
        }

        term<T>* newTerm = new term<T>(coeff, exp);
        if (newTerm == NULL) return;

        if (this->head == NULL) {
            this->head = newTerm;
        } else {
            term<T>* prev = NULL;
            term<T>* current = this->head;
            while (current != NULL) {
                if (current->exp == exp) {
                    // adding coefficients if the exponents are same.
                    current->coeff = current->coeff + coeff;
                    delete newTerm;
                    break;
                }
                if (current->exp < exp) {
                    if (prev == NULL) {
                        // meaning node is to be inserted at front.
                        newTerm->next = this->head;
                        this->head = newTerm;
                        break;
                    } else {
                        prev->next = newTerm;
                        newTerm->next = current;
                        break;
                    }
                }
                prev = current;
                current = current->next;
            }
            if (current == NULL) {
                // it means node to be inserted at end.
                prev->next = newTerm;
            }
        }

        cout << "----> YOU HAD ENTERED " << terms << " TERM(s)," << endl;
        cout << "----> Do you want to submit the polynomial or add another term," << endl;
        cout << "----> Enter (S) for submit or press any key for adding another term: ";
        while (!(cin >> input)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Bad input, please re-enter: ";
        }
    }
}

// !displayPoly
template <class T>
void Poly<T>::displayPoly() {

    if (this->head == NULL) {
        cout << "Empty Polynomial" << endl;
        return;
    }
    cout << this->head->coeff << "x^" << this->head->exp;
    term<T>* current = this->head->next;
    while (current != NULL) {
        cout << " + " << current->coeff;
        if (current->exp != 0) {
            if (current->exp == 1) {
                cout << "x";
            } else
                cout << "x^" << current->exp;
        }
        current = current->next;
    }
    cout << endl;
}

// !add poly
template <class T>
void Poly<T>::addPoly(Poly<T> poly1, Poly<T> poly2) {

    this->freePoly();

    if (poly1.head == NULL && poly2.head == NULL) return;

    if (poly2.head == NULL) {
        term<T>* current = poly1.head;
        while (current != NULL) {
            this->push(current->coeff, current->exp);
            current = current->next;
        }
        return;
    }

    if (poly1.head == NULL) {
        term<T>* current = poly2.head;
        while (current != NULL) {
            this->push(current->coeff, current->exp);
            current = current->next;
        }
        return;
    }

    // else add polynomials.
    term<T>* poly1_pointer = poly1.head;
    term<T>* poly2_pointer = poly2.head;

    while (poly1_pointer != NULL && poly2_pointer != NULL) {
        // poly1 == poly2
        if (poly1_pointer->exp == poly2_pointer->exp) {
            this->push(poly1_pointer->coeff + poly2_pointer->coeff, poly1_pointer->exp);
            poly1_pointer = poly1_pointer->next;
            poly2_pointer = poly2_pointer->next;
        }
        // poly1 > poly2
        else if (poly1_pointer->exp > poly2_pointer->exp) {
            this->push(poly1_pointer->coeff, poly1_pointer->exp);
            poly1_pointer = poly1_pointer->next;
        }
        // poly2 > poly1
        else if (poly2_pointer->exp > poly1_pointer->exp) {
            this->push(poly2_pointer->coeff, poly2_pointer->exp);
            poly2_pointer = poly2_pointer->next;
        }
    }

    if (poly1_pointer == NULL) {
        while (poly2_pointer != NULL) {
            this->push(poly2_pointer->coeff, poly2_pointer->exp);
            poly2_pointer = poly2_pointer->next;
        }
    } else {
        while (poly1_pointer != NULL) {
            this->push(poly1_pointer->coeff, poly1_pointer->exp);
            poly1_pointer = poly1_pointer->next;
        }
    }
}

//!calculate polynomial
template <class T>
T Poly<T>::calcPoly(T x) {

    T result = 0;
    term<T>* current = this->head;

    while (current != NULL) {
        result += (current->coeff) * pow(x, current->exp);
        current = current->next;
    }
    return result;
}

// !push -private
template <class T>
void Poly<T>::push(T coeff, int exp) {

    term<T>* newTerm = new term<T>(coeff, exp);
    if (newTerm == NULL) return;

    if (this->head == NULL) {
        this->head = newTerm;
        this->tail = newTerm;
        return;
    }

    this->tail->next = newTerm;
    this->tail = newTerm;
}

// !free poly
template <class T>
void Poly<T>::freePoly() {
    term<T>* current = this->head;
    while (this->head != NULL) {
        this->head = this->head->next;
        delete current;
        current = this->head;
    }
    this->tail = NULL;
}