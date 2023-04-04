#include <iostream>
using namespace std;


void toh(int);
void toh(int, char, char, char);

int main() {

    toh(3);
    return 0;
}


void toh(int disks) {
    if (disks <= 0) return;
    toh(disks, 'A', 'B', 'C');
}
void toh(int disks, char a, char b, char c) {
    if (disks == 0) return;

    toh(disks - 1, a, c, b);
    cout << a << " -> " << c << "\n";
    toh(disks - 1, b, a, c);

}