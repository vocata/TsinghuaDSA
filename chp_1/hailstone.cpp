#include <iostream>

using namespace std;

int hailstone(int n);

int main(int argc, char** argv)
{
    int length;

    length = hailstone(7);
    cout << length << endl;
}

int hailstone(int n)
{
    int length;

    length = 1;
    while (1 < n) {
        n = (n % 2) ? (3 * n + 1) : (n / 2);
        length++;
    }

    return length;
}
