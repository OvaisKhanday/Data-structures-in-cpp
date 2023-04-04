#include <iostream>
using namespace std;

int gcd(int, int);
int gcdByIterations(int, int);

int main() {

    int x, y;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    cout << "Recursive: GCD of " << x << " and " << y << " is: " << gcd(x, y) << endl;
    cout << "Iterative: GCD of " << x << " and " << y << " is: " << gcdByIterations(x, y) << endl;

    return 0;
}


// int gcd(int x, int y) {
//     if (x == 0) return y;
//     if (y == 0) return x;
//     if (x == y)return x;

//     x = x < 0 ? x * -1 : x;
//     y = y < 0 ? y * -1 : y;

//     if (x > y) return gcd(x - y, y);
//     return gcd(x, y - x);
// }

int gcd(int x, int y) {
    x = x < 0 ? x * -1 : x;
    y = y < 0 ? y * -1 : y;
    if (y != 0) return gcd(y, x % y);
    return x;
}

int gcdByIterations(int x, int y) {
    if (x == 0) return y;
    if (y == 0) return x;
    if (x == y)return x;

    x = x < 0 ? x * -1 : x;
    y = y < 0 ? y * -1 : y;

    while (x != y) {
        if (x > y) x = x - y;
        else y = y - x;
    }
    return x;
}