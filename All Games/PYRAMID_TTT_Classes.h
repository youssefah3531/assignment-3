#pragma once
#ifndef PYRAMID_TTT_CLASSES_H
#define PYRAMID_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
using namespace std;

//Board
class PyramidBoard : public Board<char> {
private:
    char blank = '.';
    char invalid = '#';
    vector<vector<int>> winning_triplets;

    void init_wins();

public:
    PyramidBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

//UI
class PyramidUI : public UI<char> {
public:
    PyramidUI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;

    void display_board_matrix(const vector<vector<char>>& matrix) const ;

    PlayerType choose_player_type();
};

// Smart AI
class SmartAI_Pyramid {
public:
    pair<int, int> find_best_move(Board<char>* board, char symbol);
};

#endif

