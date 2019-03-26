#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>

class Eval {
private:
    int _get_index(char op);
    bool _is_unary(char op);
    bool _is_binary(char op);
    void _calc_unary(char op, std::stack<double>& oprd);
    void _calc_binary(char op, std::stack<double>& oprd);
    char _order_between(char top, char cur);
    void _read_number(std::string::const_iterator& iter, std::stack<double>& oprd);
    void _read_number(std::string::const_iterator& iter, std::string& RPN_expr);
    std::string _get_item(std::string::const_iterator& iter, const std::string::const_iterator& end, const std::string& RPN_expr);

    static const char _priority_table[9][9];

public:
    Eval() = default;
    double evaluate(const std::string& expr);
    std::string RPN(const std::string& expr);
    double evaluate_RPN(const std::string& RPN);
};

const char Eval::_priority_table[9][9] = {
    //         +    -    *    /    ^    !    (    )    0
    /* + */ { '>', '>', '<', '<', '<', '<', '<', '>', '>' },
    /* - */ { '>', '>', '<', '<', '<', '<', '<', '>', '>' },
    /* * */ { '>', '>', '>', '>', '<', '<', '<', '>', '>' },
    /* / */ { '>', '>', '>', '>', '<', '<', '<', '>', '>' },
    /* ^ */ { '>', '>', '>', '>', '>', '<', '<', '>', '>' },
    /* ! */ { '>', '>', '>', '>', '>', '>', '<', '>', '>' },
    /* ( */ { '<', '<', '<', '<', '<', '<', '<', '=', ' ' },
    /* ) */ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    /* 0 */ { '<', '<', '<', '<', '<', '<', '<', ' ', '=' },
};
int Eval::_get_index(char op)
{
    int index;
    switch (op) {
    case '+':
        index = 0;
        break;
    case '-':
        index = 1;
        break;
    case '*':
        index = 2;
        break;
    case '/':
        index = 3;
        break;
    case '^':
        index = 4;
        break;
    case '!':
        index = 5;
        break;
    case '(':
        index = 6;
        break;
    case ')':
        index = 7;
        break;
    case '\0':
        index = 8;
        break;
    default:
        index = -1;
        break;
    }
    return index;
}

bool Eval::_is_unary(char op)
{
    if (op == '!')
        return true;
    return false;
}

bool Eval::_is_binary(char op)
{
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
        return true;
    return false;
}

void Eval::_calc_unary(char op, std::stack<double>& oprd)
{
    if (op == '!') {
        int i = oprd.top();
        oprd.pop();
        if (i < 0) {
            printf("%s\n", "invalid syntax");
            exit(-1);
        }

        int result = 1;
        while (i > 0) {
            result *= i;
            i--;
        }
        oprd.push(result);
    }
}

void Eval::_calc_binary(char op, std::stack<double>& oprd)
{
    double l_num, r_num;
    r_num = oprd.top();
    oprd.pop();
    l_num = oprd.top();
    oprd.pop();
    switch (op) {
    case '+':
        oprd.push(l_num + r_num);
        break;
    case '-':
        oprd.push(l_num - r_num);
        break;
    case '*':
        oprd.push(l_num * r_num);
        break;
    case '/':
        oprd.push(l_num / r_num);
        break;
    case '^':
        oprd.push(powl(l_num, r_num));
        break;
    }
}

char Eval::_order_between(char top, char cur)
{
    int top_index = _get_index(top);
    int cur_index = _get_index(cur);
    if (cur_index == -1) {
        printf("%s\n", "invalid syntax");
        exit(-1);
    }

    return _priority_table[top_index][cur_index];
}

void Eval::_read_number(std::string::const_iterator& iter, std::stack<double>& oprd)
{
    double num = 0;
    int dot_count = 0;
    bool dot_flag = false;

    while (isdigit(*iter) || *iter == '.') {
        if (isdigit(*iter)) {
            num = num * 10 + (*iter - 48);
            dot_flag ? dot_count++ : 0;
        } else {
            dot_flag = true;
        }

        iter++;
    }
    num /= pow(10, dot_count);
    oprd.push(num);
}

void Eval::_read_number(std::string::const_iterator& iter, std::string& RPN_expr)
{
    while (isdigit(*iter) || *iter == '.') {
        RPN_expr.push_back(*iter);
        iter++;
    }
    RPN_expr.push_back(' ');
}

std::string Eval::_get_item(std::string::const_iterator& iter, const std::string::const_iterator& end, const std::string& RPN_expr)
{
    std::string item;
    while (iter != end && *iter != ' ')
        item.push_back(*iter++);
    iter != end ? iter++ : iter;
    return item;
}

double Eval::evaluate(const std::string& expr)
{
    std::stack<double> oprd;
    std::stack<char> optr;

    std::string::const_iterator iter = expr.begin();

    optr.push('\0');
    while (!optr.empty()) {
        if (isspace(*iter)) {
            iter++; //skip space
        } else if (isdigit(*iter)) {
            _read_number(iter, oprd);
        } else {
            switch (_order_between(optr.top(), *iter)) {
            case '<':
                optr.push(*iter++);
                break;
            case '=':
                optr.pop();
                iter++;
                break;
            case '>':
                if (_is_unary(optr.top())) {
                    if (oprd.size() < 1) {
                        printf("%s\n", "invalid syntax");
                        exit(-1);
                    }
                    _calc_unary(optr.top(), oprd);
                    optr.pop();
                } else if (_is_binary(optr.top())) {
                    if (oprd.size() < 2) {
                        printf("%s\n", "invalid syntax");
                        exit(-1);
                    }
                    _calc_binary(optr.top(), oprd);
                    optr.pop();
                } else {
                    /* TODO */
                    /* maybe ternary operator */
                    /* this block doesn't work */
                }
                break;
            default:
                printf("%s\n", "invalid syntax");
                exit(-1);
                break;
            }
        }
    }
    return oprd.top();
}

std::string Eval::RPN(const std::string& expr)
{
    std::stack<char> optr;
    std::string RNP_expr;
    std::string::const_iterator iter = expr.begin();

    optr.push('\0');
    while (!optr.empty()) {
        if (isspace(*iter)) {
            iter++;
        } else if (isdigit(*iter)) {
            _read_number(iter, RNP_expr);
        } else {
            switch (_order_between(optr.top(), *iter)) {
            case '<':
                optr.push(*iter++);
                break;
            case '=':
                optr.pop();
                iter++;
                break;
            case '>':
                RNP_expr.push_back(optr.top());
                RNP_expr.push_back(' ');
                optr.pop();
                break;
            default:
                printf("%s\n", "invalid syntax");
                exit(-1);
                break;
            }
        }
    }
    return RNP_expr;
}

double Eval::evaluate_RPN(const std::string& RPN_expr)
{
    std::string::const_iterator iter = RPN_expr.begin();
    std::string::const_iterator end = RPN_expr.end();
    std::stack<double> oprd;
    std::string item;

    while (iter != end) {
        item = _get_item(iter, end, RPN_expr);
        if (_is_unary(item[0])) {
            _calc_unary(item[0], oprd);
        } else if (_is_binary(item[0])) {
            _calc_binary(item[0], oprd);
        } else {
            oprd.push(stod(item));
        }
    }
    return oprd.top();
}

int main(int argc, char* argv[])
{
    std::string expr(argv[1]);
    Eval eval;

    // std::cout << eval.evaluate(expr) << std::endl;
    // std::cout << eval.RPN(expr) << std::endl;
    std::cout << eval.evaluate_RPN(eval.RPN(expr)) << std::endl;

    return 0;
}
