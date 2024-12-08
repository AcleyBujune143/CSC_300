#include "graph.h"

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;
    adjMatrix = new int*[maxVertices];
    for (int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i] = new int[maxVertices];
        for (int j = 0; j < maxVertices; j++)
        {
            adjMatrix[i][j] = 0; 
        }
    }
    visited = new bool[maxVertices]{false}; 
}

Graph::~Graph()
{
    delete[] visited;

    for (int i = 0; i < maxVertices; i++) {
        delete[] adjMatrix[i];  // Free each row
    }
    delete[] adjMatrix;  // Free the array of row pointers

    vertex* tempVertex;
    while (vertices)
    {
        edge* tempEdge;
        while (vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;  // Delete each edge
        }

        // Now delete the vertex itself
        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex; 
    }
}

void Graph::addVertex(char data)
{
    if (numVertices >= maxVertices)
    {
        cout << "Maximum number of vertices reached!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices;
    newVertex->aHead = nullptr;
    newVertex->visited = 0; 
    vertices = newVertex;
    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // Find the source and destination vertices
    while (srcVertex && srcVertex->data != src)
        srcVertex = srcVertex->vNext;
    while (destVertex && destVertex->data != dest)
        destVertex = destVertex->vNext;

    if (!srcVertex || !destVertex)
    {
        cout << "Vertices not found!" << endl;
        return;
    }

    // Add edge to adjacency list
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Since undirected, add the reverse edge as well
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Add edge to adjacency matrix 
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}

void Graph::removeVertex(char data)
{
    // Find the vertex to remove
    vertex* temp = vertices;
    vertex* prev = nullptr;
    while (temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }

    if (!temp)
    {
        cout << "Vertex not found!" << endl;
        return;
    }

    // Remove the vertex from adjacency list of all other vertices
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;
        while (e)
        {
            if (e->dest->data == data)
            {
                if (prevEdge)
                    prevEdge->eNext = e->eNext;
                else
                    v->aHead = e->eNext;
                delete e;
                break;
            }
            prevEdge = e;
            e = e->eNext;
        }
    }

    // Remove vertex from the list
    if (prev)
        prev->vNext = temp->vNext;
    else
        vertices = temp->vNext;

    delete temp;


    // Remove from the adjacency matrix
    int index = temp->data - 'A';
    for (int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;

}

void Graph::removeEdge(char src, char dest)
{
   // Complete this
    // Find the source and destination vertices
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    while (srcVertex && srcVertex->data != src)
        srcVertex = srcVertex->vNext;
    while (destVertex && destVertex->data != dest)
        destVertex = destVertex->vNext;

    if (!srcVertex || !destVertex)
    {
        cout << "Vertices not found!" << endl;
        return;
    }

    // Remove edge from adjacency list of source vertex
    edge* current = srcVertex->aHead;
    edge* prev = nullptr;
    while (current)
    {
        if (current->dest->data == dest)
        {
            if (prev)
                prev->eNext = current->eNext;
            else
                srcVertex->aHead = current->eNext;
            delete current;
            break;
        }
        prev = current;
        current = current->eNext;
    }

    // Remove edge from adjacency list of destination vertex
    current = destVertex->aHead;
    prev = nullptr;
    while (current)
    {
        if (current->dest->data == src)
        {
            if (prev)
                prev->eNext = current->eNext;
            else
                destVertex->aHead = current->eNext;
            delete current;
            break;
        }
        prev = current;
        current = current->eNext;
    }

    // Remove edge from adjacency matrix
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    adjMatrix[srcIndex][destIndex] = 0;
    adjMatrix[destIndex][srcIndex] = 0;
}

void Graph::displayAdjList()
{
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";
        for (edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " ( " << e->weight << ") -> ";
        }
        cout << "null" << endl;
    }
}

