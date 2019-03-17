#ifndef LIST_H_
#define LIST_H_

#include "listnode.h"
#include <cassert>
#include <cstdio>

namespace DSA {

typedef int Rank;

template <typename T>
class List {
private:
    int __size;
    Posi<T> __head;
    Posi<T> __trailer;

protected:
    void _init();
    void _clear();
    void _copy_from(const T* arr, Rank lo, Rank hi);
    void _copy_from(const List& lst, Posi<T> begin, Posi<T> end);

public:
    List() { _init(); }
    List(const T* arr, Rank size);
    List(const T* arr, Rank lo, Rank hi);
    List(const List<T>& lst);
    List(const List<T>& lst, Posi<T> begin, Posi<T> end);
    List(List<T>&& lst);
    ~List();

    T& operator[](Rank r);
    const T& operator[](Rank r) const;
    List<T>& operator=(const List<T>& lst);
    List<T>& operator=(List<T>&& lst);

    int size() const { return __size; }
    bool empty() const { return !__size; }
    int disordered() const;
    Posi<T> begin() const { return __head->succ; }
    Posi<T> end() const { return __trailer; }
    T front() const;
    T back() const;
    Posi<T> find(const T& e, Posi<T> p, int n) const;

    T remove(Posi<T> p);
};

template <typename T>
void List<T>::_init()
{
    __head = new ListNode<T>;
    __trailer = new ListNode<T>;
    __head->succ = __trailer;
    __trailer->pred = __head;
    __size = 0;
}

template <typename T>
void List<T>::_clear()
{
    Posi<T> cur = __head;
    while (cur->succ != __trailer) {
        Posi<T> tmp = cur->succ;
        cur->succ = tmp->succ;
        tmp->succ->pred = cur;
        delete tmp;
    }
    __size = 0;
}

template <typename T>
void List<T>::_copy_from(const T* arr, Rank lo, Rank hi)
{
    Posi<T> cur = __head;
    while (lo < hi) {
        Posi<T> node = new ListNode<T>;
        node->data = arr[lo++];
        node->pred = cur;
        node->succ = cur->succ;

        node->pred->succ = node;
        node->succ->pred = node;

        cur = node;
        __size++;
    }
}

template <typename T>
void List<T>::_copy_from(const List& lst, Posi<T> begin, Posi<T> end)
{
    Posi<T> pre = __head;
    Posi<T> cur = begin;
    while (cur != end) {
        Posi<T> node = new ListNode<T>;
        node->data = cur->data;
        node->pred = pre;
        node->succ = pre->succ;

        node->pred->succ = node;
        node->succ->pred = node;

        pre = node;
        cur = cur->succ;
        __size++;
    }
}

template <typename T>
List<T>::List(const T* arr, Rank size)
{
    _init();
    _copy_from(arr, 0, size);
}

template <typename T>
List<T>::List(const T* arr, Rank lo, Rank hi)
{
    _init();
    _copy_from(arr, lo, hi);
}

template <typename T>
List<T>::List(const List<T>& lst)
{
    _init();
    _copy_from(lst, lst.begin(), lst.end());
}

template <typename T>
List<T>::List(const List<T>& lst, Posi<T> begin, Posi<T> end)
{
    _init();
    _copy_from(lst, begin, end);
}

template <typename T>
List<T>::List(List<T>&& lst)
{
    _init();
    Posi<T> head = lst.__head;
    lst.__head = __head;
    __head = head;
    Posi<T> trailer = lst.__trailer;
    lst.__trailer = __trailer;
    __trailer = trailer;
    __size = lst.__size;
}

template <typename T>
List<T>::~List()
{
    _clear();
    delete __head;
    delete __trailer;
}

template <typename T>
T& List<T>::operator[](Rank r)
{
    assert(r < __size);
    Posi<T> cur;
    if (r <= (__size >> 1)) {
        cur = __head;
        for (int i = -1; i < r; i++) {
            cur = cur->succ;
        }
    } else {
        cur = __trailer;
        for (int i = __size; r < i; i--) {
            cur = cur->pred;
        }
    }
    return cur->data;
}

template <typename T>
const T& List<T>::operator[](Rank r) const
{
    List<T>& tmp = const_cast<List<T>&>(*this);
    return tmp[r];
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& lst)
{
    _clear();
    _copy_from(lst, lst.begin(), lst.end());
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& lst)
{
    Posi<T> head = lst.__head;
    lst.__head = __head;
    __head = head;
    Posi<T> trailer = lst.__trailer;
    lst.__trailer = __trailer;
    __trailer = trailer;
    __size = lst.__size;
    return *this;
}

template <typename T>
int List<T>::disordered() const
{
    if (__size < 2)
        return 0;

    int num = 0;
    Posi<T> cur = __head->succ;
    while (cur->succ != __trailer) {
        if (cur->data > cur->succ->data)
            num++;
        cur = cur->succ;
    }
    return num;
}

template <typename T>
T List<T>::front() const
{
    assert(!empty());
    return __head->succ->data;
}

template <typename T>
T List<T>::back() const
{
    assert(!empty());
    return __trailer->pred->data;
}

template <typename T>
Posi<T> List<T>::find(const T& e, Posi<T> p, int n) const
{
    if (n == 0)
        return nullptr;
    else if (n > 0) {
        while (0 < n--) {
            if (e == (p = p->succ)->data)
                return p;
        }
    } else {
        while (n++ < 0) {
            if (e == (p = p->pred)->data)
                return p;
        }
    }

    return nullptr;
}

template <typename T>
T List<T>::remove(Posi<T> p)
{
    T tmp = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;

    delete p;
    __size--;
    return tmp;
}
}

#endif /* LIST_H_ */
