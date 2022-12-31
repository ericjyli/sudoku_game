#ifndef _Generator_h_
#define _Generator_h_
#define sudDimension 9
#define numOfBlocks 81
#include <stdbool.h>

//void generator(int generatedGrid[9][9]);
/*
* This function initializes the array of available numbers for each block, the numbers range from 1 to 9.
* Return Type: void
* Parameter: the array which stores the available digits for each single block
*/
void initialAvailable(int availArray[numOfBlocks][sudDimension]);

/*
* Given the blank Sudoku grid, the linear fill function will fill in every number into the block 
* and ensures the filled numbers are legal so that the puzzle is solvable.
* Return Type: void
* Parameter: the generated grid
*/
void linearFill(int grid[sudDimension][sudDimension]);
/*
* Determine if there is still an available number in the list
* Return type: boolean
* Parameter: the index of the block, the array which stores the available numbers
*/
bool outOfNumber(int indexAvail, int availArr[numOfBlocks][sudDimension]);
/*
* Reset the numbers from 1 - 9 to the current block, given the outOfNumber boolean being true.
* Return type: void
* Parameter: the array which stores the available numbers
*/
void replenishSquareNum(int index, int arrayAvail[numOfBlocks][sudDimension]);
/* 
* Remove the “count” number of digits from the generated solvable grid in a random manner.
* Return type: void
* Parameter: the the generated grid
*/
void removeKDigits(int generateGrid[sudDimension][sudDimension]);

/*
Takes the user's input and checks if the move they are making is legal move. Takes the user indicated digit
column, and row and returns a boolean if it is legal or not.
This function may call helper functions that checks legality in each scenario.
*/
bool checkMoveLegal(int grid[sudDimension][sudDimension], int userDigit, int userCol, int userRow);
bool repeatinSubGrid(int grid[sudDimension][sudDimension], int userDigit, int userRow, int userCol);
bool repeatinRow(int grid[sudDimension][sudDimension], int userDigit, int userRow);
bool repeatinColumn(int grid[sudDimension][sudDimension], int userDigit, int userCol);
#endif
