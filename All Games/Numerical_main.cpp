#include "Numerical_Classes.h"
#include <iostream>
#include <limits>

using namespace std;

int Numerical_main() {
    NumericalGame game;
    bool playAgain = true;

    while (playAgain) {
        game = NumericalGame(); // Reset game
        cout << "\n=== NUMERICAL TIC-TAC-TOE ===\n";
        cout << "Player 1: Odd numbers (1, 3, 5, 7, 9)\n";
        cout << "Player 2: Even numbers (2, 4, 6, 8)\n";
        cout << "Objective: Make a line sum to 15\n";

        while (!game.isGameOver()) {
            // Display current state
            game.displayBoard();
            game.displayAvailableNumbers();

            int number, row, col;
            bool validMove = false;

            // Get player input
            while (!validMove) {
                cout << "\nPlayer " << game.getCurrentPlayer() << "'s turn.\n";

                // Get number
                cout << "Enter a number: ";
                while (!(cin >> number)) {
                    cout << "Invalid input. Enter a valid number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Get position
                cout << "Enter row (1-3): ";
                while (!(cin >> row)) {
                    cout << "Invalid input. Enter row (1-3): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter column (1-3): ";
                while (!(cin >> col)) {
                    cout << "Invalid input. Enter column (1-3): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Convert to 0-based indexing
                row--;
                col--;

                // Attempt move
                if (game.makeMove(number, row, col)) {
                    validMove = true;
                }
                else {
                    cout << "Invalid move! Please try again.\n";
                    cout << "Make sure:\n";
                    cout << "1. The cell is empty\n";
                    cout << "2. The number is available for your player\n";
                    cout << "3. The number hasn't been used before\n";
                }
            }

            // Check for win
            if (game.checkWin()) {
                game.displayBoard();
                cout << "\n🎉 Player " << game.getCurrentPlayer() << " wins! 🎉\n";
                cout << "They made a line sum to 15!\n";
                break;
            }

            // Switch to next player if game not over
            if (!game.isBoardFull()) {
                game.switchPlayer();
            }
        }

        // Check for draw
        if (!game.checkWin() && game.isBoardFull()) {
            game.displayBoard();
            cout << "\nIt's a draw! No line sums to 15.\n";
        }

        // Ask to play again
        char choice;
        cout << "\nPlay again? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        playAgain = (choice == 'y' || choice == 'Y');
    }

    cout << "\nThanks for playing Numerical Tic-Tac-Toe!\n";
    return 0;
}