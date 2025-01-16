#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>  
#include <conio.h>
#include <climits>
#include <chrono>
#include <functional>
#include <vector>
#include <unordered_map>

using namespace std;

struct Cell {
    int x, y;
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left 
    Cell(int _x, int _y);
};

// Struct to represent a move for undo functionality
struct PlayerMove {
    pair<int, int> position;
    char direction;
};

class Maze {
private:
    int rows, cols;
    Cell*** grid;
    pair<int, int> playerPosition;

    // Stack to store previous moves for undo functionality
    stack<PlayerMove> moveHistory;

    // Priority queue for timer tracking
    priority_queue<int, vector<int>, greater<int>> timeHeap;
    chrono::steady_clock::time_point startTime;

    int getUnvisitedNeighbors(Cell* cell, Cell* neighbors[]);
    void removeWalls(Cell& current, Cell& next);
    void recordCheckpointTime();

public:
    Maze(int r, int c);
    ~Maze();

    void displayMaze();
    void generateMaze();
    void play();

    // Undo functionality
    void undoMove();

    // Hint functionality
    void provideHint();
    void displayHintOnMaze(const pair<int, int>& hintCell);

    // Shortest path functionality
    void findAndDisplayShortestPath();

    // Timer-related functions
    void startTimer();
    int getElapsedTime();
    void displayTimer();
};

#endif