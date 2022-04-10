#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*introduction paragraph: 
partner netID: staceyl2
This program aims to solve a maze inside a given file, where"%" would represent walls, "S" represents the starting point, and "E" represents the end point. This program utilizes recursion and backtracking to solve the maze, setting the solution path as "*", and if solution is incorrect, backtrack and turn them into "~", representing visited. The final outcome would be a printed maze with the original starting point, ending point, and walls, together with the visited path and final solution printed. Locations not visited and aren't walls,"S", or"E" are left as " "(spaces).
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int _row,_col,_startR,_startC,_endR,_endC, i, j;
    char**_cells;
    maze_t* mazeptr = (maze_t*)malloc(sizeof(maze_t));
    FILE* fptr = fopen(fileName, "r");
    
    if(mazeptr==NULL){
    	printf("Failed to allocate maze.");
	return NULL;
    }							//check if the allocation is successful
    
    if(fptr ==NULL){
    	printf("File not found.");
	return NULL;
    }							//check if the file exist
    
    fscanf(fptr, "%d%d\n",&_col,&_row);			//read col and row from file
    _cells = (char**)malloc(_row * sizeof(char*));		//allocate pointer for every row
    
    for(i=0; i< _row; i++){
    	_cells[i]=(char *)malloc(_col * sizeof(char));
    }							//allocate char array for each row
    
    for(i=0; i<_row; i++){
    	for(j=0; j<_col; j++){
		fscanf(fptr, "%c", &_cells[i][j]);	// read each cell from the file
		
		if(_cells[i][j]==START){
			_startR = i;
			_startC = j;			// store START location
		}
		if(_cells[i][j]==END){
			_endR = i;
			_endC = j;			//store END location
		}
	}
	char discard;
	fscanf(fptr, "%c", &discard);
    }
    
    mazeptr->height = _row;
    mazeptr->width = _col;
    mazeptr->startRow = _startR;
    mazeptr->startColumn = _startC;
    mazeptr->endRow = _endR;
    mazeptr->endColumn = _endC;
    mazeptr->cells = _cells;				// load into struct
    
    fclose(fptr);					//close file
    return mazeptr;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i=0; i<maze->height; i++){
    	free(maze->cells[i]);				//free rows;
    }
    free(maze->cells);					//free cells array
    free(maze);						//free maze struct
    maze = NULL;
    
}


/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i;
    char** array = maze->cells;
    
    for(i=0; i<maze->height; i++){
    	printf("%s\n", array[i]);
    }
    
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    
    if(col<0|| col>=maze->width|| row<0|| row>=maze->height){
    	return 0;
    }						//base case: out of bound return 0
    
    if(maze->cells[row][col]==WALL|| maze->cells[row][col]==VISITED|| maze->cells[row][col]==PATH){
    
    	return 0;				//base case: walls or visited location return 0
    }
    
   /* if(maze->cells[row][col]==END){
    	return 1;				// return 1 if reached END
    }*/
    if(col==maze->endColumn && row==maze->endRow){
    	maze->cells[maze->startRow][maze->startColumn] = START;
	return 1;
    }
    
    if(maze->cells[row][col]!=END){
    	maze->cells[row][col]=PATH;		//set current place as PATH (if not START)
    }
    if(solveMazeDFS(maze, col-1, row)){
    	return 1;				//try solve to the left
    }
    if(solveMazeDFS(maze, col+1, row)){
    	return 1;				//try solve to the right
    }
    if(solveMazeDFS(maze, col, row-1)){
    	return 1;				//try solve upwards
    }
    if(solveMazeDFS(maze, col, row+1)){
    	return 1;				//try solve downwards
    }
    if(maze->cells[row][col]!= START &&maze->cells[row][col]!=END){
    	maze->cells[row][col]= VISITED;		//mark as VISITED(not START or END)
    }
    
    return 0;					//else return 0
    
}
