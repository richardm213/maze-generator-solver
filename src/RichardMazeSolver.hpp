#ifndef RICHARDMAZESOLVER_HPP
#define RICHARDMAZESOLVER_HPP
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include <vector>

class RichardMazeSolver : public MazeSolver
{

public:
    // Default Constructor.
    RichardMazeSolver();
    // Solves the maze.
    void solveMaze(const Maze &maze, MazeSolution &mazeSolution) override;

private:
    // 2d vector that keeps track of which cells have been visited.
    std::vector<std::vector<bool>> visited;

    // Initializes the visited 2d vector.
    void initVisited(const Maze &maze);
    // Draws a red line corresponding to the maze solution. This function uses recursive backtracking.
    void drawSolution(int x, int y, const Maze &maze, MazeSolution &mazeSolution);
    // Checks based on the current location, if it is possible to travel in the given direction.
    bool isValidDirection(int x, int y, Direction d, const Maze &maze, MazeSolution &mazeSolution);
    // Returns the opposite direction of the given direction.
    Direction oppositeDirection(Direction d);
};

#endif
