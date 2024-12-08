#include "graph.h"
 
int main()
{
    Graph g(10); 
    
    // Adding vertices
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addVertex('F');  
    g.addVertex('G');
    g.addVertex('H');
    g.addVertex('I');
    g.addVertex('J');

    // Adding edges
    g.addEdge('A', 'B', 1);
    g.addEdge('A', 'C', 2);
    g.addEdge('B', 'D', 3);
    g.addEdge('C', 'E', 4);
    g.addEdge('C', 'D', 5);
    g.addEdge('E', 'D', 6);
    g.addEdge('A', 'H', 7);
    g.addEdge('B', 'G', 8);
    g.addEdge('F', 'I', 9);
    g.addEdge('F', 'J', 10);
    g.addEdge('I', 'J', 11);
    g.addEdge('C', 'F', 12); 
    g.addEdge('D', 'F', 13);
    g.addEdge('C', 'H', 14);

    // Removing a vertex and some edges
    g.removeVertex('F');
    g.removeEdge('C', 'H');
    g.removeEdge('D', 'E');

    // Display adjacency list and matrix
    g.displayAdjList();
    g.displayAdjMatrix();
    
    cout << endl;

    // Perform BFS and DFS starting from vertex 'A'
    g.bfsL('A');
    g.bfsM('A');
    g.dfsL('A');
    g.dfsM('A');  

    cout << endl;

    //detecting circle in the graph
    cout << "Cycle Detection Test:" << endl;
    if (g.detectCycleDFS())
        cout << "Cycle Detected!" << endl;
    else
        cout << "No Cycle Detected!" << endl;


    
    cout << "\nKruskal's Algorithm Test:" << endl;
    g.kruskal();
    
    cout << "\nDijkstra's Algorithm Test:" << endl;
    g.dijkstra('A');

    cout << "\nPrim's Algorithm Test:" << endl;
    g.prim('A');

    return 0;
    
}
