#include <stdio.h>
#include "maze-solver.h"

int main(int argc, char **argv) {
    int i = 0, j= 0;

    MazeInfo maze;

    if(2 > argc) {
        printf("Usage: MazeSolver <MazeFile>\n");
        return 0;
    }

    if(FAIL == get_maze(argv[1], &maze))
        return 0;

    if(FAIL == solve(&maze)) {
        printf("Cannot solve this maze\n");
        return 0;
    }

    for(i = 0; maze.row_size > i; ++i) {
        for(j = 0; maze.column_size > j; ++j) {
            printf("%c", maze.data[i][j]);
        }
        printf("\n");
    }

    return 0;
}