//  Created by Junyu Li on 2022-Dec-30

//  Sudoku game written in C++
//  Updated based on the C version of the game using OOP

//  Two classes (GeneratedGrid, GameGrid) are implemented in this program
//
//  By being declared as a friend class, the GameGrid can access the original GeneratedGrid to see
//  if a move is valid, and print the updated board accordingly.

#include "game_mode.hpp"



int main(){

    bool end = false;

    while (!end) {
        GeneratedGrid* gGrid = new GeneratedGrid;
        gGrid -> linearFill();
        gGrid -> removeKDigits();
        GameGrid *game = new GameGrid(gGrid);
        game -> printGrid(gGrid);
        game -> playing(gGrid);


        delete gGrid;
        delete game;
        break;
    }

    return 0;
}
