#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool is_match(const std::string& str)
{
    stack<char> stk;

    for (int i = 0; i < str.size(); i++) {
        switch (str[i]) {
        case '(':
        case '[':
        case '{':
            stk.push(str[i]);
            break;

        case ')': {
            if (stk.empty() || stk.top() != '(')
                return false;
            else
                stk.pop();
        } break;
        case ']': {
            if (stk.empty() || stk.top() != '[')
                return false;
            else
                stk.pop();
        } break;
        case '}': {
            if (stk.empty() || stk.top() != '{')
                return false;
            else
                stk.pop();
        } break;
        default:
            break;
        }
    }
    return stk.empty();
}

int main()
{
    string str;
    cin >> str;
    cout << "is match: " << boolalpha << is_match(str) << endl;
}
