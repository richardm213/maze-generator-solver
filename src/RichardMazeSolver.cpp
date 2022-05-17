#include "RichardMazeSolver.hpp"

RichardMazeSolver::RichardMazeSolver() {}

void RichardMazeSolver::solveMaze(const Maze &maze, MazeSolution &mazeSolution)
{
    mazeSolution.restart();
    initVisited(maze);
    std::pair<int, int> starting_coordinates = mazeSolution.getStartingCell();
    drawSolution(starting_coordinates.first, starting_coordinates.second, maze, mazeSolution);
}

void RichardMazeSolver::drawSolution(int x, int y, const Maze &maze, MazeSolution &mazeSolution)
{
    if (mazeSolution.isComplete())
        return;

    std::vector<Direction> v{Direction::up,
                             Direction::down,
                             Direction::left,
                             Direction::right};
    visited[x][y] = true;
    for (int i = 0; i < v.size(); i++)
    {
        if (isValidDirection(x, y, v[i], maze, mazeSolution))
        {
            mazeSolution.extend(v[i]);
            if (v[i] == Direction::up)
                drawSolution(x, y - 1, maze, mazeSolution);
            else if (v[i] == Direction::down)
                drawSolution(x, y + 1, maze, mazeSolution);
            else if (v[i] == Direction::right)
                drawSolution(x + 1, y, maze, mazeSolution);
            else if (v[i] == Direction::left)
                drawSolution(x - 1, y, maze, mazeSolution);
        }
        if (mazeSolution.isComplete())
            return;
    }
    std::pair<int, int> starting_coordinates = mazeSolution.getStartingCell();
    if (x == starting_coordinates.first && y == starting_coordinates.second)
        return;
    mazeSolution.backUp();
}

void RichardMazeSolver::initVisited(const Maze &maze)
{
    visited.resize(maze.getWidth());
    for (int i = 0; i < maze.getWidth(); i++)
        visited[i].resize(maze.getHeight());
    for (int x = 0; x < maze.getWidth(); x++)
        for (int y = 0; y < maze.getHeight(); y++)
            visited[x][y] = false;
}

bool RichardMazeSolver::isValidDirection(int x, int y, Direction d, const Maze &maze, MazeSolution &mazeSolution)
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
    if (!(maze.wallExists(x, y, d)) && x2 >= 0 && x2 <= maze.getWidth() - 1 && y2 >= 0 && y2 <= maze.getHeight() - 1 && !(visited[x2][y2]))
    {
        std::vector<Direction> movements = mazeSolution.getMovements();
        if (movements.size() > 0)
        {
            // Makes sure that the direction isn't the opposite direction of the previous movement.
            if (oppositeDirection(d) != movements[movements.size() - 1])
                return true;
            return false;
        }
        else
            return true;
    }
    return false;
}

Direction RichardMazeSolver::oppositeDirection(Direction d)
{
    if (d == Direction::up)
        return Direction::down;
    else if (d == Direction::down)
        return Direction::up;
    else if (d == Direction::right)
        return Direction::left;
    else
        return Direction::right;
}
