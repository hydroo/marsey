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

    for (int vertexCount = 1; ; vertexCount += 1) {

        bool hasCompleteSubGraph;

        Graph graph(vertexCount, colorCount);

        uint64_t count = 0;

        hasCompleteSubGraph = coloringsRecursive(graph, 0, p, &count);

        if (hasCompleteSubGraph == true) {
            return vertexCount;
        }
    }
}


// generates 2^(n(n-1)/2) colorings including variants which are equivalent
// (isomorphism, inverse coloring, ?more?) for the problem
// 2^((n-1)(n-2)/2) would be correct I think (*)
// given (*) is correct, this means that we are doing 2^(n-1) times the work
// that is necessary (incredibly much)
//
// n := vertexCount
//
bool coloringsRecursive(const Graph& graph, int currentEdge, const std::vector<int>& p, uint64_t *count) {

    if (currentEdge == graph.edgeCount()) {

        *count += 1;

        for (int i = 0; i < int(p.size()); i += 1) {

            if (graph.vertexCount() < p[i]) {
                continue;
            }

            auto completeSubgraph = graph.completeSubgraph(p[i],i);
            if (completeSubgraph.empty() == false) {


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
                //fileNameStream << "-true.dot";

                //std::ofstream dotFile(fileNameStream.str());
                //dotFile << graph.toDot();
                //dotFile.close();

                return true;
            }
        }

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
        //fileNameStream << "-false.dot";

        //std::ofstream dotFile(fileNameStream.str());
        //dotFile << graph.toDot();
        //dotFile.close();

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
        //{3,5},

        {4,1},
        {4,2},
        {4,3},
        //{4,4},

        {5,1},
        {5,2}
        //{5,3}
        };

    for (auto p = parameters.begin(); p != parameters.end(); ++p) {
        cout << "R(";
        for (auto q = p->begin(); q != p->end(); ++q) {
            cout << *q << ",";
        }
        cout << ") = ";
        cout << findR(*p) << endl;
    }

    return 0;
}

