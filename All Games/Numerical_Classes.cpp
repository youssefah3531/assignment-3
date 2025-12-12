#include "Numerical_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

NumericalGame::NumericalGame() {
    // Initialize 3x3 board with zeros
    board.resize(3, vector<int>(3, 0));

    // Track numbers 1-9 (index 0 is unused, indices 1-9 are used)
    usedNumbers.resize(10, false);

    // Initialize player number pools
    player1Numbers = { 1, 3, 5, 7, 9 }; // Odd numbers
    player2Numbers = { 2, 4, 6, 8 };    // Even numbers

    currentPlayer = 1; // Player1 starts
    movesCount = 0;
}

void NumericalGame::displayBoard() const {
    cout << "\nCurrent Board:\n";
    cout << "-------------\n";

    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                cout << "   |";
            }
            else {
                cout << " " << board[i][j] << " |";
            }
        }
        cout << "\n-------------\n";
    }
}

void NumericalGame::displayAvailableNumbers() const {
    cout << "\nPlayer " << currentPlayer << " (";
    cout << (currentPlayer == 1 ? "Odds" : "Evens") << "): Available numbers: ";

    const vector<int>& currentNumbers = (currentPlayer == 1) ? player1Numbers : player2Numbers;
    bool first = true;

    for (int num : currentNumbers) {
        if (!usedNumbers[num]) {
            if (!first) cout << ", ";
            cout << num;
            first = false;
        }
    }
    cout << endl;
}

bool NumericalGame::isValidMove(int number, int row, int col) const {
    // Check bounds
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        return false;
    }

    // Check if cell is empty
    if (board[row][col] != 0) {
        return false;
    }

    // Check if number is already used
    if (usedNumbers[number]) {
        return false;
    }

    // Check if number belongs to current player
    if (currentPlayer == 1) {
        // Player 1 must use odd numbers
        if (number % 2 == 0) return false;
        auto it = find(player1Numbers.begin(), player1Numbers.end(), number);
        if (it == player1Numbers.end()) return false;
    }
    else {
        // Player 2 must use even numbers
        if (number % 2 == 1) return false;
        auto it = find(player2Numbers.begin(), player2Numbers.end(), number);
        if (it == player2Numbers.end()) return false;
    }

    return true;
}

bool NumericalGame::makeMove(int number, int row, int col) {
    if (!isValidMove(number, row, col)) {
        return false;
    }

    // Place the number
    board[row][col] = number;
    usedNumbers[number] = true;
    movesCount++;

    return true;
}

bool NumericalGame::checkWin() const {
    const int TARGET_SUM = 15;

    // Check rows
    for (int i = 0; i < 3; i++) {
        int sum = board[i][0] + board[i][1] + board[i][2];
        if (sum == TARGET_SUM && board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        int sum = board[0][j] + board[1][j] + board[2][j];
        if (sum == TARGET_SUM && board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0) {
            return true;
        }
    }

    // Check diagonals
    int diag1 = board[0][0] + board[1][1] + board[2][2];
    if (diag1 == TARGET_SUM && board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) {
        return true;
    }

    int diag2 = board[0][2] + board[1][1] + board[2][0];
    if (diag2 == TARGET_SUM && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) {
        return true;
    }

    return false;
}

bool NumericalGame::isBoardFull() const {
    return movesCount >= 9;
}

bool NumericalGame::isGameOver() const {
    return checkWin() || isBoardFull();
}

void NumericalGame::switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

vector<int> NumericalGame::getAvailableNumbersForCurrentPlayer() const {
    vector<int> available;
    const vector<int>& currentNumbers = (currentPlayer == 1) ? player1Numbers : player2Numbers;

    for (int num : currentNumbers) {
        if (!usedNumbers[num]) {
            available.push_back(num);
        }
    }

    return available;
}