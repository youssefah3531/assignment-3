#include "TTT4x4_Classes.h"
#include <cstdlib>
#include <limits>
#include <ctime>
#include <algorithm>
#include <iomanip>
using namespace std;

// TTT4x4Board Implementation
TTT4x4Board::TTT4x4Board() : Board<char>(4, 4) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            board[r][c] = blank;
        }
    }
    init_board_config();
    n_moves = 0;
}

void TTT4x4Board::init_board_config() {
    board[0][0] = board[3][1] = board[0][2] = board[3][3] = 'X';
    board[3][0] = board[0][1] = board[3][2] = board[0][3] = 'O';
}

bool TTT4x4Board::update_board(Move<char>* move) {
    Move4x4* m = static_cast<Move4x4*>(move);
    if (!m) return false;

    int sx = m->get_src_x();
    int sy = m->get_src_y();
    int dx = m->get_x();
    int dy = m->get_y();
    char sym = m->get_symbol();

    if (sx < 0 || sx >= 4 || sy < 0 || sy >= 4 || dx < 0 || dx >= 4 || dy < 0 || dy >= 4)
        return false;

    if (board[sx][sy] != sym)
        return false;

    if (board[dx][dy] != blank)
        return false;

    int dr = abs(dx - sx);
    int dc = abs(dy - sy);

    if ((dr + dc) != 1)
        return false;

 //Move is valid:
    //Clear the source cell
    board[sx][sy] = blank;
    //Place the symbol in the destination cell
    board[dx][dy] = sym;

    n_moves++;
    return true;
}

bool TTT4x4Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    //Horizontal Check
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 2; c++) {
            if (board[r][c] == s && board[r][c + 1] == s && board[r][c + 2] == s) {
                return true;
            }
        }
    }
    //Vertical Check
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 2; r++) {
            if (board[r][c] == s && board[r + 1][c] == s && board[r + 2][c] == s) {
                return true;
            }
        }
    }
    //Main Diagonals(0,0), (0,1), (1,0), (1,1)
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            if (board[r][c] == s && board[r + 1][c + 1] == s && board[r + 2][c + 2] == s) {
                return true;
            }
        }
    }

    //Anti-Diagonals(0,3), (0,2), (1,3), (1,2)
    for (int r = 0; r < 2; r++) {
        for (int c = 2; c < 4; c++) {
            if (board[r][c] == s && board[r + 1][c - 1] == s && board[r + 2][c - 2] == s) {
                return true;
            }
        }
    }

    return false;
}

bool TTT4x4Board::is_draw(Player<char>* player) {
    return false;
}

bool TTT4x4Board::game_is_over(Player<char>* player) {
    return is_win(player);
}
//UI
TTT4x4UI::TTT4x4UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe!", 4) {}

Player<char>* TTT4x4UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
PlayerType TTT4x4UI::choose_player_type() {
    cout << "Choose player type:\n1) Human\n2) Smart Computer AI\n";
    int ch;

    while (!(cin >> ch) || (ch != 1 && ch != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (ch == 1) return PlayerType::HUMAN;

    return PlayerType::AI;
}

Move<char>* TTT4x4UI::get_move(Player<char>* player) {
    int sr, sc, dr, dc;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") turn.\n";
        cout << "Enter SOURCE row col and DESTINATION row col (e.g., 0 0 1 0): ";

        while (!(cin >> sr >> sc >> dr >> dc) ||
            sr < 0 || sr >= 4 || sc < 0 || sc >= 4 ||
            dr < 0 || dr >= 4 || dc < 0 || dc >= 4)
        {
            cout << "Invalid input or coordinates. Try again (src_r src_c dest_r dest_c): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        //AI logic
        TTT4x4Board* board_ptr = dynamic_cast<TTT4x4Board*>(player->get_board_ptr());

        //Smart AI (finds a random valid move)
        SmartAI_TTT4x4 brain;
        Move4x4* move = brain.find_best_move(board_ptr, player->get_symbol());

        sr = move->get_src_x();
        sc = move->get_src_y();
        dr = move->get_x();
        dc = move->get_y();

        cout << player->get_name() << " plays by moving from (" << sr << ", " << sc << ") to (" << dr << ", " << dc << ")\n";

        return move;
    }
    return new Move4x4(sr, sc, dr, dc, player->get_symbol());
}

void TTT4x4UI::display_board_matrix(const vector<vector<char>>& M) const {
    UI<char>::display_board_matrix(M);
}
//Smart AI(Placeholder)
Move4x4* SmartAI_TTT4x4::find_best_move(TTT4x4Board* b, char s) {
    
    //finds the first valid adjacent move and returns it
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            if (b->get_board_matrix()[r][c] == s) {
                //Check adjacent cells for an empty space
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        //Ensure it's not diagonal or staying put
                        if (abs(dr) + abs(dc) != 1) continue;

                        int nr = r + dr;
                        int nc = c + dc;

                        //Check bounds and if the new position is empty
                        if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4 && b->get_board_matrix()[nr][nc] == '.') {
                            return new Move4x4(r, c, nr, nc, s);
                        }
                    }
                }
            }
        }
    }
    return new Move4x4(0, 0, 0, 0, s);
}

