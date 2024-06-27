#include "maze.hpp"
#include <raylib.h>

Maze::Maze() {
    // srand(time(nullptr));
    for(int i = 0; i < cst::G_ROWS; i++) {
        for(int j = 0; j < cst::G_COLS; j++) {
            this->grid.push_back(Cell(j, i));
        }
    }
    
    this->source = &this->grid[0];
    // immediate generation of the maze
    this->generateMazeDFS(this->source);
}

void Maze::draw() {
    for(int i = 0; i < this->grid.size(); i++) {
        this->drawCell(this->grid[i]);
    }

    // animated process
    /*a
    this->source->visited = true;
    Cell* next = this->selectRandomNeighbor(this->source);
    DrawRectangle(this->source->xPos * cst::CELL_SIZE, this->source->yPos * cst::CELL_SIZE, cst::CELL_SIZE, cst::CELL_SIZE, RED);

    if(next) {
        this->visitedCells.push(this->source);
        this->removeWalls(this->source, next);
        this->visitedCells.push(next);
        next->visited = true;
        this->source = next;
    } else if(this->visitedCells.size() > 0){
        this->source = this->visitedCells.top();
        this->visitedCells.pop();
    } else {
        return;
    }
    */
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
    if(!current || !next) {
        return;
    }

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
    } else if(yDiff == -1){
        current->walls[2] = false;
        next->walls[0] = false;
    }
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

void Maze::generateMazeDFS(Cell* current) {
    current->visited = true;
    Cell* next = nullptr;

    while(true) {
        std::vector<Cell*> neighbors;
       
        if(current->xPos > 0) {
            int left = this->index(current->xPos - 1, current->yPos);
            if(!this->grid[left].visited) {
                neighbors.push_back(&this->grid[left]);
            }
        }
        if(current->yPos > 0) {
            int top = this->index(current->xPos, current->yPos - 1);
            if(!this->grid[top].visited) {
                neighbors.push_back(&this->grid[top]);
            }
        }
        if(current->xPos < cst::G_COLS - 1) {
            int right = this->index(current->xPos + 1, current->yPos);
            if(!this->grid[right].visited) {
                neighbors.push_back(&this->grid[right]);
            }
        }
        if(current->yPos < cst::G_ROWS - 1) {
            int bottom = this->index(current->xPos, current->yPos + 1);
            if(!this->grid[bottom].visited) {
                neighbors.push_back(&this->grid[bottom]);
            }
        }

        if(neighbors.size() > 0) {
            int randVal = rand() % neighbors.size();
            next = neighbors[randVal];
            this->visitedCells.push(current);
            this->removeWalls(current, next);
            current = next;
            current->visited = true;
        } else if(this->visitedCells.size() > 0) {
            current = this->visitedCells.top();
            this->visitedCells.pop();
        } else {
            break;
        }
    }
}
