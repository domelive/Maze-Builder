#include <raylib.h>
#include "maze.hpp"

int main(int argc, char* argv[]) {
    InitWindow(scr::WIDTH, scr::HEIGHT, "Maze Builder");
    SetTargetFPS(scr::FPS);

    Maze maze = Maze();    

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            maze.solveBFS(&maze.getGrid()[0], &maze.getGrid()[maze.getGrid().size() - 1]);
            maze.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
