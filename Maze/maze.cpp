#include "maze.h"

Cell::Cell(int _x, int _y) 
{
    x = _x;
    y = _y;
    visited = false;
    walls[0] = walls[1] = walls[2] = walls[3] = true;
}

Maze::Maze(int r, int c)
{
    rows = r;
    cols = c;
    playerPosition = {0, 0};
    grid = new Cell**[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new Cell*[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = new Cell(i, j);
        }
    }

    // Start the timer when maze is created
    startTimer();
}

Maze::~Maze() 
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}

void Maze::displayMaze() 
{
    for (int i = 0; i < rows; ++i) {
        // Print top walls
        for (int j = 0; j < cols; ++j) {
            cout << (grid[i][j]->walls[0] ? "+---" : "+   ");
        }
        cout << "+" << endl;
        // Print left walls and cells
        for (int j = 0; j < cols; ++j) {
            if (playerPosition.first == i && playerPosition.second == j) {
                cout << (grid[i][j]->walls[3] ? "| P " : "  P ");
            } else {
                cout << (grid[i][j]->walls[3] ? "|   " : "    ");
            }
        }
        cout << "|" << endl;
    }
    // Print bottom line
    for (int j = 0; j < cols; ++j) {
        cout << "+---";
    }
    cout << "+" << endl;
}

void Maze::generateMaze() 
{
    // Reset all cells to unvisited
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j]->visited = false;
        }
    }

    // Implementing randomized DFS for maze generation using stack
    stack<Cell*> cellStack;
    Cell* startCell = grid[0][0];
    startCell->visited = true;
    cellStack.push(startCell);

    while (!cellStack.empty()) {
        Cell* current = cellStack.top();
        Cell* neighbors[4];
        int neighborCount = getUnvisitedNeighbors(current, neighbors);

        if (neighborCount > 0) {
            // Randomly select an unvisited neighbor
            int randomIndex = rand() % neighborCount;
            Cell* next = neighbors[randomIndex];
            
            // Remove walls between current and next cell
            removeWalls(*current, *next);
            
            // Mark the next cell as visited and push to stack
            next->visited = true;
            cellStack.push(next);
        } else {
            // No unvisited neighbors, backtrack
            cellStack.pop();
        }
    }

    // Ensure start and end are accessible
    grid[0][0]->walls[3] = false;  // Remove left wall of start
    grid[rows-1][cols-1]->walls[1] = false;  // Remove right wall of end
}

void Maze::play() 
{
    char input;
    while (true) {
        system("cls"); // Clear screen for Windows
        
        // Display timer
        displayTimer();

        // Display maze
        displayMaze();

        // Display controls
        cout << "Use WASD to move, U to undo, H for hint, P for shortest path, Q to quit." << endl;

        // Handle user input
        input = _getch();
        
        if (input == 'q' || input == 'Q') {
            break;
        }
        else if (input == 'u' || input == 'U') {
            undoMove();
            continue;
        }
        else if (input == 'h' || input == 'H') {
            provideHint();
            _getch(); // Wait for a key press
            continue;
        }
        else if (input == 'p' || input == 'P') {
            findAndDisplayShortestPath();
            _getch(); // Wait for a key press
            continue;
        }

        // Move player
        int prevX = playerPosition.first;
        int prevY = playerPosition.second;

        // Move logic with wall constraints
        if (input == 'w' || input == 'W') {
            if (playerPosition.first > 0 && !grid[playerPosition.first][playerPosition.second]->walls[0]) {
                playerPosition.first--;
            }
        }
        else if (input == 'a' || input == 'A') {
            if (playerPosition.second > 0 && !grid[playerPosition.first][playerPosition.second]->walls[3]) {
                playerPosition.second--;
            }
        }
        else if (input == 's' || input == 'S') {
            if (playerPosition.first < rows - 1 && !grid[playerPosition.first][playerPosition.second]->walls[2]) {
                playerPosition.first++;
            }
        }
        else if (input == 'd' || input == 'D') {
            if (playerPosition.second < cols - 1 && !grid[playerPosition.first][playerPosition.second]->walls[1]) {
                playerPosition.second++;
            }
        }

        // Store move in history for undo
        PlayerMove move = {{prevX, prevY}, input};
        moveHistory.push(move);

        // Check if player reached the end
        if (playerPosition.first == rows - 1 && playerPosition.second == cols - 1) {
            system("cls");
            
            displayMaze();
            cout << "Congratulations! You've reached the end of the maze!" << endl;
            break;
        }
    }
}

