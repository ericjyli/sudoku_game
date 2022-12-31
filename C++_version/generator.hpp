#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "cstdlib"
#include "iostream"

class GeneratedGrid {
    private:
        int availArr[81][9];    //to generare a solvable 9*9 grid

    protected:
        int generatedGrid[9][9];
   
    public:
        GeneratedGrid();
        //~GeneratedGrid();
        int getNum (int row, int col);
        void setNum (int row, int col, int num);    //it should be guaranteed that the number set is valid (both location and the number)
        
        void printGrid();
        
        bool spaceAvailable (int row, int col);

        //void initialAvailable();
        //Given the blank Sudoku grid, the linear fill function will fill in every number into the block 
        //and ensures the filled numbers are legal so that the puzzle is solvable.

        void linearFill();
        
        bool outOfNumber(int indexAvail);
        //Determine if there is still an available number in the list
        
        void replenishSquareNum(int index);
        //Remove the “count” number of digits from the generated solvable grid in a random manner.
        
        void removeKDigits();

        bool checkMoveLegal(int userDigit, int userRow, int userCol);
        bool repeatInSubGrid (int userDigit, int userRow, int userCol);
        bool repeatInRow (int userDigit, int userRow);
        bool repeatInCol (int userDigit, int userCol);

        friend class GameGrid;
};


#endif
