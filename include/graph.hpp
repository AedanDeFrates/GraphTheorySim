#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>

struct Coord3
{
    public:
    float x, y, z;

    bool operator==(const Coord3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

class Vertex
{
    public:
    Coord3 pos;
    float radius;

    Vertex() : pos{0,0,0}, radius(0.0f) {}
    Vertex(Coord3 p, float r)
    {
        pos = p;
        radius = r;
    }

    bool equals(Vertex* v) const
    {
        if(this->pos == v->pos) { return true; }
        return false;
    }
    std::string toString() const
    {
        std::stringstream ss;
        ss << "Vertex: POSITION = ("<< pos.x <<", "<< pos.y <<", " << pos.z <<") & RADIUS = " << radius << "";
        return ss.str();
    }
};

class Edge
{
    public:
    Vertex* head;
    Vertex* tail;

    float distance;

    Edge(Vertex* h, Vertex* t)
    {
        head = h;
        tail = t;
        
        distance = getDistance();
    }

    std::string toString() const
    {
        std::string h;
        std::string t;
        
        h = "Head " + head->toString() + "\n";
        t = "Tail " + tail->toString();
        
        return h + t;
    }

    private:
    float getDistance() const
    {
        float distance = std::sqrt(
            (head->pos.x - tail->pos.x)*(head->pos.x - tail->pos.x) + 
            (head->pos.y - tail->pos.y)*(head->pos.y - tail->pos.y) + 
            (head->pos.z - tail->pos.z)*(head->pos.z - tail->pos.z)
        );
        return distance;
    }
};

class Graph
{
    public:
    std::vector<Vertex*> vertexSet;
    std::vector<Edge*> edgeSet;

    Graph() : vertexSet(), edgeSet() {}

    bool addVertex(Vertex* v)
    {
        if(vertexSet.empty()) {vertexSet.push_back(v); return true;} //If there are no vectors in the graph: TRUE
        
        for(Vertex* vCurr : vertexSet)
        {
            if(v == vCurr) {return false;} //If the object the same: FALSE
            if(v->equals(vCurr)) {return false;} //If the positions of the vector are the same: FALSE
        }
        
        vertexSet.push_back(v);
        return true;
    }

    bool addEdge(Edge* e)
    {
        if(edgeSet.empty()) { edgeSet.push_back(e); return true;}
        
        for(Edge* eCurr : edgeSet)
        {
            if(e == eCurr) { return false; }
            if(e->head == eCurr->head && e->tail == eCurr->tail) { return false; }
        }
         
        edgeSet.push_back(e);
        return true;
    }
    
    std::vector<float> getLineVectors() const
    {
        std::vector<float> vertices;
        for(int i = 0; i < edgeSet.size(); i++)
        {
            vertices.push_back(edgeSet.at(i)->head->pos.x);
            vertices.push_back(edgeSet.at(i)->head->pos.y);
            vertices.push_back(edgeSet.at(i)->head->pos.z);
            vertices.push_back(edgeSet.at(i)->tail->pos.x);
            vertices.push_back(edgeSet.at(i)->tail->pos.y);
            vertices.push_back(edgeSet.at(i)->tail->pos.z);
        }

        return vertices;
    }
    std::vector<glm::vec3> getTrianglePositions() const
    {
        std::vector<glm::vec3> vertexPositions;
        for(int i = 0; i < vertexSet.size(); i++)
        {
            vertexPositions.push_back(glm::vec3(vertexSet.at(i)->pos.x, vertexSet.at(i)->pos.y, vertexSet.at(i)->pos.z));
        }
        return vertexPositions;
    }
};

Graph graph_test();

#endif