#ifndef _5X5X_O_H
#define _5X5X_O_H
#include "BoardGame_Classes.h"
template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    //virtual functions
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    //virtual
    void getmove(int& x, int& y) ;
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    //virtual
    void getmove(int &x, int &y) ;
};

//=============IMPLEMENTATION===========
#include <iostream>
#include <iomanip>
#include <cctype> 
#include <algorithm>

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    //initialize
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
// Update the board
template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // check that this move is valid 
    if ((x >= 0 && x < this->rows && y >= 0 && y < this->columns ) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

// Display the board
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------";
    }
    cout << endl;
}
int fl = 0;
template <typename T>
bool X_O_Board<T>::is_win() {
  int check_1 = 0, check_2 = 0;
    //check horzintal
    for (int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns-2; j++)
        {
            if ((this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0)){
                if(this->board[i][j] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
        }
    }
    //check vertical
    for (int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->columns; j++)
        {
            if ((this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] && this->board[i][j] != 0)){
                if(this->board[i][j] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
        }
    }
    // Check diagonals
    for (int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->columns-2; j++)
        {
            if(this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != 0)
            {
                if(this->board[i][j] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
            if(this->board[i][j+2] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j] && this->board[i][j+2] != 0)
            {
                if(this->board[i][j+2] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
        }
    }
    if(check_1 > check_2 && this->n_moves == 24)
    {
        cout << "player 1 wins" << endl;
        fl = 1;
    }
    else if(check_1 < check_2 && this->n_moves == 24)
    {
        cout << "player 2 wins" << endl;
        fl = 1;
    }
    return false;
   
}
template <typename T>
bool X_O_Board<T>::is_draw() {
    int check_1 = 0, check_2 = 0;
    //check horzintal
    for (int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns-2; j++)
        {
            if ((this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0)){
                if(this->board[i][j] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
        }
    }
    //check vertical
    for (int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->columns; j++)
        {
            if ((this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] && this->board[i][j] != 0)){
                if(this->board[i][j] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
        }
    }
    // Check diagonals
    for (int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->columns-2; j++)
        {
            if(this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != 0)
            {
                if(this->board[i][j] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
            if(this->board[i][j+2] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j] && this->board[i][j+2] != 0)
            {
                if(this->board[i][j+2] == 'X')
                {
                    check_1++;
                }
                else{
                    check_2++;
                }
            }
        }
    }

    return (this->n_moves == 24 && (check_1 == check_2));
}
template <typename T>
bool X_O_Board<T>::game_is_over() {
    return (is_draw() || this->n_moves == 24 || fl == 1);
}
//================================================
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  
    y = rand() % this->dimension;
}
 
#endif //_5X5X_O_H
