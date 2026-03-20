#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

struct Coord3 
{
    float x; float y; float z;
    
    bool operator==(Coord3& other) const 
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

class Vertex
{
    public:
    Coord3 pos;
    float radius;
    
    Vertex() : pos{0,0,0}, radius(0.0) {}
    Vertex(Coord3 p, float r)
    {
        pos = p;
        radius = r;
    }
    
    bool equals(Vertex* v)
    {
        if(this->pos == v->pos) {return false;}
        else {return true;}
    }

    std::string toString()
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
    
    Edge(Vertex* h, Vertex* t)
    {
        this->head = h;
        this->tail = t;
    }
    bool isLoop()
    {
        return head == tail;
    }
    
    std::string toString()
    {
        std::string h;
        std::string t;
        
        h = "Head " + head->toString() + "\n";
        t = "Tail " + tail->toString();
        
        return h + t;
    }
    
    public:
    float getDistance()
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
    std::vector<Vertex*>    vectSet;
    std::vector<Edge*>      edgeSet;
    
    Graph()
    {
        this->vectSet = {};
        this->edgeSet = {};
    }
    
    bool addVector(Vertex* v)
    {
        if(vectSet.empty()) {vectSet.push_back(v); return true;} //If there are no vectors in the graph: TRUE
        
        for(Vertex* vCurr : vectSet)
        {
            if(v == vCurr) {return false;} //If the object the same: FALSE
            if(v->equals(vCurr)) {return false;} //If the positions of the vector are the same: FALSE
        }
        
        vectSet.push_back(v);
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
    
    bool isSimple()
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
};

int test_graph()
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

    Coord3 coord1{1,2,3};
    Coord3 coord2{2,4,6};
    Coord3 coord3{3,5,7};
    Coord3 coord4{1,1,1};
    Coord3 coord5{2,3,6};

    Vertex v1(coord1, 1.0f); Vertex* v1P = &v1;
    Vertex v2(coord2, 1.0f); Vertex* v2P = &v2;
    Vertex v3(coord3, 1.0f); Vertex* v3P = &v3;
    Vertex v4(coord4, 1.0f); Vertex* v4P = &v4;
    Vertex v5(coord5, 1.0f); Vertex* v5P = &v5;

    Edge e1(v1P, v2P); Edge* e1P = &e1;
    Edge e2(v1P, v1P); Edge* e2P = &e2;
    Edge e3(v2P, v3P); Edge* e3P = &e3;
    Edge e4(v3P, v4P); Edge* e4P = &e4;
    Edge e5(v3P, v5P); Edge* e5P = &e5;
    Edge e6(v2P, v5P); Edge* e6P = &e6;

    Graph g;

    g.addVector(v1P);
    g.addVector(v2P);
    g.addVector(v3P);
    g.addVector(v4P);
    g.addVector(v5P);

    g.addEdge(e1P);
    g.addEdge(e2P);
    g.addEdge(e3P);
    g.addEdge(e4P);
    g.addEdge(e5P);
    g.addEdge(e6P);

    return 0;
}