#include <iostream>

using namespace std;

unsigned long fib_1(unsigned n)
{
    return n < 2 ? n : fib_1(n - 1) + fib_1(n - 2);
}

static unsigned long tmp;
unsigned long fib_2(unsigned n)
{
    if (n == 0) {
        tmp = 1;
        return 0;
    } else {
        unsigned long pre = fib_2(n - 1);
        unsigned long pre_prev = tmp;
        tmp = pre;
        return pre_prev + pre;
    }
}

unsigned long fib_3(unsigned n)
{
    unsigned long k, l;

    k = 0;
    l = 1;
    while (n-- > 0) {
        l = l + k;
        k = l - k;
    }
    return k;
}

int main(int argc, char** argv)
{
    int n = 10;

    for (int i = 0; i < n; i++) {
        cout << fib_2(i) << endl;
    }

    return 0;
}
