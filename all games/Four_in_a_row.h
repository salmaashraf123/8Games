#ifndef FOUR_IN_A_ROW
#define FOUR_IN_A_ROW

#include <vector>
#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

class Four_in_a_row_board : public Board<char> {
protected:
    vector<vector<char>> board;

public:
    Four_in_a_row_board() {
        board = vector<vector<char>>(6, vector<char>(7, '_'));
    }

    char get_cell(int x, int y) {
        if (x >= 0 && x < board.size() && y >= 0 && y < board[x].size()) {
            return board[x][y];
        }
        return ' ';
    }

    void display_board() override {
        cout << "|";
        for (int i = 0; i < 7; i++) {
            cout << i + 1 << "|";
        }
        cout << "==> columns\n";
        cout << "===============\n";
        for (const auto& row : board) {
            cout << "|";
            for (char cell : row) {
                cout << cell << "|";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool update_board(int x, int y, char symbol) override {
        if (y >= 0 && y < board[0].size()) {
            for (int i = board.size() - 1; i >= 0; --i) {
                if (board[i][y] == '_') {
                    board[i][y] = symbol;
                    return true;
                }
            }
        }
        return false;
    }

    bool check_v(int i, int j, char symbol) {
        int counter = 0;
        for (int k = i; k < board.size(); ++k) {
            if (board[k][j] == symbol) counter++;
            else break;
        }
        return counter >= 4;
    }

    bool check_h(int i, int j, char symbol) {
        int counter = 0;
        for (int k = j; k < board[0].size(); ++k) {
            if (board[i][k] == symbol) counter++;
            else break;
        }
        return counter >= 4;
    }

    bool check_d(int i, int j, char symbol) {
        int counter1 = 0, counter2 = 0;

        for (int x = i, y = j; x < board.size() && y < board[0].size(); ++x, ++y) {
            if (board[x][y] == symbol) counter1++;
            else break;
        }

        for (int x = i, y = j; x < board.size() && y >= 0; ++x, --y) {
            if (board[x][y] == symbol) counter2++;
            else break;
        }

        return counter1 >= 4 || counter2 >= 4;
    }

    bool is_win() override {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] != '_') {
                    if (check_v(i, j, board[i][j]) || check_h(i, j, board[i][j]) || check_d(i, j, board[i][j])) {
                        return true;
                    }
                }
            }
        }
        return false;
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
        return is_draw() || is_win();
    }
};

class Four_in_a_row_player : public Player<char> {
public:
    Four_in_a_row_player(const string& name, char symbol = 'X') : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << " (" << symbol << "), enter your move (column) as 1 base index: ";
        cin >> y;
        x = 0;
        y--;  // Convert to zero-based index
    }
};

class Four_in_a_row_random_player : public RandomPlayer<char> {
private:
    Four_in_a_row_board& Board;

public:
    Four_in_a_row_random_player(const string& name, char symbol, Four_in_a_row_board& board)
        : RandomPlayer<char>(symbol), Board(board) {}

    void getmove(int& x, int& y) override {
        do {
            y = rand() % 7;  // Random column
            for (x = 5; x >= 0; --x) {
                if (Board.get_cell(x, y) == '_') break;
            }
        } while (x < 0);
    }
};

#endif  // FOUR_IN_A_ROW
