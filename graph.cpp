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

    // note: index calculation has optimization potential (hash v -> - ((v+1)*(v+2)/2)
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

    // note: index calculation has optimization potential (hash v -> - ((v+1)*(v+2)/2)
    int index = v*vertexCount + w - ((v+1)*(v+2)/2);
    coloringMatrix[index] = c;

}


int Graph::vertexDegree(int v1, Color color) const {

    int sum = 0;

    for (int v2 = 0; v2 < vertexCount; v2 += 1) {
        if (v2 != v1 && edgeColor(v1, v2) == color) {
            sum += 1;
        }
    }

    return sum;
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


std::string Graph::vertexListToString() const {

    ostringstream o;

    int vertexWidth = (2 + (log10(vertexCount-1) > log10(colorCount-1) ?
            log10(vertexCount-1) : log10(colorCount-1)));

    for (int v1 = 0; v1 < vertexCount; v1 += 1) {

        o.width(vertexWidth);
        o << v1 << ": [";

        for (int v2 = 0; v2 < vertexCount; v2 += 1) {
            if (v1 == v2) { continue; }
            o << "\e[0;3" << (int(edgeColor(v1,v2)) + 1) << "m";
            o.width(vertexWidth);
            o << v2;
            o << "\e[0;30m";
            o << ", ";
        }

        o << "] ";

        o << "{";
        for (Color c = 0; c < colorCount; c += 1) {
            o << "\e[0;3" << int(c)+1 << "m";
            o.width(vertexWidth);
            o << int(c) << ":" << vertexDegree(v1,c);
            o << "\e[0;30m";
            o << ", ";
        }
        o << "}" << endl;
    }

    return o.str();
}

