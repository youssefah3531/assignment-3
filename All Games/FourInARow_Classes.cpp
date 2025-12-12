#include "FourInARow_Classes.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>
using namespace std;

FourInARowBoard::FourInARowBoard() : Board(ROWS, COLS) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

int FourInARowBoard::get_drop_row(int col) const {
    if (col < 0 || col >= columns) return -1;
    
    // Find the lowest empty row in this column
    for (int r = rows - 1; r >= 0; r--) {
        if (board[r][col] == blank_symbol)
            return r;
    }
    return -1; // Column is full
}

bool FourInARowBoard::update_board(Move<char>* move) {
    int col = move->get_y(); // Column to drop piece
    char mark = move->get_symbol();

    if (col < 0 || col >= columns)
        return false;

    int row = get_drop_row(col);
    if (row == -1) // Column is full
        return false;

    board[row][col] = toupper(mark);
    n_moves++;
    return true;
}

bool FourInARowBoard::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    // Check horizontal
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c <= columns - 4; c++) {
            if (board[r][c] == sym && board[r][c+1] == sym &&
                board[r][c+2] == sym && board[r][c+3] == sym)
                return true;
        }
    }

    // Check vertical
    for (int c = 0; c < columns; c++) {
        for (int r = 0; r <= rows - 4; r++) {
            if (board[r][c] == sym && board[r+1][c] == sym &&
                board[r+2][c] == sym && board[r+3][c] == sym)
                return true;
        }
    }

    // Check diagonal (down-right)
    for (int r = 0; r <= rows - 4; r++) {
        for (int c = 0; c <= columns - 4; c++) {
            if (board[r][c] == sym && board[r+1][c+1] == sym &&
                board[r+2][c+2] == sym && board[r+3][c+3] == sym)
                return true;
        }
    }

    // Check diagonal (down-left)
    for (int r = 0; r <= rows - 4; r++) {
        for (int c = 3; c < columns; c++) {
            if (board[r][c] == sym && board[r+1][c-1] == sym &&
                board[r+2][c-2] == sym && board[r+3][c-3] == sym)
                return true;
        }
    }

    return false;
}

bool FourInARowBoard::is_draw(Player<char>* player) {
    // Check if all columns are full
    for (int c = 0; c < columns; c++) {
        if (get_drop_row(c) != -1)
            return false;
    }
    return !is_win(player);
}

bool FourInARowBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

FourInARowUI::FourInARowUI() : UI<char>("Welcome to Four-in-a-Row!", 3) {}

Player<char>* FourInARowUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* FourInARowUI::get_move(Player<char>* player) {
    int col;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() 
             << ") - Drop piece in column (0-6): ";
        cin >> col;
    }
    else if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        // Random valid column
        FourInARowBoard* board = dynamic_cast<FourInARowBoard*>(player->get_board_ptr());
        do {
            col = rand() % board->get_columns();
        } while (board->get_drop_row(col) == -1);
    }
    
    // Return move with row=0 (will be calculated in update_board)
    return new Move<char>(0, col, player->get_symbol());
}

PlayerType FourInARowUI::choose_player_type() {
    cout << "Choose player type:\n1) Human\n2) Computer\n";
    int ch;
    while (!(cin >> ch) || (ch != 1 && ch != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (ch == 1) return PlayerType::HUMAN;
    return PlayerType::COMPUTER;
}

