#ifndef NUMERICAL_CLASSES_H
#define NUMERICAL_CLASSES_H

#include <vector>
#include <string>
#include "BoardGame_Classes.h"
using namespace std;

class NumericalGame {
private:
    std::vector<std::vector<int>> board; // 3x3 board, 0 means empty
    std::vector<bool> usedNumbers; // Track used numbers (1-9)
    int currentPlayer; // 1 for Player1 (odds), 2 for Player2 (evens)
    int movesCount;

    // Player number pools
    std::vector<int> player1Numbers;
    std::vector<int> player2Numbers;

public:
    NumericalGame();

    // Display functions
    void displayBoard() const;
    void displayAvailableNumbers() const;

    // Game logic
    bool makeMove(int number, int row, int col);
    bool checkWin() const;
    bool isBoardFull() const;
    bool isValidMove(int number, int row, int col) const;
    int getCurrentPlayer() const { return currentPlayer; }

    // Game state
    bool isGameOver() const;
    void switchPlayer();

    // Helper functions
    std::vector<int> getAvailableNumbersForCurrentPlayer() const;
};

#endif // NUMERICAL_CLASSES_H