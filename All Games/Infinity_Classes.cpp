#include "Infinity_Classes.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <utility>

using namespace std;

InfinityGame::InfinityGame() {
    // Initialize 3x3 board with empty spaces
    board.resize(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));

    currentPlayer = 'X'; // Player X starts
    moveCounter = 0;
    totalMoves = 0;
}

bool InfinityGame::isValidPosition(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool InfinityGame::isCellEmpty(int row, int col) const {
    return isValidPosition(row, col) && board[row][col] == ' ';
}

void InfinityGame::removeOldestMove() {
    if (!moveHistory.empty()) {
        MoveRecord oldest = moveHistory.front();
        moveHistory.pop();

        // Remove from board if it's still there (might have been overwritten)
        if (board[oldest.row][oldest.col] == oldest.player) {
            board[oldest.row][oldest.col] = ' ';
            cout << "Move #" << oldest.moveNumber << " (Player " << oldest.player
                << " at position " << oldest.row + 1 << "," << oldest.col + 1
                << ") has vanished!\n";
        }
    }
}

void InfinityGame::displayBoard() const {
    cout << "\nMove: " << totalMoves + 1;
    cout << " | Current Player: " << currentPlayer;
    cout << " | Moves until removal: " << (MOVES_BEFORE_REMOVAL - (moveCounter % MOVES_BEFORE_REMOVAL)) << "\n\n";

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

    // Display move history size
    cout << "Moves in history: " << moveHistory.size() << "\n";
}

void InfinityGame::displayInstructions() const {
    cout << "\n=== INFINITY TIC-TAC-TOE ===\n";
    cout << "Board: 3x3 grid\n";
    cout << "Winning condition: Get 3 in a row (horizontal, vertical, or diagonal)\n";
    cout << "Special rule: After every " << MOVES_BEFORE_REMOVAL << " moves, the OLDEST move vanishes!\n";
    cout << "Strategy: Win before your winning moves disappear!\n";
}

bool InfinityGame::isValidMove(int row, int col) const {
    return isValidPosition(row, col) && isCellEmpty(row, col);
}

bool InfinityGame::makeMove(int row, int col) {
    if (!isValidMove(row, col)) {
        return false;
    }

    // Record the move
    MoveRecord newMove;
    newMove.row = row;
    newMove.col = col;
    newMove.player = currentPlayer;
    newMove.moveNumber = totalMoves + 1;

    // Make the move
    board[row][col] = currentPlayer;
    moveHistory.push(newMove);

    moveCounter++;
    totalMoves++;

    return true;
}

bool InfinityGame::checkWin() const {
    char player = currentPlayer;

    // Check rows
    for (int row = 0; row < BOARD_SIZE; row++) {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player) {
            return true;
        }
    }

    // Check columns
    for (int col = 0; col < BOARD_SIZE; col++) {
        if (board[0][col] == player && board[1][col] == player && board[2][col] == player) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

bool InfinityGame::isBoardFull() const {
    // In infinity mode, board is never truly "full" because moves disappear
    // But we can check if all cells are currently occupied
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool InfinityGame::isGameOver() const {
    // Game ends when someone wins
    return checkWin();
}

void InfinityGame::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void InfinityGame::processMoveCycle() {
    // Check if it's time to remove oldest move
    if (moveCounter >= MOVES_BEFORE_REMOVAL) {
        cout << "\n--- " << MOVES_BEFORE_REMOVAL << " moves completed! ---\n";
        removeOldestMove();
        moveCounter = 0; // Reset counter
    }
}

pair<int, int> InfinityGame::getOldestMovePosition() const {
    if (!moveHistory.empty()) {
        MoveRecord oldest = moveHistory.front();
        return make_pair(oldest.row, oldest.col);
    }
    return make_pair(-1, -1);
}