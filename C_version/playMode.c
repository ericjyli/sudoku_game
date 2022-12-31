#include "playMode.h"
#include "Generator.h"
#include "gameFiles.h"
#include <stdio.h>
#include <stdlib.h>


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

//color adjustment
void clay();
void reset();

bool wantToContinue();

#endif

void initGrid(int grid[9][9]);

//color adjustment
void clay(){
    printf("\033[0;36m");
}
void reset(){
    printf("\033[0m");
}


/* This function takes in the user’s selected row and column to check whether the position has an element.
* Return type: boolean
* Parameter: the integer which represents the user's choice on row and column
*/
bool isElementNotGenerated(int generatedGrid[sudDimension][sudDimension],int userCol, int userRow){

    if (generatedGrid[userCol][userRow] == 0){
        return true;
    }

    else {
        return false;
    }
}

/*Checks if all the spaces in the grid are taken up and returns to user if it is*/
bool gameNotDone(int grid[sudDimension][sudDimension]){

    for (int i = 0; i < sudDimension; i++){
        for (int j = 0; j < sudDimension; j++){
            if (grid[i][j] == 0){
                return true;
            }
        }
    }

    return false;
}


void printSudokuGrid(int grid[sudDimension][sudDimension],int generatedGrid[sudDimension][sudDimension]){
    int k = 0;
    char c = 'A'; char d = 'A';
    
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            if (j == 0 && i == 0){
                printf("   ");
                continue;
            }
            else if (i == 0 && j != 0){
                printf("%3c ",c);
                c++;
                k++;
                if (k != 0 && k % 3 == 0){
                    printf(" ");
                }
                if (c == 'J'){
                    printf ("\n\n");
                
                }
                continue;
            }

            else if (j == 0 && i != 0) {
                printf ("%3c",d);
                d++;
                continue;
            }
    
            //print the numbers in the 9*9 board
            else if (i != 0 && j != 0){
                if (grid[i-1][j-1] != 0){

                    //different color for input numbers (where the initial board has 0)
                    if (generatedGrid[i-1][j-1] == 0){  
                        clay();
                        printf("%3d ",grid[i-1][j-1]);
                        reset();
                    }
                    else{
                        printf("%3d ",grid[i-1][j-1]);
                    }
                }
                
                else if (grid[i-1][j-1] == 0){
                    printf("    ");
                }

                if ((j-1) % 3 == 2){
                    printf ("|");
                }
            
                //after 3 rows are finished
                if ((i-1) % 3 == 2 && j == 9){
                    printf("\n");
                    printf ("    --------------------------------------\n");
            
                }
                else if (j == 9){
                    printf ("\n\n");
                }
            }
        }
    }
    
}

void restartRecord (){

    FILE *gameRecords = fopen ("gameRecords.txt","w");
    fclose(gameRecords);
    
    FILE *gameNum = fopen ("gameNum.txt","w");
    fclose(gameNum);
}

void playing(int generatedGrid[9][9], int grid[9][9]){

    initGrid(grid);
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            grid[i][j] = generatedGrid [i][j];
        }
    }

    printSudokuGrid(grid,generatedGrid);
    printf("If you want to restart this game, fill in 10.\n");
    printf("Exiting the game without finishing it may lead to the loss of data.\n");

    bool goOn = gameNotDone (grid);
    int userNum;
    char userRow;   char userCol;
    int row;    int col;
    bool move;

    while (goOn){
        //prompt an input for number, userRow, userCol
        printf("Enter the number you want to fill in: ");
        scanf ("%d",&userNum);

        //Enter 10 to restart the game (reset to the initial generated grid)
        if (userNum == 10){
            for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++){
                    grid[i][j] = generatedGrid[i][j];
                }
            }
            printSudokuGrid(grid,generatedGrid);
            continue;
        }



        if (userNum < 0 || userNum > 9){
            
            printf ("Invalid input.\n");
            continue;
        }
        if (userNum >= 0 && userNum <= 9){
            
            printf("Enter the location you want to fill %d in: (row col): ",userNum);
            scanf(" %c %c",&userRow,&userCol);
            row = userRow - 'A';
            col = userCol - 'A';

            //Enter 0 to remove the digit filled
            if (userNum == 0){       
                if (generatedGrid[row][col] == 0){
                    grid[row][col] = 0;
                    printSudokuGrid(grid,generatedGrid);
                    continue;
                }
            }

            if (row > 8 || col > 8 || row < 0 || col < 0){
                printf("The move is illegal.\n");
                continue;  
            }

            move = checkMoveLegal (grid,userNum,col,row);
            if (generatedGrid[row][col] != 0){
                move = false;
            }

            if (move == false){
                printf("The move is illegal.\n");
                continue;
            }
            else if (move == true){
                grid[row][col] = userNum;
                printSudokuGrid(grid,generatedGrid);
                goOn = gameNotDone (grid);
                if (goOn == false){
                    printf("You win!\n\n");
                    break;
                }
            }
        }
        
    }

}

bool notWantToContinue(){
    char next;
    printf("Do you want to continue to the next game?\n");
    printf("If you want to clear the past game data, put 'c'. (y/n/c): ");
    scanf(" %c",&next);
    bool valid = false;
    while (!valid){
        if (next == 'y' || next == 'Y'){
            return false;
        }

        else if (next == 'n' || next == 'N'){
            return true;
        }

        //when the user wants to clear the data, restart the record and terminate the game
        else if (next == 'c' || next == 'C'){

            FILE *gameRecords = fopen ("gameRecords.txt","w");
            fclose(gameRecords);
    
            FILE *gameNum = fopen ("gameNum.txt","w");
            fclose(gameNum);
            
            return true;
        }

        else {
            printf("Invalid input!\n");
            continue;
        }
    }
    return 0;
}
