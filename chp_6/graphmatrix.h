#ifndef GRAPHMATRIX_H_
#define GRAPHMATRIX_H_

#include <vector>
#include "graph.h"

template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te> {
private:
    std::vector<Vertex<Tv>> v_set;
    std::vector<std::vector<Edge<Te> *>> e_set;
public:
    GraphMatrix(): Graph<Tv, Te>() {}
    ~GraphMatrix();

    /* vertex operation */
    int insert(const Tv &v_elem);
    Tv remove(int i);
    Tv &vertex(int i) { return v_set[i].data; }
    int &indegree(int i) { return v_set[i].indegree; }
    int &outdegree(int i) { return v_set[i].outdegree; }
    VStatus &v_status(int i) { return v_set[i].status; }
    int &d_time(int i) { return v_set[i].d_time; }
    int &f_time(int i) { return v_set[i].f_time; }
    int &parent(int i) { return v_set[i].parent; }
    int &priority(int i) { return v_set[i].priority; }
    int first_nbr(int i) { return next_nbr(i, this->n); }
    int next_nbr(int i, int j);

    /* edge operation */
    void insert(const Te &e_elem, int w, int i, int j);
    Te remove(int i, int j);
    Te &edge(int i, int j) { return e_set[i][j]->data; }
    int weight(int i, int j) { return e_set[i][j]->weight; }
    bool exists(int i, int j) { return (0 <= i && i < this->n) && (0 <= j && j < this->n) && e_set[i][j] != nullptr; }
    EStatus &e_status(int i, int j) { return e_set[i][j]-> status; }
};

template <typename Tv, typename Te>
GraphMatrix<Tv, Te>::~GraphMatrix()
{
    for( int i = 0; i < this->n; i++ )
        for( int j = 0; j < this->n; j++ )
            delete e_set[i][j];
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::insert(const Tv &v_elem)
{
    for( int i = 0; i < this->n; i++ )
        e_set[i].push_back(nullptr);
    this->n++;
    e_set.push_back(std::vector<Edge<Te> *>(this->n, nullptr));
    v_set.push_back(Vertex<Tv>(v_elem));

    return this->n - 1;
}

template <typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int i)
{
    Tv ret = v_set[i].data;

    for( int j = 0; j < this->n; j++ ) {
        if( exists(i, j) ) {
            delete e_set[i][j];
            v_set[j].indegree--;
        }
    }
    e_set.erase(e_set.begin() + i);
    this->n--;
    for( int k = 0; k < this->n; k++ ) {
        if( exists(k, i) ) {
            delete e_set[k][i];
            v_set[k].outdegree--;
        }
        e_set[k].erase(e_set[k].begin() + i);
    }

    v_set.erase(v_set.begin() + i);

    return ret;
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::next_nbr(int i, int j)
{
    while( -1 < j && !exists(i, --j) );
    return j;
}

template <typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(const Te &e_elem, int w, int i, int j)
{
    if( exists(i, j) )
        return;

    e_set[i][j] = new Edge<Te>(e_elem, w);
    this->e++;
    v_set[i].outdegree++;
    v_set[j].indegree++;
}

template <typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j)
{
    Te ret = e_set[i][j]->data;

    delete e_set[i][j];
    e_set[i][j] = nullptr;
    this->e--;
    v_set[i].outdegree--;
    v_set[j].indegree--;

    return ret;
}

#endif /* GRAPHMATRIX_H_ */
