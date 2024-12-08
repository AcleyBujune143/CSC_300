#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <climits>
#include "sqll.h"  // Include your stack/queue implementation using linked list

using namespace std;

struct edge
{
    struct vertex* dest;  
    edge* eNext;
    int weight;
};

struct vertex
{
    char data;
    vertex* vNext;
    edge* aHead; 

    // for traversal
    short visited; 
};

struct EdgeInfo
{
    char src;
    char dest;
    int weight;
};

class Graph
{
    private:
        vertex* vertices;  
        int** adjMatrix;   
        bool* visited;     
        int maxVertices;   
        int numVertices;   

    public:
        Graph(int maxV);
        ~Graph();         

        // Add/Remove Vertices and Edges
        void addVertex(char data);
        void addEdge(char src, char dest, int weight);
        void removeVertex(char data);
        void removeEdge(char src, char dest);  // Complete this

        // Display methods
        void displayAdjList();
        void displayAdjMatrix();

        // Traversal/Search Algorithms
        void bfsL(char start);
        void bfsM(char start); 
        void dfsL(char start);   // Complete this
        void dfsM(char start);   // Complete this

        // Detect cycle with DFS - Extra Credit
        bool dfsCycleHelper(vertex* currentVertex, int parent);
        bool detectCycleDFS();

        //MST
        int findSet(int vertex, int parent[]);
        void unionSet(int u, int v, int parent[], int rank[]);
        void kruskal();

        void dijkstra(char start);
        void prim(char start);

};
#endif
