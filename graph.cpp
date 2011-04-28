#include "graph.hpp"

#include "debug.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
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
        m_edgeCount(m_vertexCount*(m_vertexCount - 1)/2),
        m_coloringMatrix(0) {

    check();

    this->m_coloringMatrix = (Color*) malloc(m_edgeCount);
    memset(this->m_coloringMatrix, 0, m_edgeCount);
}

Graph::Graph(const Graph& src) :
        m_vertexCount(src.m_vertexCount),
        m_colorCount(src.m_colorCount),
        m_edgeCount(m_vertexCount*(m_vertexCount - 1)/2),
        m_coloringMatrix(0) {

    this->m_coloringMatrix = (Color*) malloc(m_edgeCount);
    memcpy(this->m_coloringMatrix, src.m_coloringMatrix, m_edgeCount);
}


int Graph::vertexCount() const {
    return m_vertexCount;
}


int Graph::edgeCount() const {
    return m_edgeCount;
}


int Graph::colorCount() const {
    return m_colorCount;
}


Color Graph::edgeColor(int v1, int v2) const {

    ASSERT(v1 != v2);
    ASSERT(v1 >= 0 && v1 < m_vertexCount);
    ASSERT(v2 >= 0 && v2 < m_vertexCount);

    int index = edgeIndexFromVertexIndizes(v1,v2);

    return m_coloringMatrix[index];
}


void Graph::setEdgeColor(int v1, int v2, Color color) {

    ASSERT(v1 >= 0 && v1 < m_vertexCount);
    ASSERT(v2 >= 0 && v2 < m_vertexCount);
    ASSERT(color >= 0 && color < m_colorCount);

    int index = edgeIndexFromVertexIndizes(v1,v2);

    m_coloringMatrix[index] = color;
}

void Graph::setEdgeColor(int edgeIndex, Color color) {

    ASSERT(edgeIndex >= 0 && edgeIndex < m_edgeCount);
    ASSERT(color >= 0 && color < m_colorCount);

    m_coloringMatrix[edgeIndex] = color;
}

int Graph::vertexDegree(int v1, Color color) const {

    ASSERT(v1 >= 0 && v1 < m_vertexCount);
    ASSERT(color >= 0 && color < m_colorCount);

    int sum = 0;

    for (int v2 = 0; v2 < m_vertexCount; v2 += 1) {
        if (v2 != v1 && edgeColor(v1, v2) == color) {
            sum += 1;
        }
    }

    return sum;
}

bool Graph::isCompleteSubgraph(const std::set<int>& vertizes, Color color) const {

    ASSERT(int(vertizes.size()) <= vertexCount());
    ASSERT(color >= 0 && color < m_colorCount);

    for (auto v = vertizes.begin(); v != vertizes.end(); ++v) {

        for (auto w = ++vertizes.find(*v); w != vertizes.end(); ++w) {

            if (edgeColor(*v, *w) != color) {
                return false;
            }
        }
    }

    return true;
}



set<int> Graph::completeSubgraph(int k, Color color) const {

    ASSERT(k >= 1 && k <= m_vertexCount);
    ASSERT(color >= 0 && color < m_colorCount);

    set<int> possibleVertizes;

    for (int v = 0; v < vertexCount(); v += 1) {
        if (vertexDegree(v, color) >= k-1) {
            possibleVertizes.insert(v);
        }
    }

    if (int(possibleVertizes.size()) < k) {
        return set<int>();
    }


    auto i = possibleVertizes.begin();
    set<int> current;
    current.insert(*i);

    const set<int>& ret1 = completeSubgraphRecursive(*i, current, possibleVertizes, k, color);
    if (ret1.empty() == false) { return ret1; }
    const set<int>& ret2 = completeSubgraphRecursive(*i, set<int>(), possibleVertizes, k, color);
    if (ret2.empty() == false) { return ret2; }


    return set<int>();
}


// returns a complete subgraph as a set of vertizes or set<int>()
//
// note: TODO computes all 0 to k sized vertex sets, before
// discarding all 0 to k-1 sized sets with the first if.
// Perhaps discarding the creation of these sets earlier pays of
set<int> Graph::completeSubgraphRecursive(int lastVertex, const set<int>& current,
        const set<int>& possibleVertizes, int k, Color color) const {

    if (int(current.size()) == k) {
        if (isCompleteSubgraph(current, color) == true) {
            return current;
        } else {
            return set<int>();
        }
    }


    auto nextVertex = ++possibleVertizes.find(lastVertex);
    if (nextVertex == possibleVertizes.end()) {
        return set<int>();
    }

    set<int> currentCopy = current;
    currentCopy.insert(*nextVertex);

    const set<int>& ret1 = completeSubgraphRecursive(*nextVertex, currentCopy, possibleVertizes, k, color);
    if (ret1.empty() == false) { return ret1; }
    const set<int>& ret2 = completeSubgraphRecursive(*nextVertex, current, possibleVertizes, k, color);
    if (ret2.empty() == false) { return ret2; }

    return set<int>();
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


int Graph::edgeIndexFromVertexIndizes(int v1, int v2) const {

    // currently duplicate, but I leave the assertions in
    // in case I forget to add them in later code
    ASSERT(v1 != v2);
    ASSERT(v1 >= 0 && v1 < m_vertexCount);
    ASSERT(v2 >= 0 && v2 < m_vertexCount);

    if (v1 < v2) { std::swap(v1,v2); }

    // note: index calculation has optimization potential (hash v2 -> - ((v2+1)*(v2+2)/2)
    return v2*m_vertexCount + v1 - ((v2+1)*(v2+2)/2);
}


void Graph::check() const {

    ASSERT(m_vertexCount >= 0);
    ASSERT(m_colorCount >= 2 && m_colorCount <= std::numeric_limits<Color>::max());
    ASSERT(m_edgeCount == m_vertexCount*(m_vertexCount - 1)/2);

    if (m_coloringMatrix != 0) {
        for (int i = 0; i < m_edgeCount; i += 1) {
            ASSERT(m_coloringMatrix[i] >= 0 && m_coloringMatrix[i] < m_colorCount);
        }
    }
}

