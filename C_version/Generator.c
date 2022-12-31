#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Generator.h"

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



void initGrid (int board[9][9]);
void printBoard (int board[9][9]);



void initGrid(int grid[9][9]){
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            grid[i][j] = 0;
        }
    }
}

void printGrid(int grid[sudDimension][sudDimension]){
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            printf("%3d ",grid[i][j]);
            if (j % 3 == 2){
                printf ("|");
            }
        }
        if (i % 3 == 2){
            printf("\n");
            printf ("  -------------------------------------\n");
        }
        else{
            printf ("\n\n");
        }
    }
}

//void generator(int generatedGrid[9][9]){}

void initialAvailable(int availArray[numOfBlocks][sudDimension]){
/*
* This function initializes the array of available numbers for each block, the numbers range from 1 to 9.
* Return Type: void
* Parameter: the array which stores the available digits for each single block
*/
    for (int i = 0; i < numOfBlocks; i++){
        for (int j = 0; j < sudDimension; j++){
            availArray[i][j] = j+1;
        }
    }
}

void linearFill(int grid[sudDimension][sudDimension]){
/*
* Given the blank Sudoku grid, the linear fill function will fill in every number into the block 
* and ensures the filled numbers are legal so that the puzzle is solvable.
* Return Type: void
* Parameter: the generated grid
*/
   
    initGrid (grid);
    int availableNum[numOfBlocks][sudDimension];
    initialAvailable (availableNum);
    int numIndex;
    int colIndex;
    int rowIndex;

    srand (time(NULL));
    int currentPosition = 0;

    //Conversion:
    //rowIndex = currentPosition / 9;
    //colIndex = currentPosition % 9;

    while (currentPosition < 81){
        if (outOfNumber (currentPosition,availableNum) && currentPosition > 0){
            replenishSquareNum(currentPosition, availableNum);
            grid[rowIndex][colIndex] = 0;
            currentPosition--;
        }

        do {
            numIndex = rand() % 9;
        }  while (availableNum[currentPosition][numIndex] == 0);

        rowIndex = currentPosition / 9;
        colIndex = currentPosition % 9;

        if (checkMoveLegal(grid,availableNum[currentPosition][numIndex],colIndex,rowIndex)){
            grid[rowIndex][colIndex] = availableNum[currentPosition][numIndex];
        }
        else {
            availableNum[currentPosition][numIndex] = 0;
            continue;
        }
        currentPosition++;

    }

}

bool outOfNumber(int indexAvail, int availArr[numOfBlocks][sudDimension]){
/*
* Determine if there is still an available number in the list
* Return type: boolean
* Parameter: the index of the block, the array which stores the available numbers
*/
    int i = 0;
    while (i < sudDimension){
        if (availArr[indexAvail][i] != 0){
            return false;
        }
        i++;
    }

    return true;
}

void replenishSquareNum(int index, int arrayAvail[numOfBlocks][sudDimension]){
/*
* Reset the numbers from 1 - 9 to the current block, given the outOfNumber boolean being true.
* Return type: void
* Parameter: the array which stores the available numbers
*/
    for (int i=0; i< sudDimension; i++){
        arrayAvail[index][i] = i+1;
    }
}

void removeKDigits(int generateGrid[sudDimension][sudDimension]){

/* 
* Remove the “count” number of digits from the generated solvable grid in a random manner.
* Return type: void
* Parameter: the the generated grid
*/
    srand(time(NULL));
    bool valid = false;
    int K,k;
    while (!valid){
        printf("Please enter a number to choose the difficulty level (1 (easy), 2 (medium), 3 (hard): ");
        scanf(" %d",&k);
        
        if (k == 1) {
            K = 1;
            valid = true;
        }
        else if (k == 2) {
            K = 40;
            valid = true;
        }
        else if (k == 3) {
            K = 50;
            valid = true;
        }
        else {
            printf("Invalid difficulty selected.\n");
            k = 0;
            continue;
        }
    }
    int rowIndex;
    int colIndex;
    int random;
    int i = 0;
    while (i < K){
        random = rand() % 81;
        rowIndex = random / 9;
        colIndex = random % 9;
        if (generateGrid[rowIndex][colIndex] != 0){
            generateGrid[rowIndex][colIndex] = 0;

        //if (generateGrid[rowIndex][colIndex] != NULL){
        //    (generateGrid[rowIndex][colIndex] = NULL);
            i++;
        }
    }

}


bool checkMoveLegal(int grid[sudDimension][sudDimension], int userDigit, int userCol, int userRow){
/*
Takes the user's input and checks if the move they are making is legal move. Takes the user indicated digit
column, and row and returns a boolean if it is legal or not.
This function may call helper functions that checks legality in each scenario.
*/
    if (!repeatinSubGrid(grid,userDigit,userRow, userCol)
        &&!repeatinRow(grid,userDigit,userRow)
        &&!repeatinColumn(grid,userDigit,userCol)){
        return true;
    }
    else{
        return false;
    }
}
bool repeatinSubGrid(int grid[9][9], int userDigit, int userRow, int userCol){
    int startRow = userRow - userRow % 3, startCol = userCol - userCol % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == userDigit)
                return true;
    return false;
}
bool repeatinRow(int grid[sudDimension][sudDimension], int userDigit, int userRow){
    for (int i = 0; i<=8; i++){
        if (grid[userRow][i] == userDigit){
            return true;
        }
    }
    return false;
}
bool repeatinColumn(int grid[sudDimension][sudDimension], int userDigit, int userCol){

    for (int i = 0; i <= 8; i++){
        if (grid[i][userCol] == userDigit){
            return true;
        }
    }
    
    return false;
}




