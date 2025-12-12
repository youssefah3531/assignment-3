/**
 * @file FourInARow_Classes.h
 * @brief Defines the Four-in-a-Row (Connect 4) game classes.
 * 
 * Players drop pieces into columns, trying to get four in a row.
 */

#ifndef FOUR_IN_A_ROW_CLASSES_H
#define FOUR_IN_A_ROW_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class FourInARowBoard
 * @brief Board for Four-in-a-Row game.
 * 
 * Standard Connect 4 style game on a 6x7 board.
 */
class FourInARowBoard : public Board<char> {
private:
    char blank_symbol = '.';
    static const int ROWS = 6;
    static const int COLS = 7;

public:
    /**
     * @brief Construct a 6x7 Four-in-a-Row board.
     */
    FourInARowBoard();

    /**
     * @brief Update the board with a move (drop piece in column).
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won (four in a row).
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

    /**
     * @brief Get the row where a piece would land in a column.
     */
    int get_drop_row(int col) const;
};

/**
 * @class FourInARowUI
 * @brief UI for Four-in-a-Row game.
 */
class FourInARowUI : public UI<char> {
public:
    /**
     * @brief Construct Four-in-a-Row UI.
     */
    FourInARowUI();

    /**
     * @brief Create a player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get move from player (column to drop piece).
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Choose player type.
     */
    PlayerType choose_player_type();
};

#endif // FOUR_IN_A_ROW_CLASSES_H

