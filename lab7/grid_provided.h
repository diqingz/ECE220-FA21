#ifndef GRID_PROVIDED_H_
#define GRID_PROVIDED_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

// Function: is_val_in_row
int is_val_in_row(const int val, const int i, int grid[5][5]);

// Function: is_val_in_col
int is_val_in_col(const int val, const int i, int grid[5][5]);

// Function: is_val_valid
int is_val_valid(const int val, const int i, const int j, int grid[5][5]);

//If there is no unassigned location, we are done
int FindUnassignedLocation(int grid[5][5], int *i, int *j);


// Procedure: print_grid
void print_grid(int grid[5][5]);

void write_grid(const char wpath[], int grid[5][5]);


#endif
