#include <iostream>
using namespace std;


int nthFibonacciNumber(int);
int nthFibonacciNumberByIterations(int);

void printNFibonacciNumbers(int);
void printNFibonacciNumbersByIterations(int);


int main() {

    int n = 0;
    bool break_loop = true;
    while (break_loop) {
        cout << "Enter number: ";
        cin >> n;

        cout << "Recursion: The nth(" << n << ") fibonacci number is: " << nthFibonacciNumber(n) << "\n";
        cout << "Iteration: The nth(" << n << ") fibonacci number is: " << nthFibonacciNumberByIterations(n) << "\n";
        cout << "Recursion: Printing " << n << " fibonacci numbers\n";
        printNFibonacciNumbers(n);
        cout << "Iteration: Printing " << n << " fibonacci numbers\n";
        printNFibonacciNumbersByIterations(n);
        cout << "####Brack loop 0-Yes || 1-No: ";
        while (!(cin >> break_loop)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "####Brack loop 0-Yes || 1-No: ";
        }
    }
    return 0;
}

int nthFibonacciNumber(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 0;
    if (n == 2) return 1;
    return nthFibonacciNumber(n - 1) + nthFibonacciNumber(n - 2);
}

int nthFibonacciNumberByIterations(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 0;
    if (n == 2) return 1;

    int first_fib = 0;
    int second_fib = 1;
    int sum_fib = 0;

    --n;
    while (--n) {
        sum_fib = first_fib + second_fib;
        first_fib = second_fib;
        second_fib = sum_fib;
    }
    return sum_fib;
}

void printNFibonacciNumbers(int n) {
    if (n <= 0) return;

    cout << "0";
    for (int i = 2; i <= n; i++) {
        cout << ", " << nthFibonacciNumber(i);
    }
    cout << "\n";
}

void printNFibonacciNumbersByIterations(int n) {

    if (n <= 0) return;

    int first_fib = 1;
    int second_fib = 1;
    int sum_fib = 1;

    cout << "0\t";
    n--;

    while (n--) {
        cout << first_fib << "\t";
        if (n == 0) break;
        sum_fib = first_fib + second_fib;
        first_fib = second_fib;
        second_fib = sum_fib;
    }
    cout << "\n";
}