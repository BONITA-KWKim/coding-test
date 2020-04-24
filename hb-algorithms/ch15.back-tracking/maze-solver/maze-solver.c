#include "maze-solver.h"

int solve(MazeInfo *maze) {
    int i = 0, j = 0;
    int start_found = FAIL, result = FAIL;

    Position start;

    /* find start point */
    for(i = 0; maze->row_size > i; ++i) {
        for(j = 0; maze->column_size > j; ++j) {
            if(START == maze->data[i][j]) {
                start.x = i;
                start.y = j;
                start_found = SUCCESS;
                break;
            }
        }
    }

    if(FAIL == start_found) return FAIL;

    /* find exit */
    if(move_to(maze, &start, NORTH))
        result = SUCCESS;
    else if(move_to(maze, &start, SOUTH))
        result = SUCCESS;
    else if(move_to(maze, &start, WEST))
        result = SUCCESS;
    else if(move_to(maze, &start, EAST))
        result = SUCCESS;

    /* mark start point */
    maze->data[start.x][start.y] = START;

    return result;
}

int move_to(MazeInfo *maze, Position *cur, int dir){
    int i = 0;

    int dirs[] = {NORTH, SOUTH, WEST, EAST};

    Position next;

    if(GOAL == maze->data[cur->x][cur->y]) return SUCCESS;

    maze->data[cur->x][cur->y] = MARKED;

    for(i = 0; 4 > i; ++i) {
        if(FAIL == get_next_step(maze, cur, dirs[i], &next))
            continue;

        if(SUCCESS == move_to(maze, &next, NORTH))
            return SUCCESS;
    }

    maze->data[cur->x][cur->y] = WAY;

    return FAIL;
}

int get_next_step(MazeInfo *maze, Position *cur, int dir, Position *next) {
    switch(dir) {
        case NORTH:
        next->x = cur->x;
        next->y = cur->y - 1;

        if(-1 == next->y) return FAIL;
        break;
        case SOUTH:
        next->x = cur->x;
        next->y = cur->y + 1;

        if(maze->row_size == next->y) return FAIL;
        break;
        case WEST:
        next->x = cur->x - 1;
        next->y = cur->y;

        if(-1 == next->x) return FAIL;
        break;
        case EAST:
        next->x = cur->x + 1;
        next->y = cur->y;

        if(maze->column_size == next->x) return FAIL;
        break;
    }

    if(WALL == maze->data[next->x][next->y]) return FAIL;
    if(MARKED == maze->data[next->x][next->y]) return FAIL;

    return SUCCESS;
}

int get_maze(char *file_path, MazeInfo *maze) {
    int i = 0, j= 0;
    int row_size = 0, column_size = INIT_VALUE;

    FILE *fp;
    char buffer[MAX_BUFFER];

    if(NULL == (fp = fopen(file_path, "r"))) {
        printf("Cannot open file: %s\n", file_path);
        return FAIL;
    }

    while(NULL != fgets(buffer, MAX_BUFFER, fp)) {
        ++row_size;

        if(INIT_VALUE == column_size) {
            column_size = strlen(buffer) - 1;
        } else if((strlen(buffer) - 1) != column_size) {
            printf("Maze data in file: %s is not valid. %d\n", 
                file_path, strlen(buffer));

            fclose(fp);
            return FAIL;
        }
    }

    maze->row_size = row_size;
    maze->column_size = column_size;
    maze->data = (char**)malloc(sizeof(char*) * row_size);

    for(i = 0; row_size > i; ++i) {
        maze->data[i] = (char *)malloc(sizeof(char) * column_size);
    }

    rewind(fp);

    for(i = 0; row_size > i; ++i) {
        fgets(buffer, MAX_BUFFER, fp);
        for(j = 0; column_size > j; ++j) {
            maze->data[i][j] = buffer[j];
        }
    }

    fclose(fp);

    return SUCCESS;
}
