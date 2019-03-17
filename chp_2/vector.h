#ifndef VECTOR_H_
#define VECTOR_H_

#include "fib.h"
#include <cassert>

namespace DSA {
#define CAPACITY_DEFAULT 3
typedef int Rank;

template <typename T>
class Vector {
private:
    int __capacity;
    Rank __size;
    T* __elem;

protected:
    void _copy_from(const T* arr, Rank lo, Rank hi);
    Rank _bin_search_A(const T& e, Rank lo, Rank hi) const;
    Rank _bin_search_B(const T& e, Rank lo, Rank hi) const;
    Rank _bin_search_C(const T& e, Rank lo, Rank hi) const;
    Rank _fib_search_A(const T& e, Rank lo, Rank hi) const;
    Rank _fib_search_B(const T& e, Rank lo, Rank hi) const;
    Rank _bubble_A(Rank lo, Rank hi);
    Rank _bubble_B(Rank lo, Rank hi);
    void _bubble_sort(Rank lo, Rank hi);
    void _merge(Rank lo, Rank mi, Rank hi);
    void _merge_sort(Rank lo, Rank hi);

public:
    Vector(int c = CAPACITY_DEFAULT, Rank size = 0, T init = 0);
    Vector(const T* arr, Rank size) { _copy_from(arr, 0, size); }
    Vector(const T* arr, Rank lo, Rank hi) { _copy_from(arr, lo, hi); }
    Vector(const Vector<T>& vec) { _copy_from(vec.__elem, 0, vec.__size); }
    Vector(const Vector<T>& vec, Rank size) { _copy_from(vec.__elem, 0, size); }
    Vector(const Vector<T>& vec, Rank lo, Rank hi) { _copy_from(vec.__elem, lo, hi); }
    Vector(Vector<T>&& vec);
    ~Vector() { delete[] __elem; }

    Vector<T>& operator=(const Vector<T>& vec);
    Vector<T>& operator=(Vector<T>&& vec);
    T& operator[](Rank r) { return __elem[r]; }
    const T& operator[](Rank r) const { return __elem[r]; }

    int capacity() const { return __capacity; }
    int size() const { return __size; }
    bool empty() const { return !__size; }
    int disordered() const;
    Rank begin() const { return 0; }
    Rank end() const { return __size; }
    T front() const { return __elem[0]; }
    T back() const { return __elem[__size - 1]; }

    void expand();
    void shrink_to_fit();

    T get(Rank r) const { return __elem[r]; }
    void put(Rank r, T elem) { __elem[r] = elem; }

    Rank insert(Rank r, const T& e);
    int remove(Rank lo, Rank hi);
    T remove(Rank r);

    Rank find(const T& e, Rank lo, Rank hi) const;
    int deduplicate();

    void sort(Rank lo, Rank hi);
    Rank search(const T& e, Rank lo, Rank hi) const;
    int uniquify();

    void clear();

