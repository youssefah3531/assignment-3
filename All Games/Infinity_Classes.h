#ifndef INFINITY_CLASSES_H
#define INFINITY_CLASSES_H

#include <vector>
#include <string>
#include <queue>
#include <utility>
#include "BoardGame_Classes.h"
using namespace std;/**
 * @file Infinity_Classes.h
 * @brief Defines the Infinity game classes.
 * 
 * Infinity: A game on a 3x3 grid where players alternate placing 'X' and 'O'.
 * After every 3 moves, the oldest move is removed from the board.
 * The first player to align 3 of their symbols in a row, column, or diagonal wins.
 */


class InfinityGame {
private:
    static const int BOARD_SIZE = 3;
    static const int MOVES_BEFORE_REMOVAL = 3;

    struct MoveRecord {
        int row;
        int col;
        char player;
        int moveNumber;
    };

    std::vector<std::vector<char>> board; // 3x3 board
    std::queue<MoveRecord> moveHistory; // Track moves in order
    char currentPlayer; // 'X' or 'O'
    int moveCounter;
    int totalMoves;

    // Helper functions
    bool isValidPosition(int row, int col) const;
    bool isCellEmpty(int row, int col) const;
    void removeOldestMove();

public:
    InfinityGame();

    // Display functions
    void displayBoard() const;
    void displayInstructions() const;

    // Game logic
    bool makeMove(int row, int col);
    bool checkWin() const;
    bool isBoardFull() const;
    bool isValidMove(int row, int col) const;
    char getCurrentPlayer() const { return currentPlayer; }
    int getMoveCounter() const { return moveCounter; }
    int getTotalMoves() const { return totalMoves; }

    // Game state
    bool isGameOver() const;
    void switchPlayer();
    void processMoveCycle();

    // Get oldest move info
    std::pair<int, int> getOldestMovePosition() const;
};

#endif // INFINITY_CLASSES_H