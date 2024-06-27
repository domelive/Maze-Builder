#include <raylib.h>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include "utils.hpp"

struct Cell {
    int xPos, yPos;
    bool walls[4] = {true, true, true, true};
    bool visited = false;

    Cell(int xPos, int yPos) : xPos(xPos), yPos(yPos) {}
};

class Maze {
    public:
        Maze();
        void draw();
    private:
        std::vector<Cell> grid;
        std::stack<Cell*> visitedCells;
        Cell* source;

        void drawCell(Cell current);
        void removeWalls(Cell* current, Cell* next);
        int index(int x, int y); // converts a 2D index into a 1D index
        Cell* selectRandomNeighbor(Cell* current);
        void generateMazeDFS(Cell* current);
};