int Maze::getUnvisitedNeighbors(Cell* cell, Cell* neighbors[]) 
{
    int x = cell->x;
    int y = cell->y;
    int count = 0;

    // Check all four neighbors
    if (x > 0 && !grid[x - 1][y]->visited) neighbors[count++] = grid[x - 1][y];
    if (y > 0 && !grid[x][y - 1]->visited) neighbors[count++] = grid[x][y - 1];
    if (x < rows - 1 && !grid[x + 1][y]->visited) neighbors[count++] = grid[x + 1][y];
    if (y < cols - 1 && !grid[x][y + 1]->visited) neighbors[count++] = grid[x][y + 1];

    return count;
}

void Maze::removeWalls(Cell& current, Cell& next) 
{
    // Determine the direction between current and next cells
    if (current.x == next.x) {
        // Horizontal movement
        if (current.y > next.y) {
            // Moving left
            current.walls[3] = false;
            next.walls[1] = false;
        } else {
            // Moving right
            current.walls[1] = false;
            next.walls[3] = false;
        }
    } else {
        // Vertical movement
        if (current.x > next.x) {
            // Moving up
            current.walls[0] = false;
            next.walls[2] = false;
        } else {
            // Moving down
            current.walls[2] = false;
            next.walls[0] = false;
        }
    }
}

void Maze::undoMove() 
{
    if (moveHistory.empty()) {
        cout << "No moves to undo!" << endl;
        _getch(); // Wait for key press
        return;
    }

    // Remove the last move
    moveHistory.pop();

    // If there are no moves left, reset to start
    if (moveHistory.empty()) {
        playerPosition = {0, 0};
    } else {
        // Restore previous position
        PlayerMove lastMove = moveHistory.top();
        playerPosition = lastMove.position;
    }
}

void Maze::startTimer()
{
    startTime = chrono::steady_clock::now();
    timeHeap = priority_queue<int, vector<int>, greater<int>>();
    timeHeap.push(0); // Initial time
}

int Maze::getElapsedTime()
{
    auto currentTime = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
}

void Maze::displayTimer()
{
    int elapsedTime = getElapsedTime();
    cout << "Time elapsed: " << elapsedTime << " seconds" << endl;
}

void Maze::findAndDisplayShortestPath() 
{
    // Start and end positions
    int startX = 0, startY = 0;
    int endX = rows - 1, endY = cols - 1;

    // Queue for BFS (stores x, y coordinates)
    queue<int> bfsQueue;

    // Visited cells
    bool visited[rows][cols] = {false};

    // To track the previous cell for path reconstruction
    int previous[rows][cols][2]; // Stores {prevX, prevY} for each cell

    // Enqueue the starting position
    bfsQueue.push(startX);
    bfsQueue.push(startY);
    visited[startX][startY] = true;

    bool found = false;

    while (!bfsQueue.empty()) {
        int currentX = bfsQueue.front(); bfsQueue.pop();
        int currentY = bfsQueue.front(); bfsQueue.pop();

        // Reached the end
        if (currentX == endX && currentY == endY) {
            found = true;
            break;
        }

        // Possible moves: up, right, down, left
        int directions[4][2] = {
            {-1, 0}, // Up
            {0, 1},  // Right
            {1, 0},  // Down
            {0, -1}  // Left
        };

        for (int i = 0; i < 4; ++i) {
            int newX = currentX + directions[i][0];
            int newY = currentY + directions[i][1];

            // Check bounds and wall constraints
            bool canMove = false;
            if (directions[i][0] == -1 && newX >= 0 && !grid[currentX][currentY]->walls[0]) canMove = true;     // Up
            if (directions[i][0] == 1 && newX < rows && !grid[currentX][currentY]->walls[2]) canMove = true;    // Down
            if (directions[i][1] == -1 && newY >= 0 && !grid[currentX][currentY]->walls[3]) canMove = true;    // Left
            if (directions[i][1] == 1 && newY < cols && !grid[currentX][currentY]->walls[1]) canMove = true;   // Right

            if (canMove && !visited[newX][newY]) {
                bfsQueue.push(newX);
                bfsQueue.push(newY);
                visited[newX][newY] = true;
                previous[newX][newY][0] = currentX;
                previous[newX][newY][1] = currentY;
            }
        }
    }

    if (!found) {
        cout << "No path found!" << endl;
        return;
    }

    // Reconstruct the path and calculate the number of steps
    int currentX = endX, currentY = endY;
    bool path[rows][cols] = {false};
    int pathLength = 0;

    while (!(currentX == startX && currentY == startY)) {
        path[currentX][currentY] = true;
        int prevX = previous[currentX][currentY][0];
        int prevY = previous[currentX][currentY][1];
        currentX = prevX;
        currentY = prevY;
        pathLength++;
    }
    path[startX][startY] = true;

    // Display the maze with the path
    cout << "Shortest Path:" << endl;
    for (int i = 0; i < rows; ++i) {
        // Print top walls
        for (int j = 0; j < cols; ++j) {
            cout << (grid[i][j]->walls[0] ? "+---" : "+   ");
        }
        cout << "+" << endl;

        // Print left walls and cells
        for (int j = 0; j < cols; ++j) {
            if (path[i][j]) {
                cout << (grid[i][j]->walls[3] ? "| * " : "  * ");
            } else {
                cout << (grid[i][j]->walls[3] ? "|   " : "    ");
            }
        }
        cout << "|" << endl;
    }

    // Print bottom line
    for (int j = 0; j < cols; ++j) {
        cout << "+---";
    }
    cout << "+" << endl;

    // Display the number of steps
    cout << "Path length: " << pathLength + 1 << " steps" << endl;
}

