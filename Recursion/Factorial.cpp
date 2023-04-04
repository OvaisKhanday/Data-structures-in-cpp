#include <iostream>
using namespace std;

int factorial(int);
int factorialByIterations(int);

int main() {

    int n = 0;
    bool break_loop = true;
    while (break_loop) {
        cout << "Enter number: ";
        cin >> n;

        cout << "Recursion: The factorial of " << n << " is: " << factorial(n) << "\n";
        cout << "Iteration: The factorial of " << n << " is: " << factorialByIterations(n) << "\n";
        cout << "####Brack loop 0-Yes || 1-No: ";
        cin >> break_loop;
    }
    return 0;
}

int factorial(int n) {

    if (n < 0) return -1;
    if (n < 2) return 1;
    return n * factorial(n - 1);
}

int factorialByIterations(int n) {

    if (n < 0) return -1;
    if (n < 2) return 1;

    int result = 1;
    while (n != 1) {
        result *= n;
        n--;
    }
    return result;
}