#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

using namespace std;

// Word Board Class
class Word_board : public Board<char> {
protected:
    vector<vector<char>> board;
    vector<string> Words;

public:
    Word_board() : board(vector<vector<char>>(3, vector<char>(3, '_'))) {}

    void x(vector<string>& wordss){
        Words = wordss;
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
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == '_') {
            board[x][y] = toupper(symbol);
            return true;
        }
        return false;
    }

    bool check_V(int x, int y) {
        string word = "";
        for (int i = x; i < 3 && board[i][y] != '_'; ++i) {
            word += board[i][y];
        }
        string word2 = word;
        reverse(word2.begin(), word2.end());

        return find(Words.begin(), Words.end(), word) != Words.end() ||
               find(Words.begin(), Words.end(), word2) != Words.end();
    }

    bool check_H(int x, int y) {
        string word = "";
        for (int j = y; j < 3 && board[x][j] != '_'; ++j) {
            word += board[x][j];
        }
        string word2 = word;
        reverse(word2.begin(), word2.end());

        return find(Words.begin(), Words.end(), word) != Words.end() ||
               find(Words.begin(), Words.end(), word2) != Words.end();
    }

    bool check_D(int x, int y) {
        string diag1 = "", diag2 = "";
        for (int i = x, j = y; i < 3 && j < 3 && board[i][j] != '_'; ++i, ++j) {
            diag1 += board[i][j];
        }
        for (int i = x, j = y; i < 3 && j >= 0 && board[i][j] != '_'; ++i, --j) {
            diag2 += board[i][j];
        }
        string diag11 = diag1, diag22 = diag2;
        reverse(diag11.begin(), diag11.end());
        reverse(diag22.begin(), diag22.end());
        return find(Words.begin(), Words.end(), diag1) != Words.end() ||
               find(Words.begin(), Words.end(), diag2) != Words.end() ||
               find(Words.begin(), Words.end(), diag11) != Words.end() ||
               find(Words.begin(), Words.end(), diag22) != Words.end();
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] != '_' && (check_V(i, j) || check_H(i, j) || check_D(i, j))) {
                    return true;
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

// Word Player Class
class Word_player : public Player<char> {
public:
    Word_player(const string& name) : Player<char>(name, ' ') {}

    void getmove(int& x, int& y) override {
        char ch;
        while (true) {
            cout << getname() << ", enter your move (row column letter) as 1 base index: ";
            cin >> x >> y >> ch;
            if (x > 0 && x <= 3 && y > 0 && y <= 3 && isalpha(ch)) {
                --x, --y; // Adjust for zero-based indexing
                setSymbol(toupper(ch));
                return; 
            }
            cout << "Invalid input. Please try again.\n";
        }
    }
    // Add setter for symbol in RandomPlayer class
    void setSymbol(char symbol) {
        this->symbol = symbol;
    }
};

// Random Word Player Class
class Word_random_player : public RandomPlayer<char> {
private:
    Word_board& board;

public:
    Word_random_player(const string& name, Word_board& board)
        : RandomPlayer<char>(' '), board(board) {}

    void getmove(int& x, int& y) override {
        do {
            x = rand() % 3; // Random row (0-2)
            y = rand() % 3; // Random column (0-2)
        } while (board.get_cell(x, y) != '_');
        setSymbol('A' + rand() % 26); // Random letter A-Z
    }

    // Add setter for symbol in RandomPlayer class
    void setSymbol(char symbol) {
        this->symbol = symbol;
    }
};

#endif // WORD_TIC_TAC_TOE_H

