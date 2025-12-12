/**
 * @file Misere_TTT_Classes.h
 * @brief Defines the Misère (Inverse) Tic-Tac-Toe game classes.
 * 
 * In Misère Tic-Tac-Toe, players try to avoid getting three-in-a-row.
 * A player loses if they complete a line of three of their own marks.
 */

#ifndef MISERE_TTT_CLASSES_H
#define MISERE_TTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class MisereBoard
 * @brief Board for Misère (Inverse) Tic-Tac-Toe game.
 * 
 * Players lose if they get three-in-a-row of their own symbol.
 */
class MisereBoard : public Board<char> {
private:
    char blank_symbol = '.';

public:
    /**
     * @brief Construct a 3x3 Misère board.
     */
    MisereBoard();

    /**
     * @brief Update the board with a move.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won (has NOT completed three-in-a-row).
     * In Misère, winning means the opponent lost.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost (completed three-in-a-row).
     */
    bool is_lose(Player<char>* player) override;

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
 * @class MisereUI
 * @brief UI for Misère Tic-Tac-Toe game.
 */
class MisereUI : public UI<char> {
public:
    /**
     * @brief Construct Misère UI.
     */
    MisereUI();

    /**
     * @brief Create a player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get move from player.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Choose player type.
     */
    PlayerType choose_player_type();
};

#endif // MISERE_TTT_CLASSES_H

