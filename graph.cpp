#include "graph.hpp"

#include "debug.hpp"

#include <cmath>
#include <cstring>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::ostringstream;
using std::string;


Graph::Graph() {
    memset(this->coloringMatrix, 0, coloringMatrixSize);
}


Graph::Graph(const Graph&) {
}


Color Graph::edgeColor(int w, int v) const {

    //could possibly leave that out and make it an assertion
    if (w < v) {
        int tmp = w;
        w = v;
        v = tmp;
    }

    // note: index calculation has optimization potential (hash w -> - (w*(w+1)/2)
    int index = v*vertexCount + w - ((v+1)*(v+2)/2);
    return coloringMatrix[index];

}


void Graph::setEdgeColor(int w, int v, Color c) {

    ASSERT(c < colorCount);

    //could possibly leave that out and make it an assertion
    if (w < v) {
        int tmp = w;
        w = v;
        v = tmp;
    }

    // note: index calculation has optimization potential (hash w -> - (w*(w+1)/2)
    int index = v*vertexCount + w - ((v+1)*(v+2)/2);
    coloringMatrix[index] = c;

}


int Graph::vertexDegree(int v, Color color) const {
    return 0;
}


std::string Graph::coloringMatrixToString() const {

    ostringstream o;

    int vertexWidth = (2 + (log10(vertexCount-1) > log10(colorCount-1) ?
            log10(vertexCount-1) : log10(colorCount-1)));


    // header
    for (int i = 0; i < vertexWidth; i += 1) {
        o << " ";
    }

    for (int v = 0; v < vertexCount; v += 1) {
        o.width(vertexWidth);
        o << v;
    }

    o << endl;


    //body
    for (int w = 0; w < vertexCount; w += 1) {

        o.width(vertexWidth);
        o << w ;


        for (int v = 0; v < w; v += 1) {
            // bash coloring
            o << "\e[0;3" << (int(edgeColor(v,w)) + 1) << "m";
            o.width(vertexWidth);
            o << int(edgeColor(v,w));
            o << "\e[0;30m";
        }

        o << endl;
    }

    return o.str();
}
