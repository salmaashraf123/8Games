#include <bits/stdc++.h>
#include "PyramicalTicTacToe.h"
#include "Four_in_a_row.h"
#include "5x5X_O.h"
#include "Word_Tic_Tac_Toe.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "misere.h"
#include "4_4_Tic_Tac_Toe.h"
#include "Ultimate_Tic_Tac_Toe.h"

using namespace std;

int main() {
    cout << "Welcom to XO games program\n\n";
    while(true) {
        cout << "(1) Run game_1 (Pyramid Game)\n";
        cout << "(2) Run game_2 (Four In a Row Game)\n";
        cout << "(3) Run game_3 (3x3X_O)\n";
        cout << "(4) Run game_4 (Word Tic Tac Toe!)\n";
        cout << "(5) Run game_5 (Numerical Tic Tac Toe)\n";
        cout << "(6) Run game_6 (Misere)\n";
        cout << "(7) Run game_7 (4*4 Tic Tac Toe)\n";
        cout << "(8) Run game_8\n";
        cout << "(9) Exit program\n";
        string choice; 
        cout << "Choose number from 1 to 8: "; cin >> choice;

        if(choice == "1"){
            int choice;
            Player<char>* players[2];
            PyramidBoard* board = new PyramidBoard();

            cout << "\nWelcome to the Pyramid Tic Tac Toe Game\n";

            // Configure the first player
            string first_player_name, second_player_name;
            cout << "Choose first player type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter first player name: ";
                    cin >> first_player_name;
                    players[0] = new PyramidPlayer(first_player_name, 'X'); // 'X' as the symbol
                    break;
                case 2:
                    players[0] = new PyramidRandomPlayer("Computer", 'X', *board); // Random computer with 'X' as symbol
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    delete board;
                    continue;
            }

            // Configure the second player
            cout << "Choose second player type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter second player name: ";
                    cin >> second_player_name;
                    players[1] = new PyramidPlayer(second_player_name, 'O'); // 'O' as the symbol
                    break;
                case 2:
                    players[1] = new PyramidRandomPlayer("Computer", 'O', *board); // Random computer with 'O' as symbol
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    delete board;
                    if (players[0]) delete players[0];
                    continue;
            }

            // Assign the board to each player
            for (int i = 0; i < 2; ++i) {
                players[i]->setBoard(board);
            }

            // Start the game
            GameManager<char> game_manager(board, players);
            game_manager.run();

            // Clean up
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }

        else if(choice == "2"){
            cout << "\nWelcome to (Four In a Row) Game\n";
            cout << "(1) Play with your friend\n";
            cout << "(2) Play with computer\n";

            string choice;
            cin >> choice;

            if (choice == "1") {
                string name1, name2;
                cout << "Enter your name: ";
                cin >> name1;
                cout << "Enter your friend's name: ";
                cin >> name2;

                Four_in_a_row_board* board = new Four_in_a_row_board();
                Four_in_a_row_player player1(name1, 'X');
                Four_in_a_row_player player2(name2, 'O');

                GameManager<char> game_manager(board, new Player<char>*[2]{&player1, &player2});
                game_manager.run();
            } 
            else if (choice == "2") {
                string name;
                cout << "Enter your name: ";
                cin >> name;

                Four_in_a_row_board *board = new Four_in_a_row_board();
                Four_in_a_row_player player1(name, 'X');
                Four_in_a_row_random_player computer("Computer", 'O', *board);

                GameManager<char> game_manager(board, new Player<char>*[2]{&player1, &computer});
                game_manager.run();
            } 
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }

        else if(choice == "3"){
            int choice;
            Player<char>* players[2];
            X_O_Board<char>* B = new X_O_Board<char>();
            string playerXName, player2Name;

            cout << "\nWelcome to FCAI X-O Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new X_O_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new X_O_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    continue;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new X_O_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new X_O_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    continue;
            }

            // Create the game manager and run the game
            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }

        else if(choice == "4"){
            vector<string> Words;

            cout << "\nWelcome to Word Tic Tac Toe!\n";
            string file_name, word;
            cout << "Enter the file name containing all valid 3-letter words (e.g., dic.txt): ";
            cin >> file_name;

            ifstream File(file_name);
            if (!File.is_open()) {
                cerr << "Error: Unable to open file " << file_name << endl;
                continue;
            }

            // Read valid words into Words vector
            while (File >> word) {
                Words.push_back(word);
            }
            File.close();

            cout << "(1) Play with your friend\n";
            cout << "(2) Play with the computer\n";
            string choice;
            cin >> choice;

            Player<char>* players[2];

            if (choice == "1") {
                string player1, player2;
                cout << "Enter your name: ";
                cin >> player1;
                cout << "Enter your friend's name: ";
                cin >> player2;

                Word_board* wordBoard = new Word_board();
                wordBoard->x(Words);
                Word_player wordPlayer1(player1);
                Word_player wordPlayer2(player2);

                players[0] = &wordPlayer1;
                players[1] = &wordPlayer2;

                // Pass the vector of player pointers to the GameManager constructor
                GameManager<char> gameManager(wordBoard, players);
                gameManager.run();
            } else if (choice == "2") {
                string player;
                cout << "Enter your name: ";
                cin >> player;

                Word_board* wordBoard = new Word_board();
                wordBoard->x(Words);
                Word_player wordPlayer(player);
                Word_random_player wordRandomPlayer("Computer", *wordBoard);

                players[0] = &wordPlayer;
                players[1] = &wordRandomPlayer;

                // Pass the vector of player pointers to the GameManager constructor
                GameManager<char> gameManager(wordBoard, players);
                gameManager.run();
            } else {
                cout << "Invalid input. Try again." << endl;
            }
        }

        else if(choice == "5"){
            cout << "\nWelcome to Numerical Tic Tac Toe!\n";
            cout << "Rules:\n";
            cout << "1. Player1 takes odd numbers (1, 3, 5, 7, 9).\n";
            cout << "2. Player2 takes even numbers (2, 4, 6, 8).\n";
            cout << "3. Don't repeat any number you entered.\n";
            cout << "4. The sum of numbers in any row, column, or diagonal must equal 15 to win.\n";
            cout << "\nSelect a mode:\n";
            cout << "1. Play with a friend.\n";
            cout << "2. Play against the computer.\n";
            cout << "Choice: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                cout << "Enter Player 1's name: ";
                string player1_name;
                cin >> player1_name;

                cout << "Enter Player 2's name: ";
                string player2_name;
                cin >> player2_name;

                // Set up the game for two players
                Numerical_board board;
                Numerical_Player player1(player1_name, 'o'); // Odd numbers
                Numerical_Player player2(player2_name, 'e'); // Even numbers

                player1.setBoard(&board);
                player2.setBoard(&board);

                Player<char>* players[] = {&player1, &player2};
                GameManager<char> gameManager(&board, players);

                gameManager.run();

            } else if (choice == 2) {
                cout << "Enter your name: ";
                string player_name;
                cin >> player_name;

                cout << "Choose your type:\n";
                cout << "1. Odd numbers (1, 3, 5, 7, 9).\n";
                cout << "2. Even numbers (2, 4, 6, 8).\n";
                cout << "Choice: ";

                int type;
                cin >> type;

                if (type == 1) {
                    // Player chooses odd numbers
                    Numerical_board board;
                    Numerical_Player player(player_name, 'o');
                    Numerical_Random_Player computer("Computer", board);

                    player.setBoard(&board);
                    computer.setBoard(&board);

                    Player<char>* players[] = {&player, &computer};
                    GameManager<char> gameManager(&board, players);

                    gameManager.run();

                } else if (type == 2) {
                    // Player chooses even numbers
                    Numerical_board board;
                    Numerical_Player player(player_name, 'e');
                    Numerical_Random_Player computer("Computer", board);

                    player.setBoard(&board);
                    computer.setBoard(&board);

                    Player<char>* players[] = {&computer, &player};
                    GameManager<char> gameManager(&board, players);

                    gameManager.run();

                } else {
                    cout << "Invalid choice. Restart the game.\n";
                }

            } else {
                cout << "Invalid choice. Please restart the game and select a valid option.\n";
            }

        }

        else if(choice == "6"){
            int choice;
            Player<char>* players[2];
            X_Board<char>* B = new X_Board<char>();
            string playerXName, player2Name;

            cout << "\nWelcome to FCAI Misere Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new X_Player <char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new X_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    continue;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new X_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new X_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    continue;
            }

            // Create the game manager and run the game
            GameManager<char> x_game(B, players);
            x_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }

        else if(choice == "7"){
            cout << "\nWelcome to (4*4 Tic Tac Toe) Game\n";
            vector<vector<char>> board = {
                {'O', 'X', 'O', 'X'},
                {'_', '_', '_', '_'},
                {'_', '_', '_', '_'},
                {'X', 'O', 'X', 'O'}
            };
    
            // Display the board
            for (int i = 0; i < 4; i++) {
                cout << "|";
                for (int j = 0; j < 4; j++) {
                    cout << board[i][j] << "|";
                }
                cout << "\n";
            }
            cout << "\n";

            cout << "(1) Symbols at the top\n";
            cout << "(2) Symbols at the bottom\n";
            cout << "Choose 1 or 2: ";
            char c; cin >> c;
            if (c != '1' && c != '2') {
                cout << "Invalid choice for symbols. Exiting.\n";
                continue;
            }

            cout << "(1) Play with your friend\n";
            cout << "(2) Play with Computer\n";
            cout << "Choose 1 or 2: ";
            char s; cin >> s;

            if (s == '1') {
                string name1, name2;
                cout << "Please enter your name: "; cin >> name1;
                cout << "Please enter your friend's name: "; cin >> name2;

                // Initialize board and players
                Four_Four_board board;
                Four_Four_Player player1(name1, c);
                Four_Four_Player player2(name2, (c == '1' ? '2' : '1'));

                // Set up game manager
                Player<char>* players[] = {&player1, &player2};
                GameManager<char> gameManager(&board, players);

                gameManager.run();
            } 
            else if (s == '2') {
                string name1;
                cout << "Please enter your name: "; cin >> name1;

                // Initialize board and players
                Four_Four_board board;
                Four_Four_Player player1(name1, c);
                Four_Four_Random_Player player2("Computer", (c == '1' ? '2' : '1'), board);

                // Set up game manager
                Player<char>* players[] = {&player1, &player2};
                GameManager<char> gameManager(&board, players);

                gameManager.run();
            } 
            else {
                cout << "Invalid choice. Exiting.\n";
            }
        }

        else if(choice == "8"){
            // Create two players
            int choice;
            Player<char>* players[2];
            UltimateTicTacToeBoard<char>* gameBoard = new UltimateTicTacToeBoard<char>();
            string playerXName, player2Name;
            cout << "\nWelcome to Ultimate Tic Tac Toe! :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
            case 1:
                players[0] = new UltimateTicTacToePlayer<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new UltimateTicTacToeRandomPlayer<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                continue;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
            case 1:
                players[1] = new UltimateTicTacToePlayer<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new UltimateTicTacToeRandomPlayer<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                continue;
            }

            // Set the board for each player
            players[0]->setBoard(gameBoard);
            players[1]->setBoard(gameBoard);

            int x, y;
            bool player1_turn = true;

            while (!gameBoard->game_is_over()) {
                // Display the board
                gameBoard->display_board();

                if (player1_turn) {
                    cout << "Player 1's Turn (X):\n";
                    players[0]->getmove(x, y);
                    while (!gameBoard->update_board(x, y, 'X')) {
                        cout << "Invalid move! Try again.\n";
                        players[0]->getmove(x, y);
                    }
                }
                else {
                    cout << "Player 2's Turn (O):\n";
                    players[1]->getmove(x, y);
                    while (!gameBoard->update_board(x, y, 'O')) {
                        cout << "Invalid move! Try again.\n";
                        players[1]->getmove(x, y);
                    }
                }

                player1_turn = !player1_turn;

                // After each move, check if a small board is won
                int small_board_x = x / 3;
                int small_board_y = y / 3;
                if (gameBoard->update_small_board(small_board_x, small_board_y, (player1_turn ? 'O' : 'X'))) {
                    cout << "Player " << (player1_turn ? 2 : 1) << " won a small board at (" << small_board_x << "," << small_board_y << ").\n";
                }
            }

            if (gameBoard->is_win()) {
                cout << "We have a winner! Congratulations!\n";
            }
            else {
                cout << "The game ended in a draw.\n";
            }

            // Clean up dynamically allocated memory
            delete gameBoard;
            delete players[0];
            delete players[1];
        }

        else if(choice == "9"){ cout << "Exit!\n"; break; }

        else{
            cout << "Invalid choice. Try again\n\n";
        }

    }

    return 0;
}