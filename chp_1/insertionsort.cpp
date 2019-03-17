#include <iostream>

void insertionsort(int* arr, int n)
{
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        /* 这里有比较和移动操作，相对于列表，向量还需支付移动所带来的额外开销 */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    int arr[] = { 1, 3, 2, 35, 2, 5, 832, 32 };
    insertionsort(arr, sizeof(arr) / sizeof(int));
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}
