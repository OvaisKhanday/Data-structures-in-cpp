#include <iostream>
#include <math.h>
using namespace std;


void printAllFactorsOfNumber(int);
void printAllFactorsOfNumberByIterations(int);
void printAllFactors(int, int);


int main() {
    int n = 0;
    cout << "Enter: ";
    cin >> n;
    cout << "Recursive: Printing all factors of " << n << ":\n";
    printAllFactorsOfNumber(n);
    cout << "Iterative: Printing all factors of " << n << ":\n";
    printAllFactorsOfNumberByIterations(n);
    return 0;
}

void printAllFactorsOfNumberByIterations(int n) {
    // there can not be any factor in between (n/2, n)-exclusive.
    if (n < 0) n *= -1;

    cout << "[ 1";
    for (int i = 2, j = n / 2; i <= j;i++) {
        if (n % i == 0) cout << ", " << i;
    }
    cout << ", " << n << " ]\n";
}

void printAllFactorsOfNumber(int n) {

    if (n < 0) n *= -1;
    cout << "[ 1";
    printAllFactors(n, 2);
    cout << ", " << n << " ]\n";
}


void printAllFactors(int n, int i) {
    if (i > n / 2) return;
    if (n % i == 0) cout << ", " << i;
    printAllFactors(n, i + 1);
}
