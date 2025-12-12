#include "Diamond_TTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <iomanip>
using namespace std;

bool DiamondBoard::is_valid_cell(int r, int c) const {
    // Diamond shape: center row has all 5, rows above/below have fewer
    int center = 2; // Middle row
    int dist_from_center = abs(r - center);
    int min_col = dist_from_center;
    int max_col = 4 - dist_from_center;
    return (c >= min_col && c <= max_col);
}

DiamondBoard::DiamondBoard() : Board(5, 5) {
    // Initialize all as invalid, then set valid cells
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (is_valid_cell(r, c))
                board[r][c] = blank_symbol;
            else
                board[r][c] = invalid;
        }
    }
}

bool DiamondBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;
    
    if (!is_valid_cell(x, y))
        return false;
    
    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = toupper(mark);
    n_moves++;
    return true;
}

bool DiamondBoard::has_line_of_3(char sym) const {
    // Check all possible lines of 3 in the diamond
    // Horizontal lines
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c <= 2; c++) {
            if (is_valid_cell(r, c) && is_valid_cell(r, c+1) && is_valid_cell(r, c+2)) {
                if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym)
                    return true;
            }
        }
    }
    
    // Vertical lines
    for (int c = 0; c < 5; c++) {
        for (int r = 0; r <= 2; r++) {
            if (is_valid_cell(r, c) && is_valid_cell(r+1, c) && is_valid_cell(r+2, c)) {
                if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym)
                    return true;
            }
        }
    }
    
    // Diagonal lines (down-right)
    for (int r = 0; r <= 2; r++) {
        for (int c = 0; c <= 2; c++) {
            if (is_valid_cell(r, c) && is_valid_cell(r+1, c+1) && is_valid_cell(r+2, c+2)) {
                if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym)
                    return true;
            }
        }
    }
    
    // Diagonal lines (down-left)
    for (int r = 0; r <= 2; r++) {
        for (int c = 2; c < 5; c++) {
            if (is_valid_cell(r, c) && is_valid_cell(r+1, c-1) && is_valid_cell(r+2, c-2)) {
                if (board[r][c] == sym && board[r+1][c-1] == sym && board[r+2][c-2] == sym)
                    return true;
            }
        }
    }
    
    return false;
}

bool DiamondBoard::has_line_of_4(char sym) const {
    // Check all possible lines of 4 in the diamond
    // Horizontal lines
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c <= 1; c++) {
            if (is_valid_cell(r, c) && is_valid_cell(r, c+1) && 
                is_valid_cell(r, c+2) && is_valid_cell(r, c+3)) {
                if (board[r][c] == sym && board[r][c+1] == sym && 
                    board[r][c+2] == sym && board[r][c+3] == sym)
                    return true;
            }
        }
    }
    
    // Vertical lines
    for (int c = 0; c < 5; c++) {
        for (int r = 0; r <= 1; r++) {
            if (is_valid_cell(r, c) && is_valid_cell(r+1, c) && 
                is_valid_cell(r+2, c) && is_valid_cell(r+3, c)) {
                if (board[r][c] == sym && board[r+1][c] == sym && 
                    board[r+2][c] == sym && board[r+3][c] == sym)
                    return true;
            }
        }
    }
    
    // Diagonal lines (down-right)
    for (int r = 0; r <= 1; r++) {
        for (int c = 0; c <= 1; c++) {
            if (is_valid_cell(r, c) && is_valid_cell(r+1, c+1) && 
                is_valid_cell(r+2, c+2) && is_valid_cell(r+3, c+3)) {
                if (board[r][c] == sym && board[r+1][c+1] == sym && 
                    board[r+2][c+2] == sym && board[r+3][c+3] == sym)
                    return true;
            }
        }
    }
    
    // Diagonal lines (down-left)
    for (int r = 0; r <= 1; r++) {
        for (int c = 3; c < 5; c++) {
            if (is_valid_cell(r, c) && is_valid_cell(r+1, c-1) && 
                is_valid_cell(r+2, c-2) && is_valid_cell(r+3, c-3)) {
                if (board[r][c] == sym && board[r+1][c-1] == sym && 
                    board[r+2][c-2] == sym && board[r+3][c-3] == sym)
                    return true;
            }
        }
    }
    
    return false;
}

bool DiamondBoard::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    // Must have both a line of 3 AND a line of 4
    return has_line_of_3(sym) && has_line_of_4(sym);
}

bool DiamondBoard::is_draw(Player<char>* player) {
    // Check if all valid cells are filled
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (is_valid_cell(r, c) && board[r][c] == blank_symbol)
                return false;
        }
    }
    return !is_win(player);
}

bool DiamondBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

DiamondUI::DiamondUI() : UI<char>("Welcome to Diamond Tic-Tac-Toe!", 3) {}

Player<char>* DiamondUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* DiamondUI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() 
             << ") - Need both a line of 3 AND a line of 4 to win!\n";
        cout << "Enter row and col (0-4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        // Random valid move
        DiamondBoard* board = dynamic_cast<DiamondBoard*>(player->get_board_ptr());
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (!board->is_valid_cell(x, y) || 
                 board->get_board_matrix()[x][y] != '.');
    }
    
    return new Move<char>(x, y, player->get_symbol());
}

void DiamondUI::display_board_matrix(const vector<vector<char>>& M) const {
    cout << "\n      0     1     2     3     4\n";
    cout << "    +-----+-----+-----+-----+-----+\n";
    for (int r = 0; r < 5; r++) {
        cout << "  " << r << " |";
        for (int c = 0; c < 5; c++) {
            if (M[r][c] == '#') {
                cout << "     |";
            } else {
                cout << "  " << M[r][c] << "  |";
            }
        }
        cout << "\n    +-----+-----+-----+-----+-----+\n";
    }
    cout << endl;
}

PlayerType DiamondUI::choose_player_type() {
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

