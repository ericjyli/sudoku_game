#include <stdio.h>
#include "Generator.h"
#include "playMode.h"
#include "gameFiles.h"

int main(void){
    bool end = false;   bool complete;  bool first = false;
//    FILE *gameRecords = NULL;
   
    while (!end){
        int generatedGrid[9][9];
        int grid[9][9];
        linearFill(generatedGrid);
        removeKDigits(generatedGrid);
        complete = false;
        fileSave(generatedGrid,complete,first);
        playing(generatedGrid,grid);
        complete = true;
        fileSave(grid,complete,first);
        first = true;   //eliminate bool first
        end = notWantToContinue();
    }
    printf("\nGame ends.\n");
    return 0;
}

