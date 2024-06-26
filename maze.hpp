#include "utils.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>

class Cell {
    public:
        int xPos, yPos;
        bool visited = false;
        bool walls[4] = {true, true, true, true}; // top, right, bottom, left
        
        Cell(int xPos, int yPos);
        void drawCell(Cell current);
};

class Maze {
    private:
        std::vector<Cell> grid;
        std::stack<Cell*> cellStack;
        void removeWalls(Cell* current, Cell* next);
        int index(int x, int y);
        void generateMazeDFS(Cell* current);
        void initializeMaze();
    public:
        Maze();
        void draw();
        void solveBFS(Cell* start, Cell* end);
        std::vector<Cell> getGrid();
};
