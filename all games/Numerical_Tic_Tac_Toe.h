#ifndef NUMERICAL_TIC_TAC_TOE
#define NUMERICAL_TIC_TAC_TOE

#include <iostream>
#include <bits/stdc++.h> //  11_1
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

using namespace std;

char num; // Global variable to store the chosen number
set <char> s;

// Numerical Board Class
class Numerical_board : public Board<char> {
protected:
    vector<vector<char>> board;
public:
    Numerical_board() {
        board = vector<vector<char>>(3, vector<char>(3, '_'));
    }

    char get_cell(int x, int y) {
        if (x >= 0 && x < 3 && y >= 0 && y < 3) {
            return board[x][y];
        }
        return ' ';
    }

    void display_board() override {
        for (int i = 0; i < 3; ++i) {
            cout << "|";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << "|";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool update_board(int x, int y, char symbol) override {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == num) return false; // Number already used
            }
        }
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == '_') {
            board[x][y] = num; // Use global num directly
            return true;
        }
        return false;
    }



    bool check_V(int x, int y) {
        int sum = 0, counter = 0;
        while (x < 3) {
            sum += (board[x][y] - '0');
            counter++;
            x++;
        }
        return (counter == 3 && sum == 15);
    }

    bool check_H(int x, int y) {
        int sum = 0, counter = 0;
        while (y < 3) {
            sum += (board[x][y] - '0');
            counter++;
            y++;
        }
        return (counter == 3 && sum == 15);
    }

    bool check_D() {
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < 3; ++i) {
            sum1 += (board[i][i] - '0');         // Top-left to bottom-right
            sum2 += (board[i][2 - i] - '0');     // Top-right to bottom-left
        }
        return (sum1 == 15 || sum2 == 15);
    }

    bool is_win() override {
        for (int i = 0; i < 3; i++) {
                if (check_V(0, i) || check_H(i, 0)) {
                    return true;
                }
        }
        return check_D();
    }

    bool is_draw() override {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == '_') return false;
            }
        }
        return !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// Numerical Player Class
class Numerical_Player : public Player<char> {
public:
    Numerical_Player(const string& name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        while (true) {
            cout << name << ", enter your move (row column number) as 1 base index: ";
            cin >> x >> y >> num;

            if (x < 1 || x > 3 || y < 1 || y > 3) {
                cout << "Invalid position. Please enter values between 1 and 3.\n";
                continue;
            }
            if (num < '1' || num > '9') {
                cout << "Invalid number. Please enter a number between 1 and 9.\n";
                continue;
            }
            if (symbol == 'o' && (num - '0') % 2 == 0) {
                cout << "Please enter an odd number.\n";
                continue;
            }
            if (symbol == 'e' && (num - '0') % 2 != 0) {
                cout << "Please enter an even number.\n";
                continue;
            }

            x--; y--; // Convert to zero-based index
            return;
        }
    }
};

// Numerical Random Player Class
class Numerical_Random_Player : public RandomPlayer<char> {
private:
    Numerical_board& board;

public:
    Numerical_Random_Player(const string& name, Numerical_board& board)
        : RandomPlayer(' '), board(board) {}

    void getmove(int& x, int& y) override {
    srand(static_cast<unsigned>(time(0))); // Seed the random generator once per program run, ideally outside this function

    // Select a random valid cell
    do {
        x = rand() % 3; // Random row (0-2)
        y = rand() % 3; // Random column (0-2)
    } while (board.get_cell(x, y) != '_');

    // Select a valid number
    if ((num - '0') % 2 == 0) {
        char arr[] = {'1', '3', '5', '7', '9'}; // Odd numbers
        int i;
        do {
        i = rand() % 5; // Random index within [0, 4]
        } while(s.count(arr[i]));
        s.insert(num = arr[i]);
    } else {
        char arr[] = {'2', '4', '6', '8'}; // Even numbers
        int i;
        do {
        i = rand() % 4; // Random index within [0, 3]
        } while(s.count(arr[i]));
        s.insert(num = arr[i]);
    }

    }

};

#endif // NUMERICAL_TIC_TAC_TOE


