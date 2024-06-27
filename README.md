# Maze-Builder

## Running Maze Generator:
+ To run the program type the following line in the terminal:
```sh
    g++ main.cpp maze.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

## Maze class:
+ __Cell struct__:
    + Each cell of the maze has x and y coordinates to represent their position,
    an array of booleans that represents the walls (respectively top, right, bottom
    and left), and a variable that represents the visited state of the cell.

+ __Maze class__:
    + The maze class implements the generation and displaying of the maze.
    The generation it's done using random DFS algorithm with recursive backtracking.
