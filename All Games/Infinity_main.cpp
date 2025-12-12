#include "Infinity_Classes.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

int Infinity_main() {
    bool playAgain = true;

    while (playAgain) {
        InfinityGame game;
        game.displayInstructions();

        cout << "\nGame starting...\n";
        cout << "Every " << InfinityGame::MOVES_BEFORE_REMOVAL << " moves, the oldest move will vanish!\n\n";

        while (!game.isGameOver()) {
            // Display current board
            game.displayBoard();

            int row, col;
            bool validMove = false;

            // Get player input
            while (!validMove) {
                cout << "\nPlayer " << game.getCurrentPlayer() << "'s turn.\n";

                cout << "Enter row (1-3): ";
                while (!(cin >> row) || row < 1 || row > 3) {
                    cout << "Invalid input. Enter row (1-3): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter column (1-3): ";
                while (!(cin >> col) || col < 1 || col > 3) {
                    cout << "Invalid input. Enter column (1-3): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Convert to 0-based indexing
                row--;
                col--;

                // Attempt move
                if (game.makeMove(row, col)) {
                    validMove = true;
                }
                else {
                    cout << "Invalid move! That position is either:\n";
                    cout << "1. Out of bounds (1-3 only)\n";
                    cout << "2. Already occupied\n";
                    cout << "Please try again.\n";
                }
            }

            // Check for win immediately after move
            if (game.checkWin()) {
                // Small delay for dramatic effect
                this_thread::sleep_for(chrono::milliseconds(500));

                game.displayBoard();
                cout << "\n🎉🎉🎉 Player " << game.getCurrentPlayer() << " wins! 🎉🎉🎉\n";
                cout << "They got 3 in a row before any moves vanished!\n";
                cout << "Total moves made: " << game.getTotalMoves() << "\n";
                break;
            }

            // Process move cycle (check if oldest move should vanish)
            game.processMoveCycle();

            // Check if board is temporarily full
            if (game.isBoardFull()) {
                cout << "\nBoard is currently full! Next move will cause the oldest move to vanish...\n";
            }

            // Switch to next player
            game.switchPlayer();
        }

        // If no one won (shouldn't happen in infinity mode, but just in case)
        if (!game.isGameOver() && game.getTotalMoves() >= 50) {
            cout << "\nMaximum moves reached! Game ending...\n";
            cout << "This is Infinity Tic-Tac-Toe - the game could go on forever!\n";
        }

        // Ask to play again
        char choice;
        cout << "\nPlay again? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        playAgain = (choice == 'y' || choice == 'Y');
    }

    cout << "\nThanks for playing Infinity Tic-Tac-Toe!\n";
    cout << "Remember: In infinity, nothing lasts forever... not even winning moves!\n";
    return 0;
}