void Maze::provideHint() 
{
    // Start and end positions
    int startX = playerPosition.first;
    int startY = playerPosition.second;
    int endX = rows - 1, endY = cols - 1;

    // Queue for BFS (stores x, y coordinates)
    queue<pair<int, int>> bfsQueue;

    // Visited cells
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // To track the previous cell for path reconstruction
    vector<vector<pair<int, int>>> previous(rows, vector<pair<int, int>>(cols, {-1, -1}));

    // Enqueue the starting position
    bfsQueue.push({startX, startY});
    visited[startX][startY] = true;

    bool found = false;

    // BFS to find the path
    while (!bfsQueue.empty()) {
        auto [currentX, currentY] = bfsQueue.front();
        bfsQueue.pop();

        // Reached the end
        if (currentX == endX && currentY == endY) {
            found = true;
            break;
        }

        // Possible moves: up, right, down, left
        vector<pair<int, int>> directions = {
            {-1, 0}, // Up
            {0, 1},  // Right
            {1, 0},  // Down
            {0, -1}  // Left
        };

        for (const auto& [dx, dy] : directions) {
            int newX = currentX + dx;
            int newY = currentY + dy;

            // Check bounds and wall constraints
            bool canMove = false;
            if (dx == -1 && newX >= 0 && !grid[currentX][currentY]->walls[0]) canMove = true;     // Up
            if (dx == 1 && newX < rows && !grid[currentX][currentY]->walls[2]) canMove = true;    // Down
            if (dy == -1 && newY >= 0 && !grid[currentX][currentY]->walls[3]) canMove = true;    // Left
            if (dy == 1 && newY < cols && !grid[currentX][currentY]->walls[1]) canMove = true;   // Right

            if (canMove && !visited[newX][newY]) {
                bfsQueue.push({newX, newY});
                visited[newX][newY] = true;
                previous[newX][newY] = {currentX, currentY};
            }
        }
    }

    if (!found) {
        cout << "No path found!" << endl;
        return;
    }

    // Reconstruct the path to the next step
    int currentX = endX, currentY = endY;
    pair<int, int> nextStep;

    while (!(currentX == startX && currentY == startY)) {
        nextStep = {currentX, currentY};
        int prevX = previous[currentX][currentY].first;
        int prevY = previous[currentX][currentY].second;
        currentX = prevX;
        currentY = prevY;
    }

    // Provide a hint based on the next step
    string hintDirection;
    if (nextStep.first < startX) {
        hintDirection = "Move UP";
    } else if (nextStep.first > startX) {
        hintDirection = "Move DOWN";
    } else if (nextStep.second < startY) {
        hintDirection = "Move LEFT";
    } else if (nextStep.second > startY) {
        hintDirection = "Move RIGHT";
    }

    // Display the hint
    cout << "Hint: " << hintDirection << " towards the end of the maze." << endl;
    
    // Optional: Display a visual hint on the maze
    displayHintOnMaze(nextStep);
}

void Maze::displayHintOnMaze(const pair<int, int>& hintCell) 
{
    cout << "Hint Path:" << endl;
    for (int i = 0; i < rows; ++i) {
        // Print top walls
        for (int j = 0; j < cols; ++j) {
            cout << (grid[i][j]->walls[0] ? "+---" : "+   ");
        }
        cout << "+" << endl;

        // Print left walls and cells
        for (int j = 0; j < cols; ++j) {
            if (i == hintCell.first && j == hintCell.second) {
                cout << (grid[i][j]->walls[3] ? "| H " : "  H ");
            } else if (i == playerPosition.first && j == playerPosition.second) {
                cout << (grid[i][j]->walls[3] ? "| P " : "  P ");
            } else {
                cout << (grid[i][j]->walls[3] ? "|   " : "    ");
            }
        }
        cout << "|" << endl;
    }

    // Print bottom line
    for (int j = 0; j < cols; ++j) {
        cout << "+---";
    }
    cout << "+" << endl;
}