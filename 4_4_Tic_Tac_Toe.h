#ifndef FOUR_FOUR_TIC_TAC_TOE
#define FOUR_FOUR_TIC_TAC_TOE

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

using namespace std;

int xx, yy;
const int nx[] = {1, -1, 0, 0};
const int ny[] = {0, 0, 1, -1};

class Four_Four_board : public Board<char> {
protected:
    vector<vector<char>> Player1;
    vector<vector<char>> Player2;
    vector<vector<char>> board;
public:
    Four_Four_board(){
        Player1 = {{'O', 'X', 'O', 'X'},
                   {'_', '_', '_', '_'},
                   {'_', '_', '_', '_'},
                   {'_', '_', '_', '_'}};

        Player2 = {{'_', '_', '_', '_'},
                   {'_', '_', '_', '_'},
                   {'_', '_', '_', '_'},
                   {'X', 'O', 'X', 'O'}};

        board   = {{'O', 'X', 'O', 'X'},
                   {'_', '_', '_', '_'},
                   {'_', '_', '_', '_'},
                   {'X', 'O', 'X', 'O'}};
    }

    void display_board() override {
        for (int i = 0; i < 4; ++i) {
            cout << "|";
            for (int j = 0; j < 4; ++j) {
                cout << board[i][j] << "|";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool update_board(int x, int y, char symbol) override {
        bool ok = false;
        for(int i=0; i<4; i++){
            if(nx[i] + x == xx && ny[i] + y == yy){
                ok = true; break;
            }
        }
        if(!ok){ return false; }

        if(x >= 0 && x < 4 && y >= 0 && y < 4 && xx >= 0 && xx < 4 && yy >= 0 && yy < 4 
        && board[x][y] != '_' && board[xx][yy] == '_') {

            if(symbol == '1' && Player1[x][y] != '_') {
                swap(Player1[x][y], Player1[xx][yy]);
                swap(board[x][y], board[xx][yy]);
                return true;

            } else if(symbol == '2' && Player2[x][y] != '_') {
                swap(Player2[x][y], Player2[xx][yy]);
                swap(board[x][y], board[xx][yy]);
                return true;

            } else {
                return false;
            }

        } else {
            return false;
        } 
    }

    bool check_V(int x, int y, char c) {
        int counter = 0;
        while(x >= 0 && x < 4){
            if(board[x][y] == c){ counter++, x++; }
            else{ break; }
        }
        if(counter == 3){ return true; }
        return false;
    }

    bool check_H(int x, int y, char c) {
        int counter = 0;
        while(y >= 0 && y < 4){
            if(board[x][y] == c){ counter++, y++; }
            else{ break; }
        }
        if(counter >= 3){ return true; }
        return false;
    }

    bool check_D(int x, int y, char c) {
        int counter1 = 0, counter2 = 0, xx = x, yy = y;

        while(xx >= 0 && xx < 4 && yy >= 0 && yy < 4){
            if(board[xx][yy] == c){ counter1++, xx++, yy++; }
            else{ break; }
        }

        while(x >= 0 && x < 4 && y >= 0 && y < 4){
            if(board[x][y] == c){ counter2++, x++, y--; }
            else{ break; }
        }

        if(counter1 >= 3 || counter2 >= 3){ return true; }
        return false;
    }

    bool is_win() override {
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if(board[i][j] != '_'){
                    if(check_V(i, j, board[i][j]) || check_H(i, j, board[i][j]) || check_D(i, j, board[i][j])){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return false;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class Four_Four_Player : public Player<char> {
public:
    Four_Four_Player(const string& name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        while(true) {
            cout << name << ", Please enter the position that you want to move it's symbol to another cell as 1 base index: ";
            cin >> x >> y;

            if (x < 1 || x > 4 || y < 1 || y > 4) {
                cout << "Invalid position. Please enter values between 1 and 4.\n";
                continue;
            }
            x--, y--;
            break;
        }
        while(true) {
            cout << name <<", Please enter the position of the cell that will receive the symbol as 1 base index: ";
            cin >> xx >> yy;
            if (xx < 1 || xx > 4 || yy < 1 || yy > 4) {
                cout << "Invalid position. Please enter values between 1 and 4.\n";
                continue;
            }
            xx--, yy--;
            return;
        }
    }
};

class Four_Four_Random_Player : public RandomPlayer<char>, protected  Four_Four_board{
private:
    Four_Four_board& Board;
public:
    Four_Four_Random_Player(const string& name, char symbol, Four_Four_board& board)
    : RandomPlayer(symbol), Board(board) {}

    void getmove(int& x, int& y) override {
        bool ok = false;
        if("Player" + symbol == "Player1"){
            do {
                x = rand() % 4;
                y = rand() % 4;
            } while(Player1[x][y] == '_');

            do {
                xx = rand() % 4;
                yy = rand() % 4;
                for(int i=0; i<4; i++){
                    if(nx[i] + x == xx && ny[i] + y == yy){
                        ok = true;
                    }
                }
                if(ok && board[xx][yy] == '_'){ break; }
                else{ ok = false; }
            } while(board[xx][yy] != '_' || !ok);

        } else{
            do {
                x = rand() % 4;
                y = rand() % 4;
            } while(Player2[x][y] == '_');

            do {
                xx = rand() % 4;
                yy = rand() % 4;
                for(int i=0; i<4; i++){
                    if(nx[i] + x == xx && ny[i] + y == yy){
                        ok = true;
                    }
                }
                if(ok && board[xx][yy] == '_'){ break; }
                else{ ok = false; }
            } while(board[xx][yy] != '_' || !ok);
        }
    }
};




#endif