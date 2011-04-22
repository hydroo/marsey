#include "graph.hpp"

#include "debug.hpp"

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;


bool coloringsRecursive(const Graph& graph, int currentEdge, const std::vector<int>& p, uint64_t *count);


int findR(const std::vector<int>& p) {

    int colorCount = p.size();

    for (int vertexCount = 0; ; vertexCount += 1) {
        bool hasCompleteSubGraph;

        Graph graph(vertexCount, colorCount);

        uint64_t count = 0;

        hasCompleteSubGraph = coloringsRecursive(graph, 0, p, &count);

        if (hasCompleteSubGraph == true) {
            return vertexCount;
        }
    }
}


bool coloringsRecursive(const Graph& graph, int currentEdge, const std::vector<int>& p, uint64_t *count) {

    if (currentEdge == graph.edgeCount()) {

        *count += 1;

        for (int i = 0; i < int(p.size()); i += 1) {
            auto completeSubgraph = graph.completeSubgraph(p[i],i);
            if (completeSubgraph != std::set<int>()) {


                //std::ostringstream fileNameStream;

                //fileNameStream << "R-";
                //for (auto q = p.begin(); q != p.end(); ++q) {
                //    fileNameStream << *q << "-";
                //}
                //fileNameStream << "/";

                //fileNameStream << graph.vertexCount() << ":";
                //fileNameStream.width(5);
                //fileNameStream.fill('0');
                //fileNameStream << *count;
                //fileNameStream << ".dot";

                //std::ofstream dotFile(fileNameStream.str());
                //dotFile << graph.toDot();
                //dotFile.close();

                return true;
            }
        }

        return false;
    }

    bool ret = true;

    for (Color c = 0; c < graph.colorCount(); c += 1) {
        Graph fork(graph);
        fork.setEdgeColor(currentEdge, c);
        ret &= coloringsRecursive(fork, currentEdge + 1, p, count);
    }

    return ret;
}


int main(int argc, char** argv) {

    std::set<std::vector<int>> parameters{
        {1,1},
        {1,2},
        {1,3},
        {1,4},
        {1,5},

        {2,1},
        {2,2},
        {2,3},
        {2,4},
        {2,5},

        {3,1},
        {3,2},
        {3,3},
        {3,4},
        {3,5},

        {4,1},
        {4,2},
        {4,3},
        {4,4},

        {5,1},
        {5,2},
        {5,3}
        };

    for (auto p = parameters.begin(); p != parameters.end(); ++p) {
        cout << "R(";
        for (auto q = p->begin(); q != p->end(); ++q) {
            cout << *q << ",";
        }
        cout << ") = ";
        cout << findR(*p) << endl;
    }


    //Graph graph;

    //graph.setEdgeColor(1,0,1);
    //graph.setEdgeColor(1,2,1);
    //graph.setEdgeColor(0,2,1);
    ////graph.setEdgeColor(4,3,1);
    ////graph.setEdgeColor(5,0,2);
    ////graph.setEdgeColor(5,4,1);

    //cout << "coloring matrix:" << endl;
    //cout << graph.coloringMatrixToString() << endl;

    //cout << "vertex list:" << endl;
    //cout << graph.vertexListToString() << endl;

    //std::set<int> kn = graph.completeSubgraph(3,1);

    //for (auto i = kn.begin(); i != kn.end(); ++i) {
    //    cout << *i << ", ";
    //}
    //cout << endl;

    //std::ofstream dotFile("test.dot");
    //dotFile << graph.toDot();
    //dotFile.close();

    return 0;
}

