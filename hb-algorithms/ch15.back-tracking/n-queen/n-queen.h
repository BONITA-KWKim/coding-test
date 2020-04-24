#ifndef __N_QUEEN_H__
#define __N_QUEEN_H__

#include <stdio.h>
#include <stdlib.h>

void print_solution(int *, int);
int  is_threatened(int *, int);
void find_solution_for_queen(int *, int, int, int *);

#endif