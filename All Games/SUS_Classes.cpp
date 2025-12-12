#include "SUS_Classes.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <cctype>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

SUSBoard::SUSBoard() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

char SUSBoard::get_player_letter(Player<char>* player) const {
    auto it = player_letters.find(player);
    if (it != player_letters.end())
        return it->second;
    return '\0';
}

void SUSBoard::set_player_letter(Player<char>* player, char letter) {
    player_letters[player] = toupper(letter);
}

void SUSBoard::set_current_player(Player<char>* player) {
    current_player = player;
}

bool SUSBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;
    
    if (board[x][y] != blank_symbol)
        return false;
    
    // Validate that mark is 'S' or 'U'
    mark = toupper(mark);
    if (mark != 'S' && mark != 'U')
        return false;
    
    // Verify the current player is using the correct letter
    if (current_player) {
        char player_letter = get_player_letter(current_player);
        if (player_letter != '\0' && player_letter != mark) {
            // Player is trying to use wrong letter
            return false;
        }
    }

    board[x][y] = mark;
    if (current_player) {
        move_owners[make_pair(x, y)] = current_player;
        // Also set player letter if not set yet
        if (get_player_letter(current_player) == '\0') {
            player_letters[current_player] = mark;
        }
    }
    n_moves++;
    current_player = nullptr; // Reset after move
    return true;
}

int SUSBoard::count_SUS_sequences() const {
    int count = 0;
    
    // Check all horizontal sequences
    for (int r = 0; r < 3; r++) {
        if (board[r][0] == 'S' && board[r][1] == 'U' && board[r][2] == 'S')
            count++;
    }
    
    // Check all vertical sequences
    for (int c = 0; c < 3; c++) {
        if (board[0][c] == 'S' && board[1][c] == 'U' && board[2][c] == 'S')
            count++;
    }
    
    // Check main diagonal
    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S')
        count++;
    
    // Check anti-diagonal
    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S')
        count++;
    
    return count;
}

int SUSBoard::count_player_sequences(Player<char>* player) const {
    int count = 0;
    char player_letter = get_player_letter(player);
    if (player_letter == '\0') return 0;
    
    // Check all horizontal sequences where player contributed
    for (int r = 0; r < 3; r++) {
        if (board[r][0] == 'S' && board[r][1] == 'U' && board[r][2] == 'S') {
            // Check if player placed letters in this sequence
            bool player_contributed = false;
            if (player_letter == 'S') {
                auto it1 = move_owners.find(make_pair(r, 0));
                auto it2 = move_owners.find(make_pair(r, 2));
                if ((it1 != move_owners.end() && it1->second == player) ||
                    (it2 != move_owners.end() && it2->second == player))
                    player_contributed = true;
            } else if (player_letter == 'U') {
                auto it = move_owners.find(make_pair(r, 1));
                if (it != move_owners.end() && it->second == player)
                    player_contributed = true;
            }
            if (player_contributed) count++;
        }
    }
    
    // Check all vertical sequences
    for (int c = 0; c < 3; c++) {
        if (board[0][c] == 'S' && board[1][c] == 'U' && board[2][c] == 'S') {
            bool player_contributed = false;
            if (player_letter == 'S') {
                auto it1 = move_owners.find(make_pair(0, c));
                auto it2 = move_owners.find(make_pair(2, c));
                if ((it1 != move_owners.end() && it1->second == player) ||
                    (it2 != move_owners.end() && it2->second == player))
                    player_contributed = true;
            } else if (player_letter == 'U') {
                auto it = move_owners.find(make_pair(1, c));
                if (it != move_owners.end() && it->second == player)
                    player_contributed = true;
            }
            if (player_contributed) count++;
        }
    }
    
    // Check main diagonal
    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
        bool player_contributed = false;
        if (player_letter == 'S') {
            auto it1 = move_owners.find(make_pair(0, 0));
            auto it2 = move_owners.find(make_pair(2, 2));
            if ((it1 != move_owners.end() && it1->second == player) ||
                (it2 != move_owners.end() && it2->second == player))
                player_contributed = true;
        } else if (player_letter == 'U') {
            auto it = move_owners.find(make_pair(1, 1));
            if (it != move_owners.end() && it->second == player)
                player_contributed = true;
        }
        if (player_contributed) count++;
    }
    
    // Check anti-diagonal
    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
        bool player_contributed = false;
        if (player_letter == 'S') {
            auto it1 = move_owners.find(make_pair(0, 2));
            auto it2 = move_owners.find(make_pair(2, 0));
            if ((it1 != move_owners.end() && it1->second == player) ||
                (it2 != move_owners.end() && it2->second == player))
                player_contributed = true;
        } else if (player_letter == 'U') {
            auto it = move_owners.find(make_pair(1, 1));
            if (it != move_owners.end() && it->second == player)
                player_contributed = true;
        }
        if (player_contributed) count++;
    }
    
    return count;
}

