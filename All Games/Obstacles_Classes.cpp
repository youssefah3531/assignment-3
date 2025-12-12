#include "Obstacles_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>

using namespace std;

ObstaclesGame::ObstaclesGame() {
    // Initialize 6x6 board with empty spaces
    board.resize(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));

    currentPlayer = 'X'; // Player X starts
    roundCount = 1;
    movesCount = 0;

    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
}

bool ObstaclesGame::isValidPosition(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool ObstaclesGame::isCellEmpty(int row, int col) const {
    return isValidPosition(row, col) && board[row][col] == ' ';
}

bool ObstaclesGame::isCellObstacle(int row, int col) const {
    return isValidPosition(row, col) && board[row][col] == '#';
}

void ObstaclesGame::addRandomObstacles() {
    int obstaclesAdded = 0;
    int maxAttempts = BOARD_SIZE * BOARD_SIZE * 2;
    int attempts = 0;

    while (obstaclesAdded < OBSTACLES_PER_ROUND && attempts < maxAttempts) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;

        // Add obstacle only if cell is empty
        if (isCellEmpty(row, col)) {
            board[row][col] = '#';
            obstaclesAdded++;
            cout << "Obstacle added at position (" << row + 1 << ", " << col + 1 << ")\n";
        }

        attempts++;
    }
}

void ObstaclesGame::displayBoard() const {
    cout << "\nRound: " << roundCount;
    cout << " | Current Player: " << currentPlayer << "\n\n";

    // Display column numbers
    cout << "    ";
    for (int col = 0; col < BOARD_SIZE; col++) {
        cout << " " << col + 1 << "  ";
    }
    cout << "\n";

    // Display top border
    cout << "  +";
    for (int col = 0; col < BOARD_SIZE; col++) {
        cout << "---+";
    }
    cout << "\n";

    // Display board rows
    for (int row = 0; row < BOARD_SIZE; row++) {
        cout << row + 1 << " |";
        for (int col = 0; col < BOARD_SIZE; col++) {
            char cell = board[row][col];
            if (cell == ' ') {
                cout << "   |";
            }
            else if (cell == '#') {
                cout << " # |";
            }
            else {
                cout << " " << cell << " |";
            }
        }
        cout << "\n";

        // Display row border
        cout << "  +";
        for (int col = 0; col < BOARD_SIZE; col++) {
            cout << "---+";
        }
        cout << "\n";
    }

    // Legend
    cout << "\nLegend: X = Player 1, O = Player 2, # = Obstacle\n";
}

void ObstaclesGame::displayInstructions() const {
    cout << "\n=== OBSTACLES TIC-TAC-TOE ===\n";
    cout << "Board: 6x6 grid\n";
    cout << "Winning condition: Get 4 in a row (horizontal, vertical, or diagonal)\n";
    cout << "Special rule: After each round (both players move), 2 obstacles are randomly added!\n";
    cout << "Obstacles (#) block cells for both players.\n";
}

bool ObstaclesGame::isValidMove(int row, int col) const {
    return isValidPosition(row, col) && isCellEmpty(row, col);
}

bool ObstaclesGame::makeMove(int row, int col) {
    if (!isValidMove(row, col)) {
        return false;
    }

    board[row][col] = currentPlayer;
    movesCount++;
    return true;
}

bool ObstaclesGame::checkWinDirection(int startRow, int startCol, int dRow, int dCol) const {
    char player = board[startRow][startCol];
    if (player == ' ' || player == '#') return false;

    for (int i = 1; i < WIN_LENGTH; i++) {
        int row = startRow + i * dRow;
        int col = startCol + i * dCol;

        if (!isValidPosition(row, col) || board[row][col] != player) {
            return false;
        }
    }

    return true;
}

bool ObstaclesGame::checkWin() const {
    // Check all possible winning positions
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] != ' ' && board[row][col] != '#') {
                // Check horizontal (right)
                if (col <= BOARD_SIZE - WIN_LENGTH &&
                    checkWinDirection(row, col, 0, 1)) {
                    return true;
                }

                // Check vertical (down)
                if (row <= BOARD_SIZE - WIN_LENGTH &&
                    checkWinDirection(row, col, 1, 0)) {
                    return true;
                }

                // Check diagonal (down-right)
                if (row <= BOARD_SIZE - WIN_LENGTH && col <= BOARD_SIZE - WIN_LENGTH &&
                    checkWinDirection(row, col, 1, 1)) {
                    return true;
                }

                // Check diagonal (down-left)
                if (row <= BOARD_SIZE - WIN_LENGTH && col >= WIN_LENGTH - 1 &&
                    checkWinDirection(row, col, 1, -1)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool ObstaclesGame::isBoardFull() const {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool ObstaclesGame::isGameOver() const {
    return checkWin() || isBoardFull();
}

void ObstaclesGame::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void ObstaclesGame::nextRound() {
    roundCount++;
    addRandomObstacles();
}

int ObstaclesGame::countEmptyCells() const {
    int count = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == ' ') {
                count++;
            }
        }
    }
    return count;
}