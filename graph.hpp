#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <cstdint>
#include <set>
#include <string>



typedef int8_t Color;


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
    // dirty (because it reveals implementation detail, and no matching other functions exist)
    void setEdgeColor(int edgeIndex, Color color);

    int vertexDegree(int v, Color color) const;


    bool isCompleteSubgraph(const std::set<int>& vertizes, Color color) const;
private:
    std::set<int> completeSubgraphRecursive(int lastVertex, const std::set<int>& current,
            const std::set<int>& possibleVertizes, int k, Color color) const;
public:

    // returns vertizes of the sub graph
    std::set<int> completeSubgraph(int k, Color color) const;


    // debug helper
    std::string coloringMatrixToString() const;

    // debug helper
    std::string vertexListToString() const;

    // debug helper
    // produces a very irregular looking graph
    // TODO investigate how to resolve that
    std::string toDot() const;

    // debug helper
    // checks the consistency of all data stored in this instance/class
    void check() const;

private:

    int edgeIndexFromVertexIndizes(int v1, int v2) const;

private:

    int m_vertexCount;
    int m_colorCount;
    int m_edgeCount;

    Color *m_coloringMatrix;

};

#endif /* GRAPH_HPP */

