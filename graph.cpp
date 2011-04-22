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


Graph::Graph(int _vertexCount, int _colorCount) : 
        m_vertexCount(_vertexCount),
        m_colorCount(_colorCount),
        m_coloringMatrixSize(m_vertexCount*(m_vertexCount - 1)/2) {

    ASSERT(m_colorCount >= 2 && m_colorCount <= 0xff);
    ASSERT(m_vertexCount <= 50);

    this->coloringMatrix = (Color*) malloc(m_coloringMatrixSize);

    memset(this->coloringMatrix, 0, m_coloringMatrixSize);
}

Graph::Graph(const Graph& src) :
        m_vertexCount(src.m_vertexCount),
        m_colorCount(src.m_colorCount),
        m_coloringMatrixSize(m_vertexCount*(m_vertexCount - 1)/2) {

    this->coloringMatrix = (Color*) malloc(m_coloringMatrixSize);

    memcpy(this->coloringMatrix, src.coloringMatrix, m_coloringMatrixSize);

}


int Graph::vertexCount() const {
    return m_vertexCount;
}


int Graph::edgeCount() const {
    return m_coloringMatrixSize;
}


int Graph::colorCount() const {
    return m_colorCount;
}


Color Graph::edgeColor(int v1, int v2) const {

    //could possibly leave that out and make it an assertion
    if (v1 < v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    // note: index calculation has optimization potential (hash v2 -> - ((v2+1)*(v2+2)/2)
    int index = v2*m_vertexCount + v1 - ((v2+1)*(v2+2)/2);
    return coloringMatrix[index];

}


void Graph::setEdgeColor(int v1, int v2, Color color) {

    ASSERT(color < m_colorCount);

    //could possibly leave that out and make it an assertion
    if (v1 < v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    // note: index calculation has optimization potential (hash v2 -> - ((v2+1)*(v2+2)/2)
    int index = v2*m_vertexCount + v1 - ((v2+1)*(v2+2)/2);
    coloringMatrix[index] = color;

}

void Graph::setEdgeColor(int index, Color color) {
    coloringMatrix[index] = color;
}

int Graph::vertexDegree(int v1, Color color) const {

    int sum = 0;

    for (int v2 = 0; v2 < m_vertexCount; v2 += 1) {
        if (v2 != v1 && edgeColor(v1, v2) == color) {
            sum += 1;
        }
    }

    return sum;
}


set<int> Graph::completeSubgraph(int k, Color color) const {

    ASSERT(color < m_colorCount);

    set<int> ret;

    // TODO

    return set<int>({1});
}


std::string Graph::coloringMatrixToString() const {

    ostringstream o;

    int vertexWidth = (2 + (log10(m_vertexCount-1) > log10(m_colorCount-1) ?
            log10(m_vertexCount-1) : log10(m_colorCount-1)));


    // header
    for (int i = 0; i < vertexWidth; i += 1) { o << " "; }

    for (int v = 0; v < m_vertexCount; v += 1) {
        o.width(vertexWidth);
        o << v;
    }

    o << endl;


    //body
    for (int v1 = 0; v1 < m_vertexCount; v1 += 1) {

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

    int vertexWidth = 2 + log10(m_vertexCount-1);
    int colorWidth = 2 + log10(m_colorCount-1);

    for (int v1 = 0; v1 < m_vertexCount; v1 += 1) {

        o.width(vertexWidth);
        o << v1 << ": vertizes: [";

        for (int v2 = 0; v2 < m_vertexCount; v2 += 1) {
            if (v1 == v2) { continue; }
            o << "\e[0;3" << (int(edgeColor(v1,v2)) + 1) << "m";
            o.width(vertexWidth);
            o << v2;
            o << "\e[0;30m";
            o << ", ";
        }

        o << "], ";

        o << " degree by color: {";
        for (Color c = 0; c < m_colorCount; c += 1) {
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

    for (int v = 0; v < m_vertexCount; v += 1) {
        o << v << " [shape=circle]" << endl;
    }

    for (int v1 = 0; v1 < m_vertexCount; v1 += 1) {
        for (int v2 = v1+1; v2 < m_vertexCount; v2 += 1) {
            o << v1 << " -- " << v2 << " [color=\"/set19/" << int(edgeColor(v1,v2))+1 << "\"];" << endl;
        }
    }

    o << "}";

    return o.str();
}

