#ifndef BIN_NODE_H_
#define BIN_NODE_H_ 1

#include <iostream>
#include <queue>
#include <stack>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

template <typename T>
struct BinNode;

template <typename T>
using BinNodePosi = BinNode<T>*;

template <typename T>
struct BinNode {
public:
    T data;
    BinNodePosi<T> parent;
    BinNodePosi<T> l_child;
    BinNodePosi<T> r_child;
    int height;

    BinNode()
        : data()
        , parent(nullptr)
        , l_child(nullptr)
        , r_child(nullptr)
        , height(0)
    {
    }
    BinNode(const T& elem, BinNodePosi<T> p = nullptr, BinNodePosi<T> lc = nullptr, BinNodePosi<T> rc = nullptr, int h = 0)
        : data(elem)
        , parent(p)
        , l_child(lc)
        , r_child(rc)
        , height(h)
    {
    }

    int size();
    BinNodePosi<T> insert_as_lc(const T& elem);
    BinNodePosi<T> insert_as_rc(const T& elem);

    template <typename VST>
    void trav_pre(const VST& visit);
    template <typename VST>
    void trav_in(const VST& visit);
    template <typename VST>
    void trav_post(const VST& visit);
    template <typename VST>
    void trav_level(const VST& visit);

private:
    template <typename VST>
    void __trav_pre_r(BinNodePosi<T> node, const VST& visit);
    template <typename VST>
    void __trav_pre_i1(BinNodePosi<T> node, const VST& visit);
    template <typename VST>
    void __trav_pre_i2(BinNodePosi<T> node, const VST& visit);

    template <typename VST>
    void __trav_in_r(BinNodePosi<T> node, const VST& visit);
    template <typename VST>
    void __trav_in_i(BinNodePosi<T> node, const VST& visit);

    template <typename VST>
    void __trav_post_r(BinNodePosi<T> node, const VST& visit);
    template <typename VST>
    void __trav_post_i(BinNodePosi<T> node, const VST& visit);

    template <typename VST>
    void __trav_level(BinNodePosi<T> node, const VST& visit);
};

template <typename T>
int BinNode<T>::size()
{
    int s = 1;
    if (l_child)
        s += l_child->size();
    if (l_child)
        s += r_child->size();
    return s;
}

template <typename T>
BinNodePosi<T> BinNode<T>::insert_as_lc(const T& elem)
{
    return this->l_child = new BinNode<T>(elem, this);
}

template <typename T>
BinNodePosi<T> BinNode<T>::insert_as_rc(const T& elem)
{
    return this->r_child = new BinNode<T>(elem, this);
}

template <typename T>
template <typename VST>
void BinNode<T>::trav_pre(const VST& visit)
{
    //    __trav_pre_r(this, visit);
    //    __trav_pre_i1(this, visit);
    __trav_pre_i2(this, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::trav_in(const VST& visit)
{
    //    __trav_in_r(this, visit);
    __trav_in_i(this, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::trav_post(const VST& visit)
{
    //    __trav_post_r(this, visit);
    __trav_post_i(this, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::trav_level(const VST& visit)
{
    __trav_level(this, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::__trav_pre_r(BinNodePosi<T> node, const VST& visit)
{
    if (node == nullptr)
        return;
    visit(node->data);
    __trav_pre_r(node->l_child, visit);
    __trav_pre_r(node->r_child, visit);
}
template <typename T>
template <typename VST>
void BinNode<T>::__trav_pre_i1(BinNodePosi<T> node, const VST& visit)
{
    std::stack<BinNodePosi<T>> stk;
    if (node)
        stk.push(node);
    while (!stk.empty()) {
        node = stk.top();
        stk.pop();
        visit(node->data);
        if (node->r_child)
            stk.push(node->r_child);
        if (node->l_child)
            stk.push(node->l_child);
    }
}
template <typename T, typename VST>
void visit_along_left_branch(BinNodePosi<T> node, const VST& visit, std::stack<BinNodePosi<T>>& stk)
{
    while (node) {
        visit(node->data);
        if (node->r_child)
            stk.push(node->r_child);
        node = node->l_child;
    }
}
template <typename T>
template <typename VST>
void BinNode<T>::__trav_pre_i2(BinNodePosi<T> node, const VST& visit)
{
    std::stack<BinNodePosi<T>> stk;
    while (true) {
        visit_along_left_branch(node, visit, stk);
        if (stk.empty())
            break;
        node = stk.top();
        stk.pop();
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::__trav_in_r(BinNodePosi<T> node, const VST& visit)
{
    if (node == nullptr)
        return;
    __trav_in_r(node->l_child, visit);
    visit(node->data);
    __trav_in_r(node->r_child, visit);
}
template <typename T>
void go_along_left_branch(BinNodePosi<T> node, std::stack<BinNodePosi<T>>& stk)
{
    while (node) {
        stk.push(node);
        node = node->l_child;
    }
}
template <typename T>
template <typename VST>
void BinNode<T>::__trav_in_i(BinNodePosi<T> node, const VST& visit)
{
    std::stack<BinNodePosi<T>> stk;
    while (true) {
        if (node)
            go_along_left_branch(node, stk);
        if (stk.empty())
            break;
        node = stk.top();
        stk.pop();
        visit(node->data);
        node = node->r_child;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::__trav_post_r(BinNodePosi<T> node, const VST& visit)
{
    if (node == nullptr)
        return;
    __trav_post_r(node->l_child, visit);
    __trav_post_r(node->r_child, visit);
    visit(node->data);
}
template <typename T>
void goto_HLVFL(std::stack<BinNodePosi<T>>& stk)
{
    while (BinNodePosi<T> node = stk.top()) {
        if (node->l_child) {
            if (node->r_child)
                stk.push(node->r_child);
            stk.push(node->l_child);
        } else {
            stk.push(node->r_child);
        }
    }
    stk.pop();
}
template <typename T>
template <typename VST>
void BinNode<T>::__trav_post_i(BinNodePosi<T> node, const VST& visit)
{
    std::stack<BinNodePosi<T>> stk;
    if (node)
        stk.push(node);
    while (!stk.empty()) {
        if (stk.top() != node->parent)
            goto_HLVFL(stk);
        node = stk.top();
        stk.pop();
        visit(node->data);
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::__trav_level(BinNodePosi<T> node, const VST& visit)
{
    std::queue<BinNodePosi<T>> que;
    if (node)
        que.push(node);
    while (!que.empty()) {
        node = que.front();
        que.pop();
        visit(node->data);
        if (node->l_child)
            que.push(node->l_child);
        if (node->r_child)
            que.push(node->r_child);
    }
}

#endif /* BIN_NODE_H_ */
