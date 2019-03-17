#include "list.h"
#include <iostream>

using namespace std;
using namespace DSA;

int main()
{
    int arr[] = { 1, 2, 3, 3, 5, 8, 2, 93, 21 };
    int len = sizeof(arr) / sizeof(int);
    List<int> l(arr, len);
    List<int> lst(l);

    Posi<int> rst = lst.find(7, lst.end(), -lst.size());
    if (rst != nullptr) {
        cout << rst->data << endl;
    }

    for (int i = 0; i < lst.size(); i++)
        cout << lst[i] << ' ';
    cout << endl
         << lst.disordered();
    cout << endl;
}
