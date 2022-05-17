#include "RichardMazeGenerator.hpp"

RichardMazeGenerator::RichardMazeGenerator() {}

void RichardMazeGenerator::generateMaze(Maze &maze)
{
    maze.addAllWalls();
    initVisited(maze);
    digAndMakeMaze(0, 0, maze);
}

void RichardMazeGenerator::digAndMakeMaze(int x, int y, Maze &maze)
{
    std::vector<Direction> v{Direction::up,
                             Direction::down,
                             Direction::left,
                             Direction::right};
    visited[x][y] = true;
    std::shuffle(v.begin(), v.end(), engine);

    for (int i = 0; i < v.size(); i++)
    {
        if (isValidDirection(x, y, v[i], maze))
        {
            maze.removeWall(x, y, v[i]);
            if (v[i] == Direction::up)
                digAndMakeMaze(x, y - 1, maze);
            else if (v[i] == Direction::down)
                digAndMakeMaze(x, y + 1, maze);
            else if (v[i] == Direction::right)
                digAndMakeMaze(x + 1, y, maze);
            else if (v[i] == Direction::left)
                digAndMakeMaze(x - 1, y, maze);
        }
    }
}

void RichardMazeGenerator::initVisited(Maze &maze)
{
    visited.resize(maze.getWidth());
    for (int i = 0; i < maze.getWidth(); i++)
        visited[i].resize(maze.getHeight());
    for (int x = 0; x < maze.getWidth(); x++)
        for (int y = 0; y < maze.getHeight(); y++)
            visited[x][y] = false;
}

bool RichardMazeGenerator::isValidDirection(int x, int y, Direction d, Maze &maze)
{
    int x2 = int(x);
    int y2 = int(y);
    if (d == Direction::up)
        y2 -= 1;
    else if (d == Direction::down)
        y2 += 1;
    else if (d == Direction::right)
        x2 += 1;
    else if (d == Direction::left)
        x2 -= 1;
    // Makes sure that if we move in direction d, that we are still in the bounds of the maze and are in a cell that is unvisited.
    if (x2 >= 0 && x2 <= maze.getWidth() - 1 && y2 >= 0 && y2 <= maze.getHeight() - 1 && !(visited[x2][y2]))
        return true;
    return false;
}
