#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <typename T>
bool is_shuffle(const std::vector<T> &src, const std::vector<T> &tar, int n)
{
    stack<T> stk;
    stack<T> tmp;
    stack<T> target;

    for (int i = 0; i < n; i++) {
        stk.push(src[n - 1 - i]);
        target.push(tar[i]);    //将栈底的移到栈头
    }

    while (!stk.empty()) {
        tmp.push(stk.top());
        stk.pop();
        while (!tmp.empty() && tmp.top() == target.top()) {
            tmp.pop();
            target.pop();
        }
    }
    return tmp.empty();
}

#define NUM 10000000
int main()
{
    /* int tar[] = { 1, 2, 3 }; //< 1, 2, 3 ], < is top of stack */
    /* int src[] = { 3, 2, 1 }; //< 2, 1, 3 ], < is top of stack */
    /* int len = min(sizeof(tar) / sizeof(int), sizeof(src) / sizeof(int)); */
    vector<int> tar;
    vector<int> src;
    for (auto i = 1; i <= NUM; i++) {
        tar.push_back(i);
        src.push_back(NUM + 1 - i);
    }
    int len = min(tar.size(), src.size());


    cout << "is shuffled: " << boolalpha << is_shuffle(src, tar, len) << endl;
}
