#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Introduction paragraph: partner netID: staceyl2
// This program aims to solve for the correct answer to put in every block of a sudoku puzzle composed of 9 3*3 grids with recursive backtracking. This program //utilizes the functions is_val_in_row, is_val_in_col, and is_value_in_3*3 zone to calculate if each possible answer fits the three basic rules in sudoku. The 
// function is_val_valid combines and check if all three above function test passes, this would then be called in solve_sudoku function to help solve the sudoku board.


// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  int j;
	for(j = 0; j <= 8; j++)        //loop through column 
	{
		if(sudoku[i][j] == val)       //compare values in the row, if eqal to val, return 1
		{
		  return 1;
		}
	}
  return 0;

  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i;
	for(i = 0; i <= 8; i++)         //loop through row
	{
		if(sudoku[i][j] == val)         //compare values in column, if equal to val, return 1
		{
			return 1;
		}
	}
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  

        int x = i - (i % 3);         
	int y = j - (j % 3);       

	for(int n = x; n <= x + 2; n++)        
	{
		for(int m = y; m <= y + 2; m++)
		{
			if(sudoku[n][m] == val)    //if the value equals to the calue of 3x3 block, return 1.
			{
				return 1;
			}
		}	
	}

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

	
  if(!is_val_in_col(val, j, sudoku) && !is_val_in_row(val, i, sudoku) && !is_val_in_3x3_zone(val, i, j, sudoku))  
  {
 	return 1; 	
  }

  return 0;


  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int count = 0;       
  int i, j;
  int x, y;
  int num;
  for(x = 0; x <= 8; x++)
  {
  	for(y = 0; y <= 8; y++)
	{
		if(sudoku[x][y] == 0)
		{
			count++;               
			i = x;								// set x = i, y = j, if encounter a empty block
			j = y;
		}
	}
  }
  
  if(count == 0)         
  {
  	return 1;
  }
  
  for(num = 1; num <= 9; num++)				//loop through the nine possible values for a block
  {
  	if(is_val_valid(num, i, j, sudoku))       
	{
		sudoku[i][j] = num;									    // if value is valid at (i, j) , set it to num
		if(solve_sudoku(sudoku))                
		{
			return 1;
		}
		sudoku[i][j] = 0;                  // wrong answer because the entered value contradicts with another value
	}
  }
  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





