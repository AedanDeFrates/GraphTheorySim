#include "graph.hpp"

Graph graph_test()
{
    Coord3 coord1{-0.9,0,0};
    Coord3 coord2{-0.5,0,0};
    Coord3 coord3{-0.1,0,0};
    Coord3 coord4{.3, 0 ,0};
    Coord3 coord5{-0.4,-0.5,0};

    Vertex* v1 = new Vertex(coord1, 1.0f);
    Vertex* v2 = new Vertex(coord2, 1.0f);
    Vertex* v3 = new Vertex(coord3, 1.0f);
    Vertex* v4 = new Vertex(coord4, 1.0f);
    Vertex* v5 = new Vertex(coord5, 1.0f);

    Edge* e1 = new Edge(v1, v2);
    Edge* e2 = new Edge(v1, v1);
    Edge* e3 = new Edge(v2, v3);
    Edge* e4 = new Edge(v3, v4);
    Edge* e5 = new Edge(v3, v5);
    Edge* e6 = new Edge(v2, v5);

    Graph g;

    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addVertex(v4);
    g.addVertex(v5);

    g.addEdge(e1);
    g.addEdge(e2);
    g.addEdge(e3);
    g.addEdge(e4);
    g.addEdge(e5);
    g.addEdge(e6);

    return g; 
}