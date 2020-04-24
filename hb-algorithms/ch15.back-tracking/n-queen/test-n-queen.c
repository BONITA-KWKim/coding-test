#include <stdio.h>
#include <stdlib.h>
#include "n-queen.h"

int main(int argc, char **argv) {
    int i = 0;
    int queen_no = 0;
    int solution_count = 0;
    int *column;

    if(2 > argc) {
        printf("Usage: %s <Number of Queens>\n", argv[0]);
        return -1;
    }

    queen_no = atoi(argv[1]);
    column = (int *)calloc(queen_no, sizeof(int));

    for(i = 0; queen_no > i; ++i) {
        column[0] = i;
        find_solution_for_queen(column, 0, queen_no, &solution_count);
    }

    free(column);

    return 0;
}