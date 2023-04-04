#include <iostream>
using namespace std;

// Taylor series using Homer's rule.
double taylor(int, int);
double taylorByIterations(int, int);

int main() {

    int x, n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n: ";
    cin >> n;
    cout << "Recursive: taylor(" << x << "," << n << "): " << taylor(x, n) << endl;
    cout << "Iterative: taylor(" << x << "," << n << "): " << taylorByIterations(x, n) << endl;
    return 0;
}

double taylorByIterations(int x, int n) {
    if (n <= 0) return 0;
    double result = 1.0;
    while (n > 0) {
        result = 1 + (x * result) / n;
        n--;
    }
    return result;
}

double taylor(int x, int n) {
    static double result = 1;
    if (n <= 0) return result;
    result = 1 + (x * result) / n;
    return taylor(x, n - 1);
}