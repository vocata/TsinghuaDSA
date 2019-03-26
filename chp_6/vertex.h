#ifndef VERTEX_H_
#define VERTEX_H_

#include <climits>

enum VStatus { UNDISCOVERED, DISCOVERED, VISITED };

template <typename Tv>
struct Vertex {
    Tv data;
    int indegree, outdegree;
    VStatus status;
    int d_time, f_time;
    int parent;
    int priority;

    Vertex(const Tv &elem)
        : data(elem), indegree(0), outdegree(0), status(UNDISCOVERED), d_time(-1), f_time(-1), parent(-1), priority(INT_MAX) {}
};

#endif /* VERTEX_H_ */
