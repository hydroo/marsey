#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <cstdint>
#include <string>


#define COLORCOUNT 3
#define VERTEXCOUNT 6

static_assert(COLORCOUNT >= 2 && COLORCOUNT <= 0xff, "COLORCOUNT >= 2 && COLORCOUNT <= 0xff");
static_assert(VERTEXCOUNT <= 50, "VERTEXCOUNT <= 50");

typedef uint8_t Color;


class Graph {

public:

    Graph();
    Graph(const Graph&);

    // v1 vert,v2 horiz
    Color edgeColor(int v1, int v2) const;
    void setEdgeColor(int v1, int v2, Color c);

    int vertexDegree(int v, Color color) const;

    // debug helper
    std::string coloringMatrixToString() const;

    // debug helper
    std::string vertexListToString() const;

    // debug helper
    // produces a very irregular looking graph
    // TODO investigate how to resolve that
    std::string toDot() const;


private:

    static const int vertexCount = VERTEXCOUNT;
    static const int colorCount = COLORCOUNT;
    static const int coloringMatrixSize = vertexCount*(vertexCount - 1)/2;

    Color coloringMatrix[coloringMatrixSize];

};

#endif /* GRAPH_HPP */

