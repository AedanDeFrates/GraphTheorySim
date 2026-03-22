#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "graph.hpp"


bool Coord3::operator==(const Coord3& other) const 
{
    return x == other.x && y == other.y && z == other.z;
}

//=====================================================
//                  VERTEX CLASS IMPL
//=====================================================

//Construxtors
    Vertex::Vertex() : pos{0,0,0}, radius(0.0) {}
    Vertex::Vertex(Coord3 p, float r)
    {
        pos = p;
        radius = r;
    }
    
    bool Vertex::equals(Vertex* v) const
    {
        if(this->pos == v->pos) {return true;}
        else {return false;}
    }

    std::string Vertex::toString() const
    {
        std::stringstream ss;
        ss << "Vertex: POSITION = ("<< pos.x <<", "<< pos.y <<", " << pos.z <<") & RADIUS = " << radius << "";
        return ss.str();
    }

    void Vertex::clampPos()
    {
        pos.x = std::clamp(pos.x, -1.0f, 1.0f);
        pos.y = std::clamp(pos.y, -1.0f, 1.0f);
        pos.z = std::clamp(pos.z, -1.0f, 1.0f);
    }

//=============================================================
//                      EDGE CLASS IMPL
//=============================================================

    Edge::Edge(Vertex* h, Vertex* t)
    {
        this->head = h;
        this->tail = t;
    }
    bool Edge::isLoop() const
    {
        return head == tail;
    }
    
    std::string Edge::toString() const
    {
        std::string h;
        std::string t;
        
        h = "Head " + head->toString() + "\n";
        t = "Tail " + tail->toString();
        
        return h + t;
    }
    
    float Edge::getDistance() const
    {
       float distance = std::sqrt(
            (head->pos.x - tail->pos.x)*(head->pos.x - tail->pos.x) + 
            (head->pos.y - tail->pos.y)*(head->pos.y - tail->pos.y) + 
            (head->pos.z - tail->pos.z)*(head->pos.z - tail->pos.z)
       );
       return distance;
    }

//=============================================================
//                      GRAPH CLASS IMPL
//=============================================================
Graph::Graph()
{
    this->vertexSet = {};
    this->edgeSet = {};
}
    
bool Graph::addVertex(Vertex* v)
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
    
bool Graph::addEdge(Edge* e)
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
    
bool Graph::isSimple() const
{
    for(int i = 0; i < edgeSet.size(); i++)
    {
        if(edgeSet.at(i)->isLoop()){ return false; }
    }
    for (int i = 0; i < edgeSet.size() -1; i++)
        {
            for(int j = i+1; j < edgeSet.size() - 2; j++)
            {
                if(edgeSet.at(i)->head == edgeSet.at(j)->head && edgeSet.at(i)->tail == edgeSet.at(j)->tail)
                { return false; }
                if(edgeSet.at(i)->head->equals(edgeSet.at(j)->head) && edgeSet.at(i)->tail->equals(edgeSet.at(j)->tail))
                { return false; }
            }
        }
        return true;
    }
    //funct to return float[] of vertex shape vectors.
    std::vector<float> Graph::mkLineVectors() const
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
    //funct to return float[] of edge line vectors.
    std::vector<float> Graph::mkTriangleVectors() const
    {
        std::vector<float> vertices;
        for(int i = 0; i < vertexSet.size(); i++)
        {
            vertices.push_back(vertexSet.at(i)->pos.x);
            vertices.push_back(vertexSet.at(i)->pos.y+0.02);
            vertices.push_back(vertexSet.at(i)->pos.z);

            vertices.push_back(vertexSet.at(i)->pos.x-0.02);
            vertices.push_back(vertexSet.at(i)->pos.y-0.02);
            vertices.push_back(vertexSet.at(i)->pos.z);

            vertices.push_back(vertexSet.at(i)->pos.x+0.02);
            vertices.push_back(vertexSet.at(i)->pos.y-0.02);
            vertices.push_back(vertexSet.at(i)->pos.z);
        }
        return vertices;
    }


//=============================================================
//                   TEST GRAPH FUNCTION
//=============================================================
Graph test_graph()
{
    std::cout << "==========Test==========\n";
    std::cout << "==========Print Coord3==========\n";
    Coord3 c1;
    c1.x = 1.0f; 
    c1.y = 1.0f; 
    c1.z = 1.0f;
    
    std::cout << "Coord3 c1: (" <<c1.x<< ", " <<c1.y<< ", " <<c1.z<< ")\n";
    
    std::cout << "==========Print Vertex==========\n";
    
    
    
    Vertex v(c1, 4);
    std::cout << v.toString() + "\n";
    
    std::cout << "==========Print Edge==========\n";
    
    Vertex vHead(c1, 3);
    Vertex vTail(c1, 4);
    
    Vertex* vHeadP = &vHead;
    Vertex* vTailP = &vTail;
    
    Edge ball(vHeadP, vTailP);
    
    std::cout << ball.toString() + "\n";
    std::cout << "Distance = " << ball.getDistance() << "\n";
    
    std::cout << "==========Test Edge Functs==========\n";
    if(ball.isLoop()) { std::cout << "Edge 1 is a loop\n"; }
    else {std::cout << "Edge 1 is not a loop\n" ;}
    
    std::cout << "==========Print Graph==========\n";

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