#ifndef __MAZE_SOLVER_H__
#define __MAZE_SOLVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024
#define INIT_VALUE -1

#define START  'S'
#define GOAL   'G'
#define WAY    ' '
#define WALL   '#'
#define MARKED '+'

enum DERECTION {NORTH, SOUTH, EAST, WEST};
enum RESTUL {FAIL, SUCCESS};

typedef struct tagPosision {
    int x;
    int y;
} Position;

typedef struct tabMazeInfo {
    int column_size;
    int row_size;

    char **data;
} MazeInfo;

int solve(MazeInfo *);
int move_to(MazeInfo *, Position *, int);
int get_next_step(MazeInfo *, Position *, int, Position *);
int get_maze(char *, MazeInfo *);

#endif //__MAZE_SOLVER_H__
