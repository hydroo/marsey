#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <cstdint>
#include <string>


#define COLORCOUNT 2
#define VERTEXCOUNT 6

static_assert(COLORCOUNT >= 2 && COLORCOUNT <= 0xff, "COLORCOUNT >= 2 && COLORCOUNT <= 0xff");
static_assert(VERTEXCOUNT <= 50, "VERTEXCOUNT <= 50");

typedef uint8_t Color;


class Graph {

public:

    Graph();
    Graph(const Graph&);

    // w vert,v horiz
    Color edgeColor(int w, int v) const;
    void setEdgeColor(int w, int v, Color c);
    int vertexDegree(int v, Color color) const;

    std::string coloringMatrixToString() const;

private:

    static const int vertexCount = VERTEXCOUNT;
    static const int colorCount = COLORCOUNT;
    static const int coloringMatrixSize = vertexCount*(vertexCount - 1)/2;

    Color coloringMatrix[coloringMatrixSize];

};

#endif /* GRAPH_HPP */

