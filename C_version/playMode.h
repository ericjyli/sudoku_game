#ifndef _playMode_h_
#define _playMode_h_
#include <stdbool.h>
#define sudDimension 9
#define numOfBlocks 81

/*Checks if all the spaces in the grid are taken up and returns to user if it is*/
bool gameNotDone(int grid[sudDimension][sudDimension]);


/* This function takes in the user’s selected row and column to check whether the position has an element.
* Return type: boolean
* Parameter: the integer which represents the user's choice on row and column
*/
bool isElementNotGenerated(int generatedGrid[sudDimension][sudDimension],int userCol, int userRow);

/*
This function should print the grid to the console, takes the grid as an input
*/
void printSudokuGrid(int grid[sudDimension][sudDimension],int generatedGrid[sudDimension][sudDimension]);
void restartRecord ();
void playing(int generatedGrid[9][9],int grid[9][9]);
bool notWantToContinue();


//colorings
void clay();
void reset();

#endif
