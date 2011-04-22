#include "graph.hpp"

#include "debug.hpp"

#include <iostream>

using std::cout;
using std::endl;


int main(int argc, char** argv) {

    Graph graph;

    graph.setEdgeColor(1,0,1);
    graph.setEdgeColor(2,1,1);
    graph.setEdgeColor(3,2,1);
    graph.setEdgeColor(4,3,1);
    graph.setEdgeColor(5,0,2);
    graph.setEdgeColor(5,4,1);

    cout << "adjacency matrix:" << endl;
    cout << graph.coloringMatrixToString() << endl;
    cout << "vertex list:" << endl;
    cout << graph.vertexListToString() << endl;

    return 0;
}

