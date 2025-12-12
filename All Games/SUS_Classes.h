/**
 * @file SUS_Classes.h
 * @brief Defines the SUS game classes.
 * 
 * SUS: A game on a 3x3 grid where players place "S" or "U" to form "S-U-S" sequences.
 * The player with the most sequences wins when the board is full.
 */

#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
#include <map>
#include <utility>
using namespace std;

/**
 * @class SUSBoard
 * @brief Board for SUS game.
 * 
 * Players place "S" or "U" letters. Each player must use the same letter each turn.
 * Players score points for each "S-U-S" sequence they create.
 */
class SUSBoard : public Board<char> {
private:
    char blank_symbol = '.';
    map<Player<char>*, char> player_letters; ///< Tracks which letter each player uses
    map<pair<int, int>, Player<char>*> move_owners; ///< Tracks which player placed each cell
    Player<char>* current_player = nullptr; ///< Current player making a move
    
    /**
     * @brief Count how many "S-U-S" sequences exist on the board.
     */
    int count_SUS_sequences() const;
    
    /**
     * @brief Count how many "S-U-S" sequences a specific player created.
     */
    int count_player_sequences(Player<char>* player) const;

public:
    /**
     * @brief Construct a 3x3 SUS board.
     */
    SUSBoard();

    /**
     * @brief Update the board with a move (place S or U).
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won (has more SUS sequences than opponent).
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost (opponent has more sequences when board is full).
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw (tie in SUS sequences).
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over (board is full).
     */
    bool game_is_over(Player<char>* player) override;
    
    /**
     * @brief Get the letter assigned to a player.
     */
    char get_player_letter(Player<char>* player) const;
    
    /**
     * @brief Set the letter for a player (must be called before first move).
     */
    void set_player_letter(Player<char>* player, char letter);
    
    /**
     * @brief Set the current player (called before update_board to track move ownership).
     */
    void set_current_player(Player<char>* player);
    
    /**
     * @brief Get count of sequences for a player (public access).
     */
    int get_player_sequence_count(Player<char>* player) const {
        return count_player_sequences(player);
    }
    
    /**
     * @brief Get total sequences on board (public access).
     */
    int get_total_sequences() const {
        return count_SUS_sequences();
    }
};

/**
 * @class SUSUI
 * @brief UI for SUS game.
 */
class SUSUI : public UI<char> {
public:
    /**
     * @brief Construct SUS UI.
     */
    SUSUI();

    /**
     * @brief Create a player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get move from player (position and letter S or U).
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Choose player type.
     */
    PlayerType choose_player_type();
    
    /**
     * @brief Choose which letter (S or U) the player will use.
     */
    char choose_player_letter(Player<char>* player);
};

#endif // SUS_CLASSES_H

