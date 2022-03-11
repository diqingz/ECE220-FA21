/*Introduction paragraph: 
partner netID: staceyl2
This program updates the map of a terminal version of game of life step by step, where given a 1-D array of the cell map, the program would determine the new changes that would occur on the map based on the rules.
Any cell with less than 2 live neighbors or more than three neighbors dies.
ANy cell with 2 living neighbors lives on.
Any dead cell that has three living neighbors revives.

*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int calPos(int row, int col, int boardColSize);

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int count = 0;
  int currRow = row;
  int currCol = col;
  int index;

  for (int i = currRow-1; i<=currRow+1; i++){
    if(i<boardRowSize && i>=0){
      for(int j = currCol-1; j<= currCol+1; j++){
	if (j <boardColSize && j>=0){
	  if(i !=currRow || j!=currCol){
	    index = board[i*boardColSize + j];
	    if (index == 1){
	    count= count +1;
	    }
	  }
	}
      }
    }
  }
  return count;

}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int newBoard[boardRowSize*boardColSize];
  //create a temporary board to store the new updates of the board

  for(int m = 0;m< boardRowSize; m++){
    for(int n = 0 ; n<boardColSize ;n++){
      int index = calPos(m,n,boardColSize);
      int liveNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize,m,n );
      if (liveNeighbors ==3){
	newBoard[index]=1;
      }//three living neighbors always result in a alive cell
      else if (liveNeighbors<2||liveNeighbors>3){
	newBoard[index]=0;
      }
      else{
	newBoard[index]=board[index];
      }
    }
  }
  //update temp board in cases of three alive neighbors and less than two or more than three alive neighbors
  
  int k =0;
  while( k<boardRowSize*boardColSize){
    board[k]= newBoard[k];
    k++;
  }
  //copy the temporary board onto the original board array

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  for (int i=0; i<boardRowSize; i++){
    for (int j=0; j<boardColSize; j++){
      int index = calPos(i,j,boardColSize);
      int liveNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize,i,j);
      if (liveNeighbors==2){
	continue;
      }
      else if (board[index]==1 && liveNeighbors==3){
	continue;
      }
      else if (board[index]==0 && (liveNeighbors<2 ||liveNeighbors>3) ){
	continue;
      }
      else{
	return 0;
      }
    }
  }//deals with the three possibilities that the cell won't change,and else it would return 0 
  return 1;

}

//function to calculate the index of position within the 1-D array with given row and column number
 int calPos(int row, int col, int boardColSize){
   
   return col + row * boardColSize;
 }
				
				
			

