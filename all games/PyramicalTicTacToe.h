// File: PyramicalTicTacToe.h
#ifndef PYRAMICALTICTACTOE_H
#define PYRAMICALTICTACTOE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
using namespace std;

// Pyramid Board Class
class PyramidBoard : public Board<char> {
protected:
    vector<vector<char>> board;

public:
    PyramidBoard() {
        board = {
            {' ', ' ', '_', ' ', ' '},
            {' ', '_', '_', '_', ' '},
            {'_', '_', '_', '_', '_'}
        };
    }

    char get_cell(int x, int y) {
        if (x >= 0 && x < board.size() && y >= 0 && y < board[x].size()) {
            return board[x][y];
        }
        return ' ';
    }

    int get_sizeofBoard() {
        return board.size();
    }

    void display_board() override {
        cout << "    ";
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if(board[i][j] != ' '){ cout << "|" << board[i][j]; }
                else if(board[i][j] != ' ' && j > 2){ cout << "|" << board[i][j]; }
            }
            cout << "|\n";
            if(i == 0){ cout << "  "; }
        }
        cout << "\n";
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < board.size() && y >= 0 && y < board[x].size() && board[x][y] == '_') {
            board[x][y] = symbol;
            return true;
        }
        return false;
    }

    bool is_win() override {
        // Diagonals
        if ((board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) ||
            (board[0][2] != '_' && board[0][2] == board[1][3] && board[1][3] == board[2][4])) {
            return true;
        }
        // Rows
        if ((board[1][1] != '_' && board[1][1] == board[1][2] && board[1][2] == board[1][3]) ||
            (board[2][0] != '_' && board[2][0] == board[2][1] && board[2][1] == board[2][2]) ||
            (board[2][1] != '_' && board[2][1] == board[2][2] && board[2][2] == board[2][3]) ||
            (board[2][2] != '_' && board[2][2] == board[2][3] && board[2][3] == board[2][4])) {
            return true;
        }
        // Columns
        if (board[0][2] != '_' && board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
            return true;
        }
        return false;
    }

    bool is_draw() override {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == '_') {
                    return false;
                }
            }
        }
        return !is_win();
    }
    bool game_is_over() override {
        return is_draw() || is_win();
    }
};

// Pyramid Player Class
class PyramidPlayer : public Player<char> {
public:
    PyramidPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << " (" << symbol << "), enter your move (row column) as 1 base index: ";
        cin >> x >> y;
        x--; y--; // Adjust for zero-based indexing
    }
};

// Pyramid Random Player Class
class PyramidRandomPlayer : public RandomPlayer<char> {
private:
    PyramidBoard& Board;

public:
    PyramidRandomPlayer(const string& name, char symbol, PyramidBoard& board)
        : RandomPlayer(symbol), Board(board) {}

    void getmove(int& x, int& y) override {
        srand(time(0));
        do {
            x = rand() % Board.get_sizeofBoard();
            y = rand() % (Board.get_sizeofBoard() + 2); // Random column in the row
        } while (Board.get_cell(x, y) != '_');
    }
};

#endif  // PYRAMICALTICTACTOE_H
