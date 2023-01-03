#include "generator.hpp"

/*
class GeneratedGrid {
    private:
        int generatedGrid[9][9];
        int availArr[81][9];

    public:
        GeneratedGrid();
        //~GeneratedGrid();
        int getNum (int row, int col);
        void setNum (int row, int col, int num);
        
        void printGrid();
        
        bool spaceAvailable (int row, int col);
        //void initialAvailable();
        
        void linearFill();
        bool outOfNumber(int indexAvail, int availArr[81][9]);
        void replenishSquareNum(int index, int arrayAvail[81][9]);
        void removeKDigits();

        bool checkMoveLegal(int userDigit, int userRow, int userCol);
        bool repeatInSubGrid (int userDigit, int userRow, int userCol);
        bool repeatInRow (int userDigit, int userRow, int userCol);
        bool repeartInCol (int userDigit, int userRow, int userCol);


        friend class GameGrid;
};

*/

GeneratedGrid::GeneratedGrid(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            generatedGrid[i][j] = 0;
        }
    }

    for (int i = 0; i < 81; i++){
        for (int j = 0; j < 9; j++){
            availArr[i][j] = j+1;
        }
    }
}

int GeneratedGrid::getNum(int row, int col){
    return generatedGrid[row][col];
}

void GeneratedGrid::setNum (int row, int col, int num){
    generatedGrid[row][col] = num;
    return;
}

void GeneratedGrid::printGrid(){
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (generatedGrid[i][j] == 0){
                printf("    ");
            }
            else {
                printf("%3d ",generatedGrid[i][j]);
            }
            
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

// bool GeneratedGrid::spaceAvailable (int row, int col){
//     if (generatedGrid[row][col] == 0)   return true;
//     else return false;
// }

// void GeneratedGrid::initialAvailable(){
//     for (int i = 0; i < 81; i++){
//         for (int j = 0; j < 9; j++){
//             availArr[i][j] = j+1;
//         }
//     }
// }

void GeneratedGrid::linearFill(){
    int numIndex, rowIndex, colIndex;
    int currentPosition = 0;
    srand((unsigned) time(NULL));

    while (currentPosition < 81){
        if (outOfNumber(currentPosition) && currentPosition > 0){
            replenishSquareNum(currentPosition);
            generatedGrid[rowIndex][colIndex] = 0;
            currentPosition--;
        }
    

        do {
            numIndex = rand() % 9;
        } while (availArr[currentPosition][numIndex] == 0);

        rowIndex = currentPosition / 9;
        colIndex = currentPosition % 9;

        if (checkMoveLegal(availArr[currentPosition][numIndex], rowIndex, colIndex)){
            generatedGrid[rowIndex][colIndex] = availArr[currentPosition][numIndex];
        }
        else {
            availArr[currentPosition][numIndex] = 0;
            continue;
        }
        currentPosition++;
    }
}

bool GeneratedGrid::outOfNumber(int indexAvail){
    int i = 0;
    while (i < 9){
        if (availArr[indexAvail][i] != 0){
            return false;
        }
        i++;
    }

    return true;
}

void GeneratedGrid::replenishSquareNum (int index){
    for (int i = 0; i < 9; i++){
        availArr[index][i] = i+1;
    }
}

void GeneratedGrid::removeKDigits(){
    bool valid = false;
    int K,k;
    while (!valid){
        std::cout << "Please enter a number to choose the difficulty level (1 (easy), 2 (medium), 3 (hard): ";
        std::cin >> k;

        if (std::cin.fail()){
            std::cout << "Invalid input. Please enter 1 or 2 or 3 to choose the difficulty level." << std::endl;
        }
        
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
            std::cout << "Invalid input. Please enter 1 or 2 or 3 to choose the difficulty level." << std::endl;
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
        if (generatedGrid[rowIndex][colIndex] != 0){
            generatedGrid[rowIndex][colIndex] = 0;

        //if (generateGrid[rowIndex][colIndex] != NULL){
        //    (generateGrid[rowIndex][colIndex] = NULL);
            i++;
        }
    }
}

bool GeneratedGrid::checkMoveLegal(int userDigit, int userRow, int userCol){
    if (!repeatInSubGrid(userDigit,userRow, userCol)
        &&!repeatInRow(userDigit,userRow)
        &&!repeatInCol(userDigit,userCol)){
        return true;
    }
    else{
        return false;
    }

}
bool GeneratedGrid::repeatInSubGrid(int userDigit, int userRow, int userCol){
    int startRow = userRow - userRow % 3, startCol = userCol - userCol % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (generatedGrid[i + startRow][j + startCol] == userDigit)
                return true;
    return false;
}
bool GeneratedGrid::repeatInRow(int userDigit, int userRow){
    for (int i = 0; i<=8; i++){
        if (generatedGrid[userRow][i] == userDigit){
            return true;
        }
    }
    return false;
}
bool GeneratedGrid::repeatInCol(int userDigit, int userCol){
    for (int i = 0; i <= 8; i++){
        if (generatedGrid[i][userCol] == userDigit){
            return true;
        }
    }
    
    return false;
}

