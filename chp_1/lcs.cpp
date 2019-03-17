#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int lcs_1(const string& str1, int m, const string& str2, int n)
{
    if (m == 0 || n == 0)
        return 0;

    int len;
    if (str1[m - 1] == str2[n - 1]) {
        len = lcs_1(str1, m - 1, str2, n - 1) + 1;
    } else {
        len = max(lcs_1(str1, m - 1, str2, n), lcs_1(str1, m, str2, n - 1));
    }

    return len;
}

int lcs_2(const string& str1, int m, const string& str2, int n)
{
    vector<vector<int>> matrix(m + 1, vector<int>(n + 1));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (str1[i] == str2[j]) {
                matrix[i + 1][j + 1] = matrix[i][j] + 1;
            } else {
                matrix[i + 1][j + 1] = max(matrix[i + 1][j], matrix[i][j + 1]);
            }
        }

    return matrix[m][n];
}

int main()
{
    string str1("iiiiiiiiiiiiiiiiiiiiiiiiii");
    string str2("iiiiiifjslfiiiiiilfjslajli");

    int lcs1_len = lcs_1(str1, str1.length(), str2, str2.length());
    int lcs2_len = lcs_2(str1, str1.length(), str2, str2.length());
    cout << lcs1_len << endl << lcs2_len << endl;
}
