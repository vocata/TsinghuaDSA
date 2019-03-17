#include <cassert>
#include <cstdint>
#include <iostream>
#include <stack>

using namespace std;

template <typename T>
void convert(stack<T>& output, int64_t num, int base = 2)
{
    assert(1 < base && base <= 16);
    char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    while (num != 0) {
        output.push(digit[num % base]);
        num /= base;
    }
}

int main()
{
    int64_t a = 10;
    stack<char> output;
    convert(output, a);
    for (; !output.empty(); output.pop()) {
        cout << output.top();
    }
    cout << endl;
}
