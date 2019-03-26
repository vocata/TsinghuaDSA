#include <iostream>
#include "graphmatrix.h"

using namespace std;

int main()
{
    GraphMatrix<int, int> graph;
    graph.insert(666);
    graph.insert(1, 1, 0, 0);
    graph.dfs(0);

    return 0;
}
