#include "Obstacles_Classes.h"
#include <iostream>
#include <limits>

using namespace std;

int Obstacles_main() {
    bool playAgain = true;

    while (playAgain) {
        ObstaclesGame game;
        game.displayInstructions();

        cout << "\nGame starting...\n";

        while (!game.isGameOver()) {
            // Display current board
            game.displayBoard();

            int row, col;
            bool validMove = false;

            // Get player input
            while (!validMove) {
                cout << "\nPlayer " << game.getCurrentPlayer() << "'s turn.\n";

                cout << "Enter row (1-6): ";
                while (!(cin >> row) || row < 1 || row > 6) {
                    cout << "Invalid input. Enter row (1-6): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter column (1-6): ";
                while (!(cin >> col) || col < 1 || col > 6) {
                    cout << "Invalid input. Enter column (1-6): ";
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
                    cout << "1. Out of bounds (1-6 only)\n";
                    cout << "2. Already occupied by a player\n";
                    cout << "3. Blocked by an obstacle (#)\n";
                    cout << "Please try again.\n";
                }
            }

            // Check for win after move
            if (game.checkWin()) {
                game.displayBoard();
                cout << "\n🎉 Player " << game.getCurrentPlayer() << " wins! 🎉\n";
                cout << "They got 4 in a row!\n";
                break;
            }

            // Check for draw
            if (game.isBoardFull()) {
                game.displayBoard();
                cout << "\nIt's a draw! The board is full.\n";
                break;
            }

            // Switch player and check if round is complete
            game.switchPlayer();

            // If both players have moved this round, add obstacles
            if (game.getRoundCount() == 1 || game.getCurrentPlayer() == 'X') {
                // This means we just completed a full round (both players moved)
                cout << "\n--- End of Round " << game.getRoundCount() << " ---\n";
                cout << "Adding " << ObstaclesGame::OBSTACLES_PER_ROUND << " random obstacles...\n";
                game.nextRound();

                // Display updated board with obstacles
                game.displayBoard();

                // Check if obstacles made the game unwinnable
                if (game.countEmptyCells() < ObstaclesGame::OBSTACLES_PER_ROUND) {
                    cout << "\nWarning: Few empty cells remaining!\n";
                }
            }
        }

        // Ask to play again
        char choice;
        cout << "\nPlay again? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        playAgain = (choice == 'y' || choice == 'Y');
    }

    cout << "\nThanks for playing Obstacles Tic-Tac-Toe!\n";
    return 0;
}