void Graph::displayAdjMatrix()
{
    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = 0; j < maxVertices; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


void Graph::bfsL(char start)
{
    // Reset visited status
    for (int i = 0; i < maxVertices; i++) visited[i] = false;

    // Find the start vertex
    vertex* startVertex = vertices;
    while (startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;
    
    if (!startVertex)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initialize queue for BFS traversal
    node* queue = nullptr;
    enqueue(queue, start);  // Enqueue the starting vertex
    visited[startVertex->data - 'A'] = true;

    cout << "BFS using Adjacency List: ";
    while (queue)
    {
        // Dequeue the front vertex
        char currentData = queue->data;
        dequeue(queue);
        cout << currentData << " ";

        // Find the vertex corresponding to the dequeued data
        vertex* currentVertex = vertices;
        while (currentVertex && currentVertex->data != currentData)
            currentVertex = currentVertex->vNext;

        // Traverse adjacent vertices
        for (edge* e = currentVertex->aHead; e != nullptr; e = e->eNext)
        {
            if (!visited[e->dest->data - 'A'])
            {
                enqueue(queue, e->dest->data);
                visited[e->dest->data - 'A'] = true;
            }
        }
    }
    cout << endl;
}

void Graph::bfsM(char start)
{
    // Reset visited status for all vertices
    for (int i = 0; i < maxVertices; i++) {
        visited[i] = false;
    }

    // Find the start vertex index
    int startIndex = start - 'A'; 

    if (startIndex < 0 || startIndex >= maxVertices) {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initialize queue for BFS traversal
    node* queue = nullptr;
    enqueue(queue, start); 
    visited[startIndex] = true;

    cout << "BFS using Adjacency Matrix: ";
    while (queue) {
        // Dequeue the front vertex
        char currentData = queue->data;
        dequeue(queue);
        cout << currentData << " ";

        int currentIndex = currentData - 'A'; 

        // Explore all adjacent vertices using the adjacency matrix
        for (int i = 0; i < maxVertices; i++) {
            // If there is an edge (adjMatrix[currentIndex][i] == 1)
            // and the vertex is not visited
            if (adjMatrix[currentIndex][i] && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i + 'A');  // Enqueue the unvisited adjacent vertex (convert index to char)
            }
        }
    }
    cout << endl;
}

void Graph::dfsL(char start)
{
    // Complete this
    // Reset visited status
    for (int i = 0; i < maxVertices; i++) visited[i] = false;

    // Find the start vertex
    vertex* startVertex = vertices;
    while (startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;
    
    if (!startVertex)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initialize stack for DFS traversal
    node* stack = nullptr;
    push(stack, start);

    cout << "DFS using Adjacency List: ";
    while (stack)
    {
        // Pop the top vertex
        char currentData = stack->data;
        pop(stack);

        // If not visited, process the vertex
        int currentIndex = currentData - 'A';
        if (!visited[currentIndex])
        {
            cout << currentData << " ";
            visited[currentIndex] = true;

            // Find the vertex corresponding to the current data
            vertex* currentVertex = vertices;
            while (currentVertex && currentVertex->data != currentData)
                currentVertex = currentVertex->vNext;

            // Push adjacent unvisited vertices to stack
            for (edge* e = currentVertex->aHead; e != nullptr; e = e->eNext)
            {
                if (!visited[e->dest->data - 'A'])
                {
                    push(stack, e->dest->data);
                }
            }
        }
    }
    cout << endl;
}

void Graph::dfsM(char start)
{
    // Complete this
    // Reset visited status
    for (int i = 0; i < maxVertices; i++) {
        visited[i] = false;
    }

    // Find the start vertex index
    int startIndex = start - 'A'; 

    if (startIndex < 0 || startIndex >= maxVertices) {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initialize stack for DFS traversal
    node* stack = nullptr;
    push(stack, start); 

    cout << "DFS using Adjacency Matrix: ";
    while (stack) {
        // Pop the top vertex
        char currentData = stack->data;
        pop(stack);

        // If not visited, process the vertex
        int currentIndex = currentData - 'A';
        if (!visited[currentIndex]) 
        {
            cout << currentData << " ";
            visited[currentIndex] = true;

            // Explore adjacent vertices using adjacency matrix
            for (int i = maxVertices - 1; i >= 0; i--) {
                // If there is an edge and the vertex is not visited
                if (adjMatrix[currentIndex][i] && !visited[i]) {
                    push(stack, i + 'A');  // Push unvisited adjacent vertex
                }
            }
        }
    }
    cout << endl;
}

bool Graph::dfsCycleHelper(vertex* currentVertex, int parent)
{
    // Mark the current vertex as visited
    int currentIndex = currentVertex->data - 'A';
    visited[currentIndex] = true;

    // Traverse all adjacent vertices
    for (edge* e = currentVertex->aHead; e != nullptr; e = e->eNext)
    {
        vertex* adjacentVertex = e->dest;
        int adjacentIndex = adjacentVertex->data - 'A';

        // If adjacent vertex is not visited, recursively check for cycle
        if (!visited[adjacentIndex])
        {
            // Pass the current vertex's index as the parent
            if (dfsCycleHelper(adjacentVertex, currentIndex))
                return true;
        }
        // If adjacent vertex is visited and is not the parent vertex, 
        // then there is a cycle
        else if (adjacentIndex != parent)
        {
            return true;
        }
    }

    return false;
}

bool Graph::detectCycleDFS()
{
    // Reset visited status for all vertices
    for (int i = 0; i < maxVertices; i++) 
    {
        visited[i] = false;
    }

    // Traverse all vertices
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        int currentIndex = v->data - 'A';
        
        // If vertex is not visited, start DFS from this vertex
        // Pass -1 as initial parent since this is the first vertex
        if (!visited[currentIndex])
        {
            // If a cycle is detected in this component, return true
            if (dfsCycleHelper(v, -1))
                return true;
        }
    }

    // No cycle found
    return false;
}

int Graph::findSet(int vertex, int parent[])
{
    if (parent[vertex] != vertex)
        parent[vertex] = findSet(parent[vertex], parent);  // Path compression

    return parent[vertex]; 
}

void Graph:: unionSet(int u, int v, int parent[], int rank[])
{
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);

    if (rootU != rootV)
    {
        if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else 
        {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}


void Graph::kruskal()
{
    if(!vertices)
    {
        cout << "Graph is empty" << endl;
        return;
    }
    
    // allocating space for edges 
    EdgeInfo edges[maxVertices * maxVertices];
    int edgeCount = 0;
    
    // Extracting edges from adjacency list manually
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        for (edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            // Avoid duplicate edges
            if (v->data <= e->dest->data)
            {
                edges[edgeCount].src = v->data;
                edges[edgeCount].dest = e->dest->data;
                edges[edgeCount].weight = e->weight;
                edgeCount++;
            }
        }
    }

    // bubble sort for edges
    for (int i = 0; i < edgeCount - 1; i++)
    {
        for (int j = 0; j < edgeCount - i - 1; j++)
        {
            if (edges[j].weight > edges[j+1].weight)
            {
                // Swap edges
                EdgeInfo temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }

    // Union-Find data structures
    int parent[maxVertices];
    int rank[maxVertices];

    // Initializing disjoint sets
    for (int i = 0; i < maxVertices; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    // Statically allocate MST edges
    EdgeInfo mst[maxVertices];
    int mstCount = 0;
    int totalCost = 0;

    // Processing the sorted edges
    for (int i = 0; i < edgeCount; i++)
    {
        int u = edges[i].src - 'A';
        int v = edges[i].dest - 'A';

        int rootU = findSet(u, parent);
        int rootV = findSet(v, parent);

        // If adding this edge doesn't create a cycle
        if (rootU != rootV)
        {
            mst[mstCount] = edges[i];
            mstCount++;
            totalCost += edges[i].weight;
            unionSet(u, v, parent, rank);
        }
    }

    // Printing MST
    cout << "Kruskal's Minimum Spanning Tree:" << endl;
    for (int i = 0; i < mstCount; i++)
    {
        cout << mst[i].src << " - " << mst[i].dest << " : " << mst[i].weight << endl;
    }
    cout << "Total Cost: " << totalCost << endl;
}


void Graph::dijkstra(char start)
{
    // Finding the start vertex
    vertex* startVertex = vertices;
    while (startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;
    
    if (!startVertex)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initializing distances and visited array
    int dist[maxVertices];
    bool visited[maxVertices];
    
    for (int i = 0; i < maxVertices; i++)
    {
        dist[i] = INT_MAX;  
        visited[i] = false;
    }

    // Distance to start vertex is 0
    int startIndex = start - 'A';
    dist[startIndex] = 0;

    // Finding shortest paths
    for (int count = 0; count < numVertices - 1; count++)
    {
        // Finding the minimum distance vertex among unvisited vertices
        int minDist = INT_MAX;
        int minVertex = -1;
        
        for (int v = 0; v < maxVertices; v++)
        {
            if (!visited[v] && dist[v] < minDist)
            {
                minDist = dist[v];
                minVertex = v;
            }
        }

        if (minVertex == -1) break;

        // Marking the selected vertex as visited
        visited[minVertex] = true;

        // Updating distances of adjacent vertices
        for (int v = 0; v < maxVertices; v++)
        {
            // If there's an edge and vertex is not visited
            // and the path through current vertex is shorter
            if (!visited[v] && 
                adjMatrix[minVertex][v] != 0 && 
                dist[minVertex] != INT_MAX && 
                dist[minVertex] + adjMatrix[minVertex][v] < dist[v])
            {
                dist[v] = dist[minVertex] + adjMatrix[minVertex][v];
            }
        }
    }

    // Printing shortest distances
    cout << "Dijkstra's Shortest Paths from vertex " << start << ":" << endl;
    for (int i = 0; i < maxVertices; i++)
    {
        if (dist[i] != INT_MAX)
            cout << "To " << char(i + 'A') << ": " << dist[i] << endl;
    }
}



void Graph::prim(char start)
{
    // Finding the start vertex index
    int startIndex = start - 'A'; 

    if (startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    int key[maxVertices];        // Minimum edge weight to include vertex in MST
    bool included[maxVertices];  // Whether the vertex is included in MST
    int parent[maxVertices];     // To store the resulting MST

    // Initializing arrays
    for (int i = 0; i < maxVertices; i++)
    {
        key[i] = INT_MAX;
        included[i] = false;
        parent[i] = -1;
    }

    // Starting with the first vertex
    key[startIndex] = 0;  
    parent[startIndex] = -1;

    for (int count = 0; count < numVertices - 1; count++)
    {
        // Finding the vertex with the minimum key value that is not yet included
        int minKey = INT_MAX;
        int u = -1;

        for (int v = 0; v < maxVertices; v++)
        {
            if (!included[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break; // No more vertices to process

        // Including the chosen vertex in MST
        included[u] = true;

        // Updating key and parent for adjacent vertices of u
        for (int v = 0; v < maxVertices; v++)
        {
            if (adjMatrix[u][v] && !included[v] && adjMatrix[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }

    // Printing the MST
    cout << "Prim's Minimum Spanning Tree:" << endl;
    int totalCost = 0;
    for (int i = 0; i < maxVertices; i++)
    {
        if (parent[i] != -1)
        {
            cout << char(parent[i] + 'A') << " - " << char(i + 'A') 
                 << " : " << adjMatrix[parent[i]][i] << endl;
            totalCost += adjMatrix[parent[i]][i];
        }
    }
    cout << "Total Cost: " << totalCost << endl;
}
