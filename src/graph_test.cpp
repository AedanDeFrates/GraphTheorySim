#include "graph.hpp"

Graph graph_test()
{
// ---- Vertices ----
Coord3 coords[40] = {
    {-0.83,  0.72, 0}, { 0.64, -0.55, 0}, {-0.12,  0.33, 0}, { 0.91,  0.10, 0},
    {-0.45, -0.88, 0}, { 0.22,  0.67, 0}, {-0.71, -0.14, 0}, { 0.38, -0.22, 0},
    {-0.19,  0.91, 0}, { 0.57,  0.48, 0}, {-0.94,  0.05, 0}, { 0.13, -0.77, 0},
    {-0.36,  0.18, 0}, { 0.79, -0.31, 0}, {-0.52,  0.59, 0}, { 0.05,  0.02, 0},
    {-0.67, -0.63, 0}, { 0.44,  0.83, 0}, {-0.08, -0.41, 0}, { 0.95, -0.74, 0},

    {-0.28,  0.49, 0}, { 0.72,  0.21, 0}, {-0.61, -0.02, 0}, { 0.18, -0.58, 0},
    {-0.77,  0.36, 0}, { 0.33,  0.04, 0}, {-0.14, -0.92, 0}, { 0.88,  0.66, 0},
    {-0.49, -0.27, 0}, { 0.60, -0.09, 0}, {-0.02,  0.76, 0}, { 0.27, -0.44, 0},
    {-0.85,  0.28, 0}, { 0.49,  0.55, 0}, {-0.31, -0.70, 0}, { 0.11,  0.39, 0},
    {-0.58,  0.84, 0}, { 0.76, -0.48, 0}, {-0.23, -0.18, 0}, { 0.03, -0.03, 0}
};

Vertex* v[40];
for(int i = 0; i < 40; i++) {
    v[i] = new Vertex(coords[i], 1.0f);
}

// ---- Graph ----
Graph g;

// Add vertices
for(int i = 0; i < 40; i++) {
    g.addVertex(v[i]);
}

// ---- Edges ----
Edge* edges[] = {
    // Horizontal connections (grid)
    new Edge(v[0], v[1]), new Edge(v[1], v[2]), new Edge(v[2], v[3]), new Edge(v[3], v[4]),
    new Edge(v[5], v[6]), new Edge(v[6], v[7]), new Edge(v[7], v[8]), new Edge(v[8], v[9]),
    new Edge(v[10], v[11]), new Edge(v[11], v[12]), new Edge(v[12], v[13]), new Edge(v[13], v[14]),
    new Edge(v[15], v[16]), new Edge(v[16], v[17]), new Edge(v[17], v[18]), new Edge(v[18], v[19]),
    new Edge(v[20], v[21]), new Edge(v[21], v[22]), new Edge(v[22], v[23]), new Edge(v[23], v[24]),

    // Vertical connections
    new Edge(v[0], v[5]), new Edge(v[5], v[10]), new Edge(v[10], v[15]), new Edge(v[15], v[20]),
    new Edge(v[1], v[6]), new Edge(v[6], v[11]), new Edge(v[11], v[16]), new Edge(v[16], v[21]),
    new Edge(v[2], v[7]), new Edge(v[7], v[12]), new Edge(v[12], v[17]), new Edge(v[17], v[22]),
    new Edge(v[3], v[8]), new Edge(v[8], v[13]), new Edge(v[13], v[18]), new Edge(v[18], v[23]),
    new Edge(v[4], v[9]), new Edge(v[9], v[14]), new Edge(v[14], v[19]), new Edge(v[19], v[24]),

    // Extra diagonal / interesting connections
    new Edge(v[0], v[6]), new Edge(v[6], v[12]), new Edge(v[12], v[18]),
    new Edge(v[2], v[8]), new Edge(v[8], v[14]),
    new Edge(v[20], v[16]), new Edge(v[16], v[12]),
    new Edge(v[25], v[26]), new Edge(v[26], v[27]), new Edge(v[27], v[28]), new Edge(v[28], v[29]),
    new Edge(v[30], v[31]), new Edge(v[31], v[32]), new Edge(v[32], v[33]), new Edge(v[33], v[34]),

    // Center connections
    new Edge(v[35], v[12]), new Edge(v[36], v[12]),
    new Edge(v[37], v[11]), new Edge(v[38], v[13]),
    new Edge(v[39], v[22])
};

// Add edges
int edgeCount = sizeof(edges) / sizeof(edges[0]);
for(int i = 0; i < edgeCount; i++) {
    g.addEdge(edges[i]);
}

return g;
}