    template <typename VST>
    void traverse(VST&& visit);
};

template <typename T>
Vector<T>::Vector(int c, Rank size, T init)
{
    __elem = new T[__capacity = c];
    for (__size = 0; __size < size; __elem[__size++] = init)
        ;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& vec)
{
    T* elem = vec.__elem;
    vec.__elem = __elem;
    __elem = elem;
    __size = vec.__size;
    __capacity = vec.__capacity;
}

template <typename T>
void Vector<T>::_copy_from(const T* arr, Rank lo, Rank hi)
{
    __elem = new T[__capacity = 2 * (hi - lo)];
    for (__size = 0; lo < hi; __elem[__size++] = arr[lo++])
        ;
}

template <typename T>
Rank Vector<T>::_bin_search_A(const T& e, Rank lo, Rank hi) const
{
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < __elem[mi])
            hi = mi;
        else if (__elem[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}

template <typename T>
Rank Vector<T>::_bin_search_B(const T& e, Rank lo, Rank hi) const
{
    while (1 < hi - lo) {
        Rank mi = (hi + lo) >> 1;
        e < __elem[mi] ? hi = mi : lo = mi;
    }
    return e == __elem[lo] ? lo : -1;
}

template <typename T>
Rank Vector<T>::_bin_search_C(const T& e, Rank lo, Rank hi) const
{
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        e < __elem[mi] ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T>
Rank Vector<T>::_fib_search_A(const T& e, Rank lo, Rank hi) const
{
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get())
            fib.pre();
        Rank mi = lo + fib.get() - 1;
        if (e < __elem[mi])
            hi = mi;
        else if (__elem[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}

template <typename T>
Rank Vector<T>::_fib_search_B(const T& e, Rank lo, Rank hi) const
{
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get())
            fib.pre();
        Rank mi = lo + fib.get() - 1;
        e < __elem[mi] ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T>
Rank Vector<T>::_bubble_A(Rank lo, Rank hi)
{
    bool sorted = true;
    while (++lo < hi) {
        if (__elem[lo - 1] > __elem[lo]) {
            T tmp = __elem[lo - 1];
            __elem[lo - 1] = __elem[lo];
            __elem[lo] = tmp;
            sorted = false;
        }
    }
    return sorted;
}

template <typename T>
Rank Vector<T>::_bubble_B(Rank lo, Rank hi)
{
    Rank last = lo;
    while (++lo < hi) {
        if (__elem[lo - 1] > __elem[lo]) {
            T tmp = __elem[lo - 1];
            __elem[lo - 1] = __elem[lo];
            __elem[lo] = tmp;
            last = lo;
        }
    }
    return last;
}

template <typename T>
void Vector<T>::_bubble_sort(Rank lo, Rank hi)
{
    /* while (!_bubble_A(lo, hi--)) */
    /*     ; */
    while (lo < (hi = _bubble_B(lo, hi)))
        ;
}

template <typename T>
void Vector<T>::_merge(Rank lo, Rank mi, Rank hi)
{
    int lb = mi - lo;
    int lc = hi - mi;
    T* A = __elem + lo;
    T* B = new T[mi - lo];
    T* C = __elem + mi;

    for (Rank i = 0; i < lb; i++)
        B[i] = A[i];
    for (Rank i = 0, j = 0, k = 0; j < lb;) {
        if (lc <= k || B[j] <= C[k])
            A[i++] = B[j++]; // B[j] <= C[k] 保证了稳定性
        if (k < lc && C[k] < B[j])
            A[i++] = C[k++];
    }

    delete[] B;
}

template <typename T>
void Vector<T>::_merge_sort(Rank lo, Rank hi)
{
    if (hi - lo < 2)
        return;
    Rank mi = (lo + hi) >> 1;
    _merge_sort(lo, mi);
    _merge_sort(mi, hi);
    _merge(lo, mi, hi);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vec)
{
    delete[] __elem;
    _copy_from(vec.__elem, 0, vec.__size);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& vec)
{
    T* elem = vec.__elem;
    vec.__elem = __elem;
    __elem = elem;
    __size = vec.__size;
    __capacity = vec.__capacity;

    return *this;
}

template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for (int i = 1; i < __size; i++) {
        n += (__elem[i - 1] > __elem[i]);
    }
    return n;
}

template <typename T>
void Vector<T>::expand()
{
    if (__size < __capacity)
        return;
    __capacity = __capacity > CAPACITY_DEFAULT ? __capacity : CAPACITY_DEFAULT;
    T* old_elem = __elem;
    __elem = new T[__capacity <<= 1];
    for (int i = 0; i < __size; i++) {
        __elem[i] = old_elem[i];
    }
    delete[] old_elem;
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (__capacity < CAPACITY_DEFAULT << 1)
        return;
    if (__capacity < __size << 2)
        return;
    T* old_elem = __elem;
    __elem = new T[__capacity >>= 1];
    for (int i = 0; i < __size; i++)
        __elem[i] = old_elem[i];
    delete[] old_elem;
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
    expand();
    for (int i = __size; i > r; i--)
        __elem[i] = __elem[i - 1];
    __elem[r] = e;
    __size++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo >= hi)
        return 0;
    while (hi < __size) {
        __elem[lo++] = __elem[hi++];
    }
    __size = lo;
    shrink_to_fit();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    assert(r < __size);
    T e = __elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const
{
    while (lo < hi-- && e != __elem[hi])
        ;
    return hi;
}

template <typename T>
int Vector<T>::deduplicate()
{
    int old_size, i;

    old_size = __size;
    i = 1;
    while (i != __size) {
        if (find(__elem[i], 0, i) < 0)
            i++;
        else
            remove(i);
    }
    return old_size - __size;
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    /* _bubble_sort(lo, hi); */
    _merge_sort(lo, hi);
}

template <typename T>
Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const
{
    /* return _bin_search_A(e, lo, hi); */
    /* return _bin_search_B(e, lo, hi); */
    return _bin_search_C(e, lo, hi);
    /* return _fib_search_A(e, lo, hi); */
    /* return _fib_search_B(e, lo, hi); */
}

template <typename T>
int Vector<T>::uniquify()
{
    int i, j;
    i = j = 0;
    while (++j < __size) {
        if (__elem[i] != __elem[j])
            __elem[++i] = __elem[j];
    }
    __size = ++i;
    shrink_to_fit();
    return j - i;
}

template <typename T>
void Vector<T>::clear()
{
    delete[] __elem;
    __size = 0;
    __capacity = CAPACITY_DEFAULT;
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST&& visit)
{
    for (int i = 0; i < __size; i++)
        visit(__elem[i]);
}
}

#endif /* VECTOR_H_ */
