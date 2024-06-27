#include "maze.hpp"
#include <raylib.h>

Maze::Maze() {
    srand(time(nullptr));
    for(int i = 0; i < cst::G_ROWS; i++) {
        for(int j = 0; j < cst::G_COLS; j++) {
            this->grid.push_back(Cell(j, i));
        }
    }
    this->source = &this->grid[0];
}

void Maze::draw() {
    for(int i = 0; i < this->grid.size(); i++) {
        this->drawCell(this->grid[i]);
    }

    this->source->visited = true;
    Cell* next = this->selectRandomNeighbor(this->source);
    
    if(next) {
        next->visited = true;
        this->source = next;
    }
}

void Maze::drawCell(Cell current) {
    int x = current.xPos * cst::CELL_SIZE;
    int y = current.yPos * cst::CELL_SIZE;

    if(current.visited) {
        DrawRectangle(x, y, cst::CELL_SIZE, cst::CELL_SIZE, BLUE);
    }

    if(current.walls[0]) {
        DrawLine(x, y, x + cst::CELL_SIZE, y, BLACK);
    }
    if(current.walls[1]) {
        DrawLine(x + cst::CELL_SIZE, y, x + cst::CELL_SIZE, y + cst::CELL_SIZE, BLACK);
    }
    if(current.walls[2]) {
        DrawLine(x, y + cst::CELL_SIZE, x + cst::CELL_SIZE, y + cst::CELL_SIZE, BLACK);
    }
    if(current.walls[3]) {
        DrawLine(x, y, x, y + cst::CELL_SIZE, BLACK);
    }
}

void Maze::removeWalls(Cell* current, Cell* next) {

}

int Maze::index(int x, int y) {
    if(x < 0 || y < 0 || x > cst::G_COLS - 1 || y > cst::G_ROWS - 1) {
        return -1;
    }
    return x + y * cst::G_COLS;
}

Cell* Maze::selectRandomNeighbor(Cell* current) {
    srand(time(nullptr));
    std::vector<Cell*> neighbors;
    
    int top = this->index(current->xPos, current->yPos - 1);
    int right = this->index(current->xPos + 1, current->yPos);
    int bottom = this->index(current->xPos, current->yPos + 1);
    int left = this->index(current->xPos - 1, current->yPos);

    if(!this->grid[top].visited && top != -1) {
        neighbors.push_back(&this->grid[top]);
    }
    if(!this->grid[right].visited && right != -1) {
        neighbors.push_back(&this->grid[right]);
    }
    if(!this->grid[bottom].visited && bottom != -1) {
        neighbors.push_back(&this->grid[bottom]);
    }
    if(!this->grid[left].visited && left != -1) {
        neighbors.push_back(&this->grid[left]);
    }

    if(neighbors.size() > 0) {
        int randVal = rand() % neighbors.size();
        return neighbors[randVal];
    } else {
        return nullptr;
    }
}
