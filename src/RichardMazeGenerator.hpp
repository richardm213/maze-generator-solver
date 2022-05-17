#ifndef RICHARDMAZEGENERATOR_HPP
#define RICHARDMAZEGENERATOR_HPP
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include <vector>
#include <algorithm>
#include <random>

class RichardMazeGenerator : public MazeGenerator
{

public:
    // Default constructor.
    RichardMazeGenerator();
    // Generates the maze.
    void generateMaze(Maze &maze) override;

private:
    // 2d vector that keeps track of which cells have been visited.
    std::vector<std::vector<bool>> visited;
    // These variables are used so that we can randomize the maze.
    std::random_device device;
    std::default_random_engine engine{device()};

    // Initializes the visited 2d vector.
    void initVisited(Maze &maze);
    // Makes the maze through recursive backtracking.
    void digAndMakeMaze(int x, int y, Maze &maze);
    // Checks based on the current location, if it is possible to travel in the given direction.
    bool isValidDirection(int x, int y, Direction d, Maze &maze);
};

#endif
