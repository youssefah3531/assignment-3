#ifndef OBSTACLES_CLASSES_H
#define OBSTACLES_CLASSES_H

#include <vector>
#include <string>
#include <utility>
#include "BoardGame_Classes.h"
using namespace std;

class ObstaclesGame {
private:
    static const int BOARD_SIZE = 6;
    static const int WIN_LENGTH = 4;

    std::vector<std::vector<char>> board; // 6x6 board
    char currentPlayer; // 'X' or 'O'
    int roundCount;
    int movesCount;

    // Helper functions
    bool isValidPosition(int row, int col) const;
    bool isCellEmpty(int row, int col) const;
    bool isCellObstacle(int row, int col) const;
    void addRandomObstacles();

public:
    static const int OBSTACLES_PER_ROUND = 2;
    ObstaclesGame();

    // Display functions
    void displayBoard() const;
    void displayInstructions() const;

    // Game logic
    bool makeMove(int row, int col);
    bool checkWin() const;
    bool checkWinDirection(int startRow, int startCol, int dRow, int dCol) const;
    bool isBoardFull() const;
    bool isValidMove(int row, int col) const;
    char getCurrentPlayer() const { return currentPlayer; }

    // Game state
    bool isGameOver() const;
    void switchPlayer();
    void nextRound();
    int getRoundCount() const { return roundCount; }

    // Count empty cells
    int countEmptyCells() const;
};

#endif // OBSTACLES_CLASSES_H