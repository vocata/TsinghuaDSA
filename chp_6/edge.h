#ifndef EDGE_H_
#define EDGE_H_

enum EStatus { UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD };

template <typename Te>
struct Edge {
    Te data;
    int weight;
    EStatus status;
    Edge(const Te& elem, int w)
        : data(elem)
        , weight(w)
        , status(UNDETERMINED)
    {
    }
};

#endif /* EDGE_H_ */
