#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <cstdint>
#include <set>
#include <string>



typedef uint8_t Color;


class Graph {

public:

    Graph(int _vertexCount, int _colorCount);
    Graph(const Graph&);

    int vertexCount() const;
    int edgeCount() const;
    int colorCount() const;

    // v1 vert,v2 horiz
    Color edgeColor(int v1, int v2) const;
    void setEdgeColor(int v1, int v2, Color color);
    // dirty
    void setEdgeColor(int index, Color color);

    int vertexDegree(int v, Color color) const;

    // returns vertizes of thesub graph
    std::set<int> completeSubgraph(int k, Color color) const;


    // debug helper
    std::string coloringMatrixToString() const;

    // debug helper
    std::string vertexListToString() const;

    // debug helper
    // produces a very irregular looking graph
    // TODO investigate how to resolve that
    std::string toDot() const;

private:

    int m_vertexCount;
    int m_colorCount;
    int m_edgeCount;

    Color *coloringMatrix;

};

#endif /* GRAPH_HPP */

