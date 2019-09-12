// last modified : 8/3/2019
// Restructure the code to implement Cancel_Invalidate_Index line 177
#include <vector>
#include <iostream>
#include <utility>
#define underline "\033[4m"
#define underlineoff "\033[0m"

using namespace std;

class Possible{
    public:
        friend class Sudoku;
        Possible();
        void Initialize_possible(int _num, const vector<vector<pair<int, bool>>>& current);
    private:
        void Invalidate_index(int x, int y);
        void Cancel_Invalidate_index(int x, int y);
        bool check_possible(int x, int y) const;
        void display(); // for debug use
    private:
        vector<vector<bool>> possible_place;
        int num;
};

class Sudoku{
    public:
        friend class Possible;
        Sudoku();
        void solve_puzzle(int x, int y);
        void display_puzzle();
        void display_terminal();
    private:
        vector<vector<pair<int, bool>>> current;
        vector<Possible> possible;
        bool is_solved;
};

Sudoku::Sudoku(): is_solved(false){
    // Form the size of Sudoku
    current.resize(9);
    possible.resize(9);
    for(unsigned i=0; i<9; ++i){
        current[i].resize(9);
    }

    // input puzzles 
    char input;
    for(unsigned i=0; i<9; ++i){
        for(unsigned j=0; j<9; ++j){
            cin >> input;
            current[i][j].first = static_cast<int>(input-'0'); 
            current[i][j].second = (current[i][j].first != 0) ? true : false;
        }
    }

    // Initialize possible
    for(unsigned i=0; i<9; ++i){
        possible[i].Initialize_possible(i+1, current);
    }
}

void Sudoku::solve_puzzle(int x, int y){
    // backtrack: base case
    if(x == 8 && y == 8){
        return;
    }

    // if this grid is what is given then move on
    if(current[x][y].second){
        if(y == 8){
            solve_puzzle(x+1, 0);
            return;
        }
        else{
            solve_puzzle(x, y+1);
            return;
        }
    }

    // iterate though each possible numver for this grid
    for(unsigned i=0; i<9; ++i){
        if(possible[i].check_possible(x, y)){
            current[x][y].first = i;
            possible[i].Invalidate_index(x, y);
            if(y == 8){
                solve_puzzle(x+1, 0);
                return;
            }
            else{
                solve_puzzle(x, y+1);
                return;
            }
            current[x][y].first = 0;

        }
    }


}

void Sudoku::display_puzzle(){
    cout << underline << " ";
    for(unsigned i=0; i<9; ++i){
        cout <<"  ";
    }
    cout << "\n";
    for(unsigned i=0; i<9; ++i){
        cout << "|";
        for(unsigned j=0; j<9; ++j){
            cout << current[i][j].first << "|";
        }
        cout << "\n";
    }
    cout << underlineoff << endl;
}

void Sudoku::display_terminal(){
    for(unsigned i=0; i<current.size(); ++i){
        for(int j=0; j<9; ++j){
            cout << current[i][j].first;
        }
    }
    cout << endl;
}

////////////////////////////////////////////////
/////// Possible function implementation ///////
////////////////////////////////////////////////

Possible::Possible(){
    possible_place.resize(9);
    for(unsigned i=0; i<possible_place.size(); ++i){
        possible_place[i].resize(9);
    }

    // initialize everywhere is possible
    for(unsigned i=0; i<9; ++i){
        for(unsigned j=0; j<9; ++j){
            possible_place[i][j] = true;
        }
    }
}

void Possible::Initialize_possible(int _num, const vector<vector<pair<int, bool>>>& current){
    num = _num;

    for(unsigned i=0; i<9; ++i){
        for(unsigned j=0; j<9; ++j){
            if(current[i][j].first == num){
                Invalidate_index(i, j);
            }
        }
    }

}

void Possible::Invalidate_index(int x, int y){
    // Invalidate based from x and y
    for(int i=0; i<9; ++i){
        possible_place[i][y] = false;
        possible_place[x][i] = false;
    }

    // Invalidate based from grid
    x /= 3;
    y /= 3;
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            possible_place[3*x+i][3*y+j] = false;
        }
    }
}

void Possible::Cancel_Invalidate_index(int x, int y){
    possible_place[x][y] = true;
    /*
        don't know how to cancel_invalidate_index
    */
}

bool Possible::check_possible(int x, int y) const{
    return possible_place[x][y];
}

void Possible::display(){
    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j){
            cout << possible_place[i][j];
        }
        cout << endl;
    }
} // for debug use