bool SUSBoard::is_win(Player<char>* player) {
    // Game only ends when board is full
    if (n_moves < 9)
        return false;
    
    // Find opponent
    Player<char>* opponent = nullptr;
    for (auto& pair : player_letters) {
        if (pair.first != player) {
            opponent = pair.first;
            break;
        }
    }
    
    if (!opponent) return false;
    
    // Count sequences created by each player
    int player_count = count_player_sequences(player);
    int opponent_count = count_player_sequences(opponent);
    
    // Player wins if they have more sequences
    return player_count > opponent_count;
}

bool SUSBoard::is_lose(Player<char>* player) {
    // Game only ends when board is full
    if (n_moves < 9)
        return false;
    
    // Find opponent
    Player<char>* opponent = nullptr;
    for (auto& pair : player_letters) {
        if (pair.first != player) {
            opponent = pair.first;
            break;
        }
    }
    
    if (!opponent) return false;
    
    // Count sequences created by each player
    int player_count = count_player_sequences(player);
    int opponent_count = count_player_sequences(opponent);
    
    // Player loses if opponent has more sequences
    return opponent_count > player_count;
}

bool SUSBoard::is_draw(Player<char>* player) {
    if (n_moves < 9)
        return false;
    
    // Find opponent
    Player<char>* opponent = nullptr;
    for (auto& pair : player_letters) {
        if (pair.first != player) {
            opponent = pair.first;
            break;
        }
    }
    
    if (!opponent) return true;
    
    // Draw if both players have the same number of sequences
    int player_count = count_player_sequences(player);
    int opponent_count = count_player_sequences(opponent);
    
    return player_count == opponent_count;
}

bool SUSBoard::game_is_over(Player<char>* player) {
    return n_moves == 9; // Game ends when board is full
}

SUSUI::SUSUI() : UI<char>("Welcome to SUS Game! Form S-U-S sequences to score points!", 3) {}

Player<char>* SUSUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

char SUSUI::choose_player_letter(Player<char>* player) {
    cout << "\n" << player->get_name() << ", choose your letter:\n";
    cout << "1) S\n";
    cout << "2) U\n";
    cout << "Enter choice (1 or 2): ";
    
    int ch;
    while (!(cin >> ch) || (ch != 1 && ch != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    return (ch == 1) ? 'S' : 'U';
}

Move<char>* SUSUI::get_move(Player<char>* player) {
    int x, y;
    char letter;
    
    SUSBoard* board = dynamic_cast<SUSBoard*>(player->get_board_ptr());
    if (!board) {
        // Fallback if cast fails
        return new Move<char>(0, 0, 'S');
    }
    
    // Set current player so board can track move ownership
    board->set_current_player(player);
    
    char player_letter = board->get_player_letter(player);
    
    if (player_letter == '\0') {
        // First move - player must choose their letter
        letter = choose_player_letter(player);
        board->set_player_letter(player, letter);
    } else {
        letter = player_letter; // Player must use the same letter
    }
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " - Place your '" << letter << "'\n";
        cout << "Enter row and col (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        // Random move
        auto matrix = board->get_board_matrix();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (matrix[x][y] != '.');
    }
    
    return new Move<char>(x, y, letter);
}

PlayerType SUSUI::choose_player_type() {
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
