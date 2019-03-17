#ifndef LISTNODE_H_
#define LISTNODE_H_

namespace DSA {

template <typename T>
class List;

template <typename T>
class ListNode;

template <typename T>
using Posi = ListNode<T>*;

template <typename T>
class ListNode {
    friend class List<T>;

private:
    Posi<T> pred;
    Posi<T> succ;

public:
    T data;
    ListNode()
        : pred(nullptr)
        , succ(nullptr)
    {
    }
    ListNode(const T& e, Posi<T> p = nullptr, Posi<T> s = nullptr)
        : data(e)
        , pred(p)
        , succ(s)
    {
    }
    Posi<T> insert_as_pred(const T& e);
    Posi<T> insert_as_succ(const T& e);
};

template <typename T>
Posi<T> ListNode<T>::insert_as_pred(const T& e)
{
    Posi<T> new_node = new ListNode<T>(e, this->pred, this);
    this->pred->succ = new_node;
    this->pred = new_node;
    return new_node;
}

template <typename T>
Posi<T> ListNode<T>::insert_as_succ(const T& e)
{
    Posi<T> new_node = new ListNode<T>(e, this, this->succ);
    this->succ->pred = new_node;
    this->succ = new_node;
    return new_node;
}
}

#endif /* LISTNODE_H_ */
