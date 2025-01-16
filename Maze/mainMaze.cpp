#include "maze.h"

int main() {
    int rows = 10;
    int cols = 10;

    Maze maze(rows, cols);
    maze.generateMaze();

    // Display the maze
    maze.displayMaze();


    maze.play();

    // Find and display the shortest path
    maze.findAndDisplayShortestPath();

    return 0;
}
