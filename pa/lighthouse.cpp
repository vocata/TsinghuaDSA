#include <iostream>

using std::cout;
using std::endl;

int inv_between(int* arr, int lo, int mi, int hi, int inv_num)
{
    int l_len = mi - lo;
    int r_len = hi - mi;
    arr = arr + lo;
    int* arr_l = new int[l_len];
    int* arr_r = arr + l_len;

    for (int i = 0; i < l_len; i++)
        arr_l[i] = arr[i];

    /* 冗余版 */
    /* for (int i = 0, j = 0, k = 0; j < l_len || k < r_len;) { */
    /*     if( k < r_len && (l_len <= j || arr_r[k] < arr_l[j]) ) */
    /*         arr[i++] = arr_r[k++]; */
    /*     if( j < l_len && (r_len <= k || arr_l[j] <= arr_r[k]) ) */
    /*         arr[i++] = arr_l[j++]; */
    /* } */

    /* 精简版 */
    for (int i = 0, j = 0, k = 0; j < l_len;) {
        if (k < r_len && arr_r[k] < arr_l[j]) {
            arr[i++] = arr_r[k++];
            inv_num += (l_len - j);
        }
        if (r_len <= k || arr_l[j] <= arr_r[k]) {
            arr[i++] = arr_l[j++];
        }
    }
    delete[] arr_l;

    return inv_num;
}

int inv_inside(int* arr, int lo, int hi)
{
    if (hi - lo < 2)
        return 0;

    int mi = (lo + hi) >> 1;
    int inv_num_l = inv_inside(arr, lo, mi);
    int inv_num_r = inv_inside(arr, mi, hi);
    return inv_between(arr, lo, mi, hi, inv_num_l + inv_num_r);
}

int main()
{
    int arr[] = {3, 2, 1};
    /* int arr[] = { 3, 2, 8, 2, 4, 8, 29, 21, 4, 38, 21, 98, 33, 47 }; */
    /* int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; */
    int len = sizeof(arr) / sizeof(int);

    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;

    int inv_num = inv_inside(arr, 0, len);

    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl << "inv_num: " << inv_num << endl;
}
