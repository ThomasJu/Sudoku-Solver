#include <iostream>
#include <vector>
#include <string>
#include "backtrackclass.h"
#define underline "\033[4m"

using namespace std;

int main(int argc, char* argv[]){
  
    ios::sync_with_stdio(false);

    Sudoku sudoku;      
    sudoku.solve_puzzle(0, 0);

    // different type of display method 
    if(argc == 2 && string(argv[1]) == "-h"){
        sudoku.display_puzzle();
    }
    else if (argc == 2 && string(argv[1]) == "-t"){
        sudoku.display_terminal();
    }
    else{
        cerr << "Invalid Command line argument" << endl;
        exit(1);
    }
    return 0;
}