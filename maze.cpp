#include "maze.hpp"
#include <raylib.h>

Cell::Cell(int xPos, int yPos) {
    this->xPos = xPos;
    this->yPos = yPos;
}

void Cell::drawCell(Cell current) {
    int xStart = current.xPos * scr::CELL_SIZE;
    int yStart = current.yPos * scr::CELL_SIZE;

    if(current.visited) {
        DrawRectangle(xStart, yStart, xStart + scr::CELL_SIZE, yStart + scr::CELL_SIZE, GRAY);
    }

    if(current.walls[0]) {
        DrawLine(xStart, yStart, xStart + scr::CELL_SIZE, yStart, BLACK);
    }
    if(current.walls[1]) {
        DrawLine(xStart + scr::CELL_SIZE, yStart, xStart + scr::CELL_SIZE, yStart + scr::CELL_SIZE, BLACK);
    }
    if(current.walls[2]) {
        DrawLine(xStart, yStart + scr::CELL_SIZE, xStart + scr::CELL_SIZE, yStart + scr::CELL_SIZE, BLACK);
    }
    if(current.walls[3]) {
        DrawLine(xStart, yStart, xStart, yStart + scr::CELL_SIZE, BLACK);
    }
}

void Maze::removeWalls(Cell* current, Cell* next) {
    int xDiff = current->xPos - next->xPos;

    if(xDiff == 1) {
        current->walls[3] = false;
        next->walls[1] = false;
    } else if(xDiff == -1) {
        current->walls[1] = false;
        next->walls[3] = false;
    }

    int yDiff = current->yPos - next->yPos;

    if(yDiff == 1) {
        current->walls[0] = false;
        next->walls[2] = false;
    } else if(yDiff == -1) {
        current->walls[2] = false;
        next->walls[0] = false;
    }
}

int Maze::index(int x, int y) {
    if(x < 0 || y < 0 || x > grid::COLS || y > grid::ROWS) {
        return -1;
    }
    return x + y * grid::COLS;
}

void Maze::generateMazeDFS(Cell* current) {
    current->visited = true;
    Cell* next = nullptr;
    
    while(true) {
        // cheking for neighbors
        std::vector<Cell*> neighbors;

        // top neighbor
        if(current->yPos > 0) {
            Cell* top = &this->grid[this->index(current->xPos, current->yPos - 1)];
            if(!top->visited) {
                neighbors.push_back(top);
            }
        }
        // right neighbor
        if(current->xPos < grid::COLS - 1) {
            Cell* right = &this->grid[this->index(current->xPos + 1, current->yPos)];
            if(!right->visited) {
                neighbors.push_back(right);
            }
        }
        // bottom neighbor
        if(current->yPos < grid::ROWS - 1) {
            Cell* bottom = &this->grid[this->index(current->xPos, current->yPos + 1)];
            if(!bottom->visited) {
                neighbors.push_back(bottom);
            }
        }
        // left neighbor
        if(current->xPos > 0) {
            Cell* left = &this->grid[this->index(current->xPos - 1, current->yPos)];
            if(!left->visited) {
                neighbors.push_back(left);
            }
        }

        if(neighbors.size() > 0) {
            int randVal = rand() % neighbors.size();
            next = neighbors[randVal];
            this->removeWalls(current,next);
            this->cellStack.push(current);
            current = next;
            current->visited = true;
        } else if(this->cellStack.size() > 0) {
            current = this->cellStack.top();
            this->cellStack.pop();
        } else {
            break;
        }
    }
}

void Maze::initializeMaze() {
    for(int row = 0; row < grid::ROWS; row++) {
        for(int col = 0; col < grid::COLS; col++) {
            this->grid.push_back(Cell(col, row));
        }
    }
    this->generateMazeDFS(&grid[0]);
}

Maze::Maze() {
    initializeMaze();
}


void Maze::draw() {
    for(int i = 0; i < grid.size(); i++) {
        grid[i].drawCell(grid[i]);
    }
}
