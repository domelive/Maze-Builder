#include <raylib.h>
#include "maze.hpp"

int main(int argc, char* argv[]) {
    InitWindow(scr::WIDTH, scr::HEIGHT, "Maze Builder");
    SetTargetFPS(scr::FPS);

    Maze maze = Maze();    

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            maze.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
