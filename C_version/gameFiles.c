#include <stdio.h>
#include <stdbool.h>
#include "gameFiles.h"

#ifndef _gameFiles_h_
#define _gameFiles_h_

void fileSave(int generatedGrid[9][9],bool complete, bool first);
#endif

void fileSave(int generatedGrid[9][9],bool complete, bool first){
    FILE *gameRecords = NULL;
    FILE *gameNum;
    int num = 0;
    int size;
    
    gameNum = fopen ("gameNum.txt","a+");
    gameRecords = fopen ("gameRecords.txt","a+");

    //when creating a new file is needed
    if (NULL != gameNum) {
        fseek (gameNum, 0, SEEK_END);
        size = ftell(gameNum);

        if (size == 0) {
            //file gameNum is empty
            num = 1;
            fprintf(gameNum,"%d",num);
            fclose(gameNum);
        }
        
        //**************this else if may not be necessary***********
        else if (num == 1 && first == false){
            fclose(gameNum);
            gameNum = fopen("gameNum.txt","w");
            fprintf(gameNum,"%d",num);
            fclose(gameNum);
        }
        //***************************************************************

        else {
            //file is not empty
            fclose(gameNum);
            gameNum = fopen("gameNum.txt","r");
            fscanf(gameNum," %d",&num);
            if (!complete){
                num++;
            }
            else if (complete){

            }
            fclose(gameNum);
            gameNum = fopen("gameNum.txt","w+");
            fprintf(gameNum,"%d",num);
            fclose(gameNum);
        }

    }

    //************Can be simpler
    
    //print the games
    fprintf(gameRecords,"Game %d: \n",num);
    
    if (complete){
        fprintf(gameRecords,"The solution:\n");
    }
    else if (!complete){
        fprintf(gameRecords,"The original game:\n");
    }

    
    for (int i=0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            fprintf(gameRecords,"%4d",generatedGrid[i][j]);
        }
        fprintf(gameRecords,"\n\n");
    }

    fclose(gameRecords);

    return;
}


