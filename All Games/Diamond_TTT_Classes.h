/**
 * @file Diamond_TTT_Classes.h
 * @brief Defines the Diamond Tic-Tac-Toe game classes.
 * 
 * A game on a diamond-shaped grid where a player must complete 
 * two lines of marks simultaneously to win (one line of 3 and one line of 4).
 */

#ifndef DIAMOND_TTT_CLASSES_H
#define DIAMOND_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class DiamondBoard
 * @brief Board for Diamond Tic-Tac-Toe game.
 * 
 * 5x5 grid arranged in a diamond shape.
 */
class DiamondBoard : public Board<char> {
private:
    char blank_symbol = '.';
    char invalid = '#';

public:
    /**
     * @brief Check if a cell is valid (part of diamond shape).
     */
    bool is_valid_cell(int r, int c) const;

    /**
     * @brief Check if there's a line of 3 of the given symbol.
     */
    bool has_line_of_3(char sym) const;

    /**
     * @brief Check if there's a line of 4 of the given symbol.
     */
    bool has_line_of_4(char sym) const;

public:
    /**
     * @brief Construct a 5x5 Diamond board.
     */
    DiamondBoard();

    /**
     * @brief Update the board with a move.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won (has both line of 3 and line of 4).
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost.
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Check if game is a draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class DiamondUI
 * @brief UI for Diamond Tic-Tac-Toe game.
 */
class DiamondUI : public UI<char> {
public:
    /**
     * @brief Construct Diamond UI.
     */
    DiamondUI();

    /**
     * @brief Create a player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get move from player.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Display the board with diamond shape.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const;

    /**
     * @brief Choose player type.
     */
    PlayerType choose_player_type();
};

#endif // DIAMOND_TTT_CLASSES_H

