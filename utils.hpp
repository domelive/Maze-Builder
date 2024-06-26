#include <raylib.h>

namespace scr {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int FPS = 60;
    const int CELL_SIZE = 20;
}

namespace grid {
    const int ROWS = scr::HEIGHT / scr::CELL_SIZE;
    const int COLS = scr::WIDTH / scr::CELL_SIZE;
}
