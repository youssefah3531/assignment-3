#pragma once
#ifndef TTT4X4_CLASSES_H
#define TTT4X4_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <cmath> 
using namespace std;

//Stores source (src_x, src_y) and destination (x, y)
class Move4x4 : public Move<char> {
private:
    int src_x;
    int src_y;

public:
    Move4x4(int sx, int sy, int dx, int dy, char sym) : Move<char>(dx, dy, sym), src_x(sx), src_y(sy) {}

    int get_src_x() const { return src_x; }
    int get_src_y() const { return src_y; }
};

//Board
class TTT4x4Board : public Board<char> {
private:
    char blank = '.';
    void init_board_config();

public:
    TTT4x4Board();

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>*) override { return false; }

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;
};

//UI
class TTT4x4UI : public UI<char> {
public:
    TTT4x4UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;

    void display_board_matrix(const vector<vector<char>>& matrix) const ;

    PlayerType choose_player_type();
};

//Smart AI
class SmartAI_TTT4x4 {
public:
    //@brief Finds a valid moves for the AI
    Move4x4* find_best_move(TTT4x4Board* board, char symbol);
};

#endif

