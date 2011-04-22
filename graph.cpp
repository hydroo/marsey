#include "graph.hpp"

#include "debug.hpp"

#include <cmath>
#include <cstring>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::ostringstream;
using std::set;
using std::string;


Graph::Graph() {
    memset(this->coloringMatrix, 0, coloringMatrixSize);
}


Graph::Graph(const Graph&) {
}


Color Graph::edgeColor(int v1, int v2) const {

    //could possibly leave that out and make it an assertion
    if (v1 < v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    // note: index calculation has optimization potential (hash v2 -> - ((v2+1)*(v2+2)/2)
    int index = v2*vertexCount + v1 - ((v2+1)*(v2+2)/2);
    return coloringMatrix[index];

}


void Graph::setEdgeColor(int v1, int v2, Color color) {

    ASSERT(color < colorCount);

    //could possibly leave that out and make it an assertion
    if (v1 < v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    // note: index calculation has optimization potential (hash v2 -> - ((v2+1)*(v2+2)/2)
    int index = v2*vertexCount + v1 - ((v2+1)*(v2+2)/2);
    coloringMatrix[index] = color;

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


set<int> Graph::completeSubGraph(int k, Color color) const {

    ASSERT(color < colorCount);

    set<int> ret;

    for (int v = 0; v < vertexCount; v += 1) {
        if (vertexDegree(v, color) >= k-1) {
            ret.insert(v);

            if (int(ret.size()) == k) {
                return ret;
            }
        }
    }

    return set<int>();
}


std::string Graph::coloringMatrixToString() const {

    ostringstream o;

    int vertexWidth = (2 + (log10(vertexCount-1) > log10(colorCount-1) ?
            log10(vertexCount-1) : log10(colorCount-1)));


    // header
    for (int i = 0; i < vertexWidth; i += 1) { o << " "; }

    for (int v = 0; v < vertexCount; v += 1) {
        o.width(vertexWidth);
        o << v;
    }

    o << endl;


    //body
    for (int v1 = 0; v1 < vertexCount; v1 += 1) {

        o.width(vertexWidth);
        o << v1 ;


        for (int v2 = 0; v2 < v1; v2 += 1) {
            // bash coloring
            o << "\e[0;3" << (int(edgeColor(v1,v2)) + 1) << "m";
            o.width(vertexWidth);
            o << int(edgeColor(v1,v2));
            o << "\e[0;30m";
        }

        o << endl;
    }

    return o.str();
}


std::string Graph::vertexListToString() const {

    ostringstream o;

    int vertexWidth = 2 + log10(vertexCount-1);
    int colorWidth = 2 + log10(colorCount-1);

    for (int v1 = 0; v1 < vertexCount; v1 += 1) {

        o.width(vertexWidth);
        o << v1 << ": vertizes: [";

        for (int v2 = 0; v2 < vertexCount; v2 += 1) {
            if (v1 == v2) { continue; }
            o << "\e[0;3" << (int(edgeColor(v1,v2)) + 1) << "m";
            o.width(vertexWidth);
            o << v2;
            o << "\e[0;30m";
            o << ", ";
        }

        o << "], ";

        o << " degree by color: {";
        for (Color c = 0; c < colorCount; c += 1) {
            o << "\e[0;3" << int(c)+1 << "m";
            o.width(vertexWidth);
            o << int(c) << ":";
            o.width(colorWidth);
            o << vertexDegree(v1,c);
            o << "\e[0;30m";
            o << ", ";
        }
        o << "}" << endl;
    }

    return o.str();
}


std::string Graph::toDot() const {
    ostringstream o;

    o << "graph G {";

    for (int v = 0; v < vertexCount; v += 1) {
        o << v << " [shape=circle]" << endl;
    }

    for (int v1 = 0; v1 < vertexCount; v1 += 1) {
        for (int v2 = v1+1; v2 < vertexCount; v2 += 1) {
            o << v1 << " -- " << v2 << " [color=\"/set19/" << int(edgeColor(v1,v2))+1 << "\"];" << endl;
        }
    }

    o << "}";

    return o.str();
}

