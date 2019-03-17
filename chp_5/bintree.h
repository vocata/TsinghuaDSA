#ifndef BINTREE_H_
#define BINTREE_H_

#include "binnode.h"

#define HEIGHT(n) ((n) ? (n->height) : (-1))

template <typename T>
class BinTree {
private:
    BinNodePosi<T> __root;
    int __size;

protected:
    virtual int update_height(BinNodePosi<T> node);
    void update_height_above(BinNodePosi<T> node);

public:
    BinTree()
        : __root(nullptr)
        , __size(0)
    {
    }

    BinNodePosi<T> root() const { return __root; }
    int size() const { return __size; }
    int height() const { return HEIGHT(__root); }
    bool empty() const { return !__root; }

    BinNodePosi<T> insert_as_root(const T& elem);
    BinNodePosi<T> insert_as_lc(BinNodePosi<T> node, const T& elem);
    BinNodePosi<T> insert_as_rc(BinNodePosi<T> node, const T& elem);

    template <typename VST>
    void trav_pre(const VST& visit)
    {
        if (__root)
            __root->trav_pre(visit);
    }
    template <typename VST>
    void trav_in(const VST& visit)
    {
        if (__root)
            __root->trav_in(visit);
    }
    template <typename VST>
    void trav_post(const VST& visit)
    {
        if (__root)
            __root->trav_post(visit);
    }
    template <typename VST>
    void trav_level(const VST& visit)
    {
        if (__root)
            __root->trav_level(visit);
    }
};

template <typename T>
int BinTree<T>::update_height(BinNodePosi<T> node)
{
    return node->height = 1 + MAX(HEIGHT(node->l_child), HEIGHT(node->r_child));
}

template <typename T>
void BinTree<T>::update_height_above(BinNodePosi<T> node)
{
    while (node) {
        update_height(node);
        node = node->parent;
    }
}

template <typename T>
BinNodePosi<T> BinTree<T>::insert_as_root(const T& elem)
{
    __size++;
    return __root = new BinNode<T>(elem);
}

template <typename T>
BinNodePosi<T> BinTree<T>::insert_as_lc(BinNodePosi<T> node, const T& elem)
{
    __size++;
    node->insert_as_lc(elem);
    update_height_above(node);
    return node->l_child;
}

template <typename T>
BinNodePosi<T> BinTree<T>::insert_as_rc(BinNodePosi<T> node, const T& elem)
{
    __size++;
    node->insert_as_rc(elem);
    update_height_above(node);
    return node->r_child;
}

#endif /* BINTREE_H_ */
