#include "graph.hpp"

#include "debug.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


int main(int argc, char** argv) {

    Graph graph;

    graph.setEdgeColor(1,0,1);
    graph.setEdgeColor(1,2,1);
    graph.setEdgeColor(0,2,1);
    //graph.setEdgeColor(4,3,1);
    //graph.setEdgeColor(5,0,2);
    //graph.setEdgeColor(5,4,1);

    cout << "coloring matrix:" << endl;
    cout << graph.coloringMatrixToString() << endl;

    cout << "vertex list:" << endl;
    cout << graph.vertexListToString() << endl;

    std::set<int> kn = graph.completeSubGraph(3,1);

    for (auto i = kn.begin(); i != kn.end(); ++i) {
        cout << *i << ", ";
    }
    cout << endl;

    std::ofstream dotFile("test.dot");
    dotFile << graph.toDot();
    dotFile.close();

    return 0;
}

