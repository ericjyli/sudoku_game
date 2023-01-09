#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_

#include "generator.hpp"
#include "stdlib.h"
#include "string"
#include "fstream"

class GameGrid {
    private: 
        int gameGrid[9][9];

    public:
        GameGrid(GeneratedGrid *gGrid);
        //~GameGrid();

        void clayColour();
        void resetColour();
        void printGrid(GeneratedGrid *gGrid);

        bool gameNotDone();
        void playing(GeneratedGrid *gGrid);
        bool notWantToContinue();

        void gameRecord(GeneratedGrid *gGrid);
        void clearRecord();
};


#endif
