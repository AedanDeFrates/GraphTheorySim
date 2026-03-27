#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

struct Coord3
{
    public:
    float x, y, z;
    bool operator==(const Coord3& other) const;
};

class Vertex
{
    public:
    Coord3 pos;
    float radius;

    Vertex();
    Vertex(Coord3 p, float r);
    bool equals(Vertex* v) const;
    std::string toString() const;
    void clampPos();
};
class Edge
{
    public:
    Vertex* head;
    Vertex* tail;

    Edge(Vertex* h, Vertex* t);
    bool isLoop() const;
    std::string toString() const;
    float getDistance() const;
};
class Graph
{
    public:
    std::vector<Vertex*> vertexSet;
    std::vector<Edge*> edgeSet;

    Graph();
    bool addVertex(Vertex* v);
    bool addEdge(Edge* e);
    bool isSimple() const;
    std::vector<glm::vec3> getEdgeHeadVectors()const;
    std::vector<glm::vec3> getEdgeTailVectors() const;

    std::vector<float> mkLineVectors() const;
    std::vector<glm::vec3> getTrianglePositions() const;

};

Graph test_graph();

#endif