#include "n-queen.h"

void find_solution_for_queen(int *column, int row, int queen_no, int *solution_count) {
    if(is_threatened(column, row)) return;

    if((queen_no - 1) == row) {
        printf("Solution #%d: \n", ++(*solution_count));
        print_solution(column, queen_no);
    } else {
        for(int i = 0; queen_no > i; ++i) {
            column[row+1] = i;
            find_solution_for_queen(column, row+1, queen_no, solution_count);
        }
    }
}

int  is_threatened(int *column, int new_row) {
    int cur_row = 0;
    int threatened = 0;

    while(new_row > cur_row) {
        if(column[new_row] == column[cur_row] || 
            (abs(column[new_row] - column[cur_row]) == abs(new_row - cur_row))) {
            threatened = 1;
            break;
        }
        ++cur_row;
    }

    return threatened;
}

void print_solution(int *column, int queen_no){
    int i = 0, j = 0;

    for(i = 0; queen_no > i; ++i) {
        for(j = 0; queen_no > j; ++j) {
            if(j == column[i])
                printf("Q");
            else
                printf(".");
        }
        printf("\n");
    }

    printf("\n");
}
