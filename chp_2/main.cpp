#include "vector.h"
#include <iostream>

using namespace std;
using namespace DSA;

template <typename T>
struct Display {
    virtual void operator()(const T& e) { cout << e << ' '; }
};
template <typename T>
struct Increase {
    virtual void operator()(T& e) { e++; }
};

int main()
{
    int arr[] = { 12, 2, 5, 4, 7, 9, 42, 77, 23 };
    Vector<int> vec(arr, sizeof(arr) / sizeof(int));

    cout << "disordered: " << vec.disordered() << endl;
    vec.sort(vec.begin(), vec.end());
    cout << "disordered: " << vec.disordered() << endl;

    cout << "search: " << vec.search(23, vec.begin(), vec.end()) << endl;

    vec.traverse(Display<int>());
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    vec.deduplicate();
    vec.traverse(Display<int>());
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    vec.expand();
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    vec.shrink_to_fit();
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    for (int i = 0; i < 4; i++)
        vec.remove(0);
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    for (int i = 0; i < 8; i++)
        vec.insert(0, i);
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    vec.expand();
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    vec.traverse(Display<int>());
    cout << "size: " << vec.size() << ' '
         << "capacity:" << vec.capacity() << endl;

    vec.deduplicate();
    vec.traverse(Display<int>());

    return 0;
}
