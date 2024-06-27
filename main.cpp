#include <raylib.h>
#include "maze.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    InitWindow(cst::S_WIDTH, cst::S_HEIGHT, "Maze Generator");
    SetTargetFPS(2);
    
    Maze maze = Maze();   

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            maze.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
