#include <algorithm>
#include <iostream>

using namespace std;

void max2_i(int arr[], int lo, int hi, int& x1, int& x2)        // i: iteration
{
    if (arr[x1 = lo] < arr[x2 = lo + 1])
        std::swap(x1, x2);
    for (int i = lo + 2; i < hi; i++) {
        if (arr[i] > arr[x1])
            x1 = i;
        else if (arr[i] > arr[x2])
            x2 = i;
    }
}

void max2_r(int arr[], int lo, int hi, int& x1, int& x2)        // r: recursion
{
    if (lo + 2 == hi) {
        if (arr[x1 = lo] < arr[x2 = lo + 1])
            swap(x1, x2);
        return;
    }
    if (lo + 3 == hi) {
        max2_r(arr, lo, lo + 2, x1, x2);
        if (arr[lo + 2] > arr[x2]) {
            if (arr[x1] < arr[x2 = lo + 2])
                swap(x1, x2);
        }
        return;
    }

    int mi = (lo + hi) / 2;
    int x1l, x2l;
    int x1r, x2r;
    max2_r(arr, lo, mi, x1l, x2l);
    max2_r(arr, mi, hi, x1r, x2r);

    if (arr[x1l] > arr[x1r]) {
        x1 = x1l;
        x2 = arr[x2l] > arr[x1r] ? x2l : x1r;
    } else {
        x1 = x1r;
        x2 = arr[x2r] > arr[x1l] ? x2r : x1l;
    }
}

int main(int argc, char** argv)
{
    int arr[] = { 1, 3, 2, 0, 54, 21, 23, 44, 24, 21 };
    int x1, x2;
    max2_i(arr, 0, sizeof(arr) / sizeof(int), x1, x2);
    cout << arr[x1] << ' ' << arr[x2] << std::endl;

    return 0;
}
