#include "game_mode.hpp"

/*
class GameGrid {
    private: 
        int gameGrid[9][9];

    public:
        GameGrid();
        ~GameGrid();

        void clayColour();
        void resetColour();
        void printGrid();

        bool gameNotDone();
        void playing();
        bool notWantToContinue();

};
*/


GameGrid::GameGrid(GeneratedGrid *gGrid){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            gameGrid[i][j] = gGrid -> generatedGrid[i][j];
        }
    }
}

void GameGrid::clayColour(){
    printf("\033[0;36m");   
}

void GameGrid::resetColour(){
    printf("\033[0m");
}

void GameGrid::printGrid(GeneratedGrid *gGrid){
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
                if (gameGrid[i-1][j-1] != 0){

                    //different color for input numbers (where the initial board has 0)
                    if (gGrid -> generatedGrid[i-1][j-1] == 0){  
                        clayColour();
                        printf("%3d ",gameGrid[i-1][j-1]);
                        resetColour();
                    }
                    else{
                        printf("%3d ",gameGrid[i-1][j-1]);
                    }
                }
                
                else if (gameGrid[i-1][j-1] == 0){
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

bool GameGrid::gameNotDone(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (gameGrid[i][j] == 0){
                return true;
            }
        }
    }

    return false;
}

void GameGrid::playing(GeneratedGrid *gGrid){
    std::cout << "If you want to restart this game, enter 10." << std::endl;
    std::cout << "Exiting the game without finishing it may lead to the loss of data." << std::endl;
    bool notDone = true;

    int userNum;
    std::string aString;
    char userRow;   char userCol;
    int row;    int col;
    bool move;

    while (notDone){
        std::cout << "Enter the number you want to fill in: ";
        std::cin >> userNum ;

        if (std::cin.fail() || std::cin.eof() || userNum < 0 || userNum > 9 ){
            std::cout << "Invalid input!" << std::endl;
            std::cout << "Please enter a number from 1 to 9 (inclusive), or 10 to restart the game" << std::endl;
            std::cin.ignore(10000,'\n');
            std::cin.clear();
            continue;  
        }

        //more error checking should be accomplished by using stringstream

        // std::cin >> aString;
        // if (!std::cin.fail()) {
        //     std::cout << "Too many inputs!" << std::endl;
        //     std::cout << "Please ONLY enter a number from 1 to 9 (or 10 to restart the game, 0 to clear the number entered)" << std::endl; 
        //     std::cin.ignore(10000,'\n');
        //     std::cin.clear();
        //     continue;  
        // }

        if (userNum == 10){
            for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++){
                    gameGrid[i][j] = gGrid -> generatedGrid[i][j];
                }
            }
            printGrid(gGrid);
            continue;
        }

        if (userNum >= 0 && userNum <= 9){
            
            std::cout << "Enter the location you want to fill " << userNum << " in: (row col): ";
            std::cin >> userRow >> userCol;
            
            // std::cin >> aString;
            // if (!std::cin.fail()){
            //     std::cout << "Too many arguments! Please only enter two letters indicating the row and the col!" << std::endl;
            //     std::cin.clear();
            //     std::cin.ignore(10000,'\n');
            //     continue;
            // }

            if (userRow < 'A' || userRow > 'I' || userCol < 'A' || userCol > 'I'){
                std::cout << "Invalid location! Please make sure the row and col are capital letters in the range of 'A' to 'I' (inclusive) " << std::endl;
                continue;
            }

            row = userRow - 'A';
            col = userCol - 'A';

            //Enter 0 to remove the digit filled
            if (userNum == 0){       
                if (gGrid -> generatedGrid[row][col] == 0){
                    gameGrid[row][col] = 0;
                    printGrid(gGrid);
                    continue;
                }
                else {
                    std::cout << "You cannot remove the number there since it was filled by the game generator" << std::endl;
                    continue;
                }
            }

            move = gGrid -> checkMoveLegal (userNum,row,col);

            if (move == false){
                std::cout << "The move is illegal." << std::endl;
                std::cout << "Please refer to the rules of sudoku to fill in a valid number" << std::endl;
                continue;
            }

            if (gGrid -> generatedGrid[row][col] != 0){
                move = false;
                std::cout << "You cannot fill in a number there since it was already filled by the game generator" << std::endl;
                continue;
            }
            else if (move == true){
                gameGrid[row][col] = userNum;
                printGrid(gGrid);
                notDone = gameNotDone ();
                if (!notDone){
                    std::cout << "You win!\n\n";
                    break;
                }
            }
        }



    }



}

bool GameGrid::notWantToContinue(){
    char next;
    std::cout << "Do you want to continue to the next game?" << std::endl;
    std::cout << "If you want to clear the past game data, put 'c'. (y/n/c): " << std::endl;
    std::cin >> next;
    bool valid = false;
    while (!valid){
        if (next == 'y' || next == 'Y'){
            return false;
        }

        else if (next == 'n' || next == 'N'){
            return true;
        }

        //when the user wants to clear the data, restart the record and terminate the game
        // else if (next == 'c' || next == 'C'){

        //     FILE *gameRecords = fopen ("gameRecords.txt","w");
        //     fclose(gameRecords);
    
        //     FILE *gameNum = fopen ("gameNum.txt","w");
        //     fclose(gameNum);
            
        //     return true;
        // }

        else {
            std::cout << "Invalid input!" << std::endl;
            continue;
        }
    }
    return 0;  
}
