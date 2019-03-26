#ifndef GRAPH_H_
#define GRAPH_H_

#include "edge.h"
#include "vertex.h"
#include <iostream>
#include <queue>

template <typename Tv, typename Te>
class Graph {
private:
    void reset();
    /* as fundamental frame for other more complex algorithms */
    void BFS(int, int&);
    void DFS(int, int&);

protected:
    int n, e;

public:
    Graph()
        : n(0)
        , e(0)
    {
    }
    virtual ~Graph() = default;

    virtual int insert(const Tv&) = 0;
    virtual Tv remove(int) = 0;
    virtual Tv& vertex(int) = 0;
    virtual int& indegree(int) = 0;
    virtual int& outdegree(int) = 0;
    virtual VStatus& v_status(int) = 0;
    virtual int& d_time(int) = 0;
    virtual int& f_time(int) = 0;
    virtual int& parent(int) = 0;
    virtual int& priority(int) = 0;
    virtual int first_nbr(int) = 0;
    virtual int next_nbr(int, int) = 0;

    virtual void insert(const Te&, int, int, int) = 0;
    virtual Te remove(int, int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int weight(int, int) = 0;
    virtual bool exists(int, int) = 0;
    virtual EStatus& e_status(int, int) = 0;

    int vertex_size() { return n; }
    int edge_size() { return e; }
    void bfs(int);
    void dfs(int);
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::reset()
{
    for (int i = 0; i < n; i++) {
        v_status(i) = UNDISCOVERED;
        d_time(i) = f_time(i) = -1;
        parent(i) = -1;
        priority(i) = INT_MAX;
        for (int j = 0; j < n; j++)
            if (exists(i, j))
                e_status(i, j) = UNDETERMINED;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) // O(n^2 + e)
{
    std::queue<int> que;
    v_status(v) = DISCOVERED;
    que.push(v);
    while (!que.empty()) { // O(n)
        v = que.front();
        que.pop();
        d_time(v) = ++clock;

        /* VISIT */
        /* TODO */
        std::cout << vertex(v) << std::endl;

        for (int u = first_nbr(v); u > -1; u = next_nbr(v, u)) { // next_nbr is O(n) and the most loop count is e
            if (v_status(u) == UNDISCOVERED) {
                v_status(u) = DISCOVERED;
                que.push(u);
                e_status(v, u) = TREE;
                parent(u) = v;
            } else {
                e_status(v, u) = CROSS;
            }
        }
        v_status(v) = VISITED; // prevent slef-cycle
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock)
{
    v_status(v) = DISCOVERED;
    d_time(v) = ++clock;

    /* VISIT */
    /* TODO */
    std::cout << vertex(v) << std::endl;

    for (int u = first_nbr(v); u > -1; u = next_nbr(v, u)) {
        switch (v_status(u)) {
        case UNDISCOVERED:
            e_status(v, u) = TREE;
            parent(u) = v;
            DFS(u, clock);
            break;
        case DISCOVERED:
            e_status(v, u) = BACKWARD;
            break;
        default:
            e_status(v, u) = d_time(v) < d_time(u) ? FORWARD : CROSS;
            break;
        }
    }
    v_status(v) = VISITED;
    f_time(v) = ++clock;
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int v)
{
    reset();
    int u = v;
    int clock = 0;
    do {
        if (v_status(u) == UNDISCOVERED)
            BFS(u, clock);
    } while (v != (u = (u + 1) % n));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int v)
{
    reset();
    int u = v;
    int clock = 0;
    do {
        if (v_status(u) == UNDISCOVERED)
            DFS(u, clock);
    } while (v != (u = (u + 1) % n));
}

#endif /* GRAPH_H_ */
