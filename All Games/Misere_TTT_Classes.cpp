#include "Misere_TTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>
using namespace std;

MisereBoard::MisereBoard() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool MisereBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;
    
    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = toupper(mark);
    n_moves++;
    return true;
}

bool MisereBoard::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool MisereBoard::is_win(Player<char>* player) {
    // In Misère, you win if the opponent loses
    // This is handled in GameManager by checking is_lose
    return false;
}

bool MisereBoard::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player));
}

bool MisereBoard::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}

MisereUI::MisereUI() : UI<char>("Welcome to Misère (Inverse) Tic-Tac-Toe!", 3) {}

Player<char>* MisereUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* MisereUI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() 
             << ") - Avoid getting three-in-a-row!\n";
        cout << "Enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        // Random move for now (can be improved with AI)
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    
    return new Move<char>(x, y, player->get_symbol());
}

PlayerType MisereUI::choose_player_type() {
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

