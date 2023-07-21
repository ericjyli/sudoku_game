//  Created by Junyu Li on 2022-Dec-30

//  Sudoku game written in C++
//  Updated based on the C version of the game using OOP

//  Two classes (GeneratedGrid, GameGrid) are implemented in this program
//
//  By being declared as a friend class, the GameGrid can access the original GeneratedGrid to see
//  if a move is valid, and print the updated board accordingly.

#include "game_mode.hpp"


int main(){

    bool end;
    

    while (1) {
        GeneratedGrid* gGrid = new GeneratedGrid;
        gGrid -> linearFill();
        gGrid -> removeKDigits();
        GameGrid *game = new GameGrid(gGrid);
        game -> printGrid(gGrid);
        game -> playing(gGrid);

        //save the game record

        game -> gameRecord(gGrid);

        //-----------------------
        delete gGrid;
        delete game;
        
        //ask if want to continue
        end = game -> notWantToContinue();
        if (!end)   continue;
        if (end)    break;
        
    }

    return 0;
}
