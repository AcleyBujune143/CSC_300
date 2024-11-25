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
            Cell* next = neighbors[rand() % neighborCount];
            removeWalls(*current, *next);
            next->visited = true;
            cellStack.push(next);
        } else {
            cellStack.pop();
        }
    }
}

void Maze::play() 
{
    char input;
    while (true) {
            system("cls"); // Clear screen for Windows

        displayMaze();
        cout << "Use WASD to move (W = up, A = left, S = down, D = right), Q to quit." << endl;
        input = _getch();
        if (input == 'q' || input == 'Q') {
            break;
        }
        movePlayer(input);
        if (playerPosition == make_pair(rows - 1, cols - 1)) {
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
    int xDiff = current.x - next.x;
    int yDiff = current.y - next.y;
    if (xDiff == 1) {
        current.walls[0] = false;
        next.walls[2] = false;
    } else if (xDiff == -1) {
        current.walls[2] = false;
        next.walls[0] = false;
    } else if (yDiff == 1) {
        current.walls[3] = false;
        next.walls[1] = false;
    } else if (yDiff == -1) {
        current.walls[1] = false;
        next.walls[3] = false;
    }
}

void Maze::movePlayer(char direction) 
{
    int x = playerPosition.first;
    int y = playerPosition.second;

    if (direction == 'w' || direction == 'W') {
        if (x > 0 && !grid[x][y]->walls[0]) {
            playerPosition.first--;
        }
    } else if (direction == 'a' || direction == 'A') {
        if (y > 0 && !grid[x][y]->walls[3]) {
            playerPosition.second--;
        }
    } else if (direction == 's' || direction == 'S') {
        if (x < rows - 1 && !grid[x][y]->walls[2]) {
            playerPosition.first++;
        }
    } else if (direction == 'd' || direction == 'D') {
        if (y < cols - 1 && !grid[x][y]->walls[1]) {
            playerPosition.second++;
        }
    }
}
