#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

struct Coord3
{
    bool operator==(Coord3& other) const;
};

class Vector
{
    Vector();
    Vector(Coord3 p, float r);

    bool equals(Vector* v);
    std::string toString();

};
class Edge
{
    Edge(Vector* h, Vector* t);
    bool isLoop();
    std::string toString();
    float getDistance();
};
class Graph
{
    public:

    Graph();
    bool addVector(Vector* v);
    bool addEdge(Edge* e);
    bool isSimple();
};

#endif