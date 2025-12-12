#include "PYRAMID_TTT_Classes.h"
#include <cstdlib>
#include <limits>
using namespace std;

//Board implementation
void PyramidBoard::init_wins() {
    winning_triplets.clear();

    winning_triplets.push_back({ 0 * 10 + 2,1 * 10 + 1,2 * 10 + 0 });
    winning_triplets.push_back({ 0 * 10 + 2,1 * 10 + 2,2 * 10 + 2 }); 
    winning_triplets.push_back({ 0 * 10 + 2,1 * 10 + 3,2 * 10 + 4 }); 

    winning_triplets.push_back({ 1 * 10 + 1,1 * 10 + 2,1 * 10 + 3 });
    winning_triplets.push_back({ 2 * 10 + 0,2 * 10 + 1,2 * 10 + 2 });
    winning_triplets.push_back({ 2 * 10 + 1,2 * 10 + 2,2 * 10 + 3 });
    winning_triplets.push_back({ 2 * 10 + 2,2 * 10 + 3,2 * 10 + 4 });
}

PyramidBoard::PyramidBoard() : Board(3, 5) {
    // fill all invalid
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 5; c++)
            board[r][c] = invalid;

    // set valid cells
    board[0][2] = blank;
    board[1][1] = board[1][2] = board[1][3] = blank;
    for (int c = 0; c < 5; c++)
        board[2][c] = blank;

    n_moves = 0;
    init_wins();
}

bool PyramidBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char sym = move->get_symbol();

    if (r < 0 || r >= 3 || c < 0 || c >= 5) return false;
    if (board[r][c] != blank) return false;
    board[r][c] = sym;
    n_moves++;
    return true;
}

bool PyramidBoard::is_win(Player<char>* player) {
    char s = player->get_symbol();
    for (auto& trip : winning_triplets) {
        int a = trip[0], b = trip[1], c = trip[2];
        int ar = a / 10, ac = a % 10, br = b / 10, bc = b % 10, cr = c / 10, cc = c % 10;
        if (board[ar][ac] == s && board[br][bc] == s && board[cr][cc] == s)
            return true;
    }
    return false;
}

bool PyramidBoard::is_draw(Player<char>* player) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 5; c++)
            if (board[r][c] == blank)
                return false;
    return !is_win(player);
}

bool PyramidBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//UI implementation
PyramidUI::PyramidUI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe!", 3) {}

Player<char>* PyramidUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

PlayerType PyramidUI::choose_player_type() {
    cout << "Choose player type:\n1) Human\n2) Smart AI\n";
    int ch; cin >> ch;
    if (ch == 1) return PlayerType::HUMAN;
    return PlayerType::AI;
}

Move<char>* PyramidUI::get_move(Player<char>* player) {
    int r, c;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") turn.\n";
        cout << "Enter row col: ";
        cin >> r >> c;
    }
    else {
        // Smart AI
        SmartAI_Pyramid brain;
        auto p = brain.find_best_move(player->get_board_ptr(), player->get_symbol());
        r = p.first; c = p.second;
    }

    return new Move<char>(r, c, player->get_symbol());
}

void PyramidUI::display_board_matrix(const vector<vector<char>>& M) const {
    cout << "\n      0     1     2     3     4\n";
    cout << "    +-----+-----+-----+-----+-----+\n";
    for (int r = 0; r < 3; r++) {
        cout << "  " << r << " |";
        for (int c = 0; c < 5; c++) {
            cout << "  " << M[r][c] << "  |";
        }
        cout << "\n    +-----+-----+-----+-----+-----+\n";
    }
    cout << endl;
}

// Smart AI simple
pair<int, int> SmartAI_Pyramid::find_best_move(Board<char>* b, char s) {
    auto mat = b->get_board_matrix();
    vector<pair<int, int>> valid;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == '.')
                valid.push_back({ i,j });
    if (valid.empty()) return { 0,0 };
    return valid[rand() % valid.size()];
}

