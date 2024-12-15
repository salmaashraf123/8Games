#ifndef ULTIMATE_TIC_TAC_TOE
#define ULTIMATE_TIC_TAC_TOE

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class UltimateTicTacToeBoard : public Board<T> {
public:
    UltimateTicTacToeBoard();
    bool update_board(int x, int y, T symbol);  
    bool update_small_board(int board_x, int board_y, T symbol); 
    void display_board();
    bool is_win();  
    bool is_draw(); 
    bool game_is_over(); 
    bool is_small_board_winner(int board_x, int board_y); 

private:
    T board[9][9];  
    T small_board_winners[3][3];  
};


template <typename T>
class UltimateTicTacToePlayer : public Player<T> {
public:
    UltimateTicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y);  
};


template <typename T>
class UltimateTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    UltimateTicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y);  
};

#endif // ULTIMATE_TIC_TAC_TOE


// -------------------------------------- IMPLEMENTATION -------------------------------------- //

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;


template <typename T>
UltimateTicTacToeBoard<T>::UltimateTicTacToeBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;  
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            small_board_winners[i][j] = 0;
        }
    }
}

template <typename T>
bool UltimateTicTacToeBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= 9 || y < 0 || y >= 9 || board[x][y] != 0) {
        return false;
    }
    board[x][y] = symbol;
    return true;
}

template <typename T>
bool UltimateTicTacToeBoard<T>::update_small_board(int board_x, int board_y, T symbol) {
    if (small_board_winners[board_x][board_y] != 0) {
        return false;
    }

    if (is_small_board_winner(board_x, board_y)) {
        small_board_winners[board_x][board_y] = symbol;
        return true;
    }

    return false;
}

template <typename T>
bool UltimateTicTacToeBoard<T>::is_small_board_winner(int board_x, int board_y) {
    int start_row = board_x * 3;
    int start_col = board_y * 3;

    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[start_row + i][start_col] == board[start_row + i][start_col + 1] &&
            board[start_row + i][start_col] == board[start_row + i][start_col + 2] &&
            board[start_row + i][start_col] != 0) {
            return true;
        }

        // Check columns
        if (board[start_row][start_col + i] == board[start_row + 1][start_col + i] &&
            board[start_row][start_col + i] == board[start_row + 2][start_col + i] &&
            board[start_row][start_col + i] != 0) {
            return true;
        }
    }

    // Check diagonals
    if (board[start_row][start_col] == board[start_row + 1][start_col + 1] &&
        board[start_row][start_col] == board[start_row + 2][start_col + 2] &&
        board[start_row][start_col] != 0) {
        return true;
    }
    if (board[start_row + 2][start_col] == board[start_row + 1][start_col + 1] &&
        board[start_row + 2][start_col] == board[start_row][start_col + 2] &&
        board[start_row + 2][start_col] != 0) {
        return true;
    }

    return false;
}

template <typename T>
void UltimateTicTacToeBoard<T>::display_board() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << (board[i][j] ? board[i][j] : ' ') << " ";
            if(j == 2 || j == 5){ cout << "||  "; }
        }
        if(i == 2 || i == 5){ cout << "\n========================  ==========================  ======================="; }
        cout << "\n";
    }
    cout << "========================  ==========================  =======================";
    cout << "\nSmall Board Winners (X or O):\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << setw(3) << (small_board_winners[i][j] ? small_board_winners[i][j] : '_');
            cout << "  | ";
        }
        cout << endl;
    }
}


template <typename T>
bool UltimateTicTacToeBoard<T>::is_win() {
    for (int i = 0; i < 3; i++) {
        if (small_board_winners[i][0] == small_board_winners[i][1] &&
            small_board_winners[i][0] == small_board_winners[i][2] &&
            small_board_winners[i][0] != 0) {
            return true;
        }
        if (small_board_winners[0][i] == small_board_winners[1][i] &&
            small_board_winners[0][i] == small_board_winners[2][i] &&
            small_board_winners[0][i] != 0) {
            return true;
        }
    }

    if (small_board_winners[0][0] == small_board_winners[1][1] &&
        small_board_winners[0][0] == small_board_winners[2][2] &&
        small_board_winners[0][0] != 0) {
        return true;
    }
    if (small_board_winners[0][2] == small_board_winners[1][1] &&
        small_board_winners[0][2] == small_board_winners[2][0] &&
        small_board_winners[0][2] != 0) {
        return true;
    }

    return false;
}

template <typename T>
bool UltimateTicTacToeBoard<T>::is_draw() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return !is_win();
}

template <typename T>
bool UltimateTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
UltimateTicTacToePlayer<T>::UltimateTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void UltimateTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move (row and column for the 9x9 grid): ";
    cin >> x >> y;
}

template <typename T>
UltimateTicTacToeRandomPlayer<T>::UltimateTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void UltimateTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 9;
    y = rand() % 9;
}