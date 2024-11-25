#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>  
#include <conio.h> 

using namespace std;

// Maze structure 
struct Cell {
    int x, y;
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left

    Cell(int _x, int _y);
};

class Maze {
    private:
        int rows, cols;
        Cell*** grid;
        pair<int, int> playerPosition;
        
        int getUnvisitedNeighbors(Cell* cell, Cell* neighbors[]);
        void removeWalls(Cell& current, Cell& next);
        void movePlayer(char direction);

    public:
        Maze(int r, int c);
        ~Maze();

        void displayMaze();
        void generateMaze();
        void play();
};

#endif
