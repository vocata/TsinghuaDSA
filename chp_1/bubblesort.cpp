#include <algorithm>
#include <iostream>

void bubblesort_A(int arr[], int n)
{
    for (bool sorted = false; (sorted = !sorted); n--)
        for (int i = 1; i < n; i++)
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                sorted = false;
            }
}

void bubblesort_B(int arr[], int n)
{
    do {
        int last = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                last = i;
            }
        }
        n = last;
    } while (n > 0);
}

int main(int argc, char** argv)
{
    int arr[] = { 3, 2, 1, 5, 3, 8, 0 };
    bubblesort_B(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
        std::cout << arr[i] << ' ';

    std::cout << std::endl;
}
