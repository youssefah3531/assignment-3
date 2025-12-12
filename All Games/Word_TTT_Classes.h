/**
 * @file Word_TTT_Classes.h
 * @brief Defines the Word Tic-Tac-Toe game classes.
 * 
 * Players place letters on the board to form valid three-letter words.
 * First player to form a valid word wins.
 */

#ifndef WORD_TTT_CLASSES_H
#define WORD_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <set>
#include <string>
using namespace std;

/**
 * @class WordBoard
 * @brief Board for Word Tic-Tac-Toe game.
 * 
 * 3x3 grid where players place letters to form words.
 */
class WordBoard : public Board<char> {
private:
    char blank_symbol = '.';
    set<string> dictionary; ///< Set of valid 3-letter words
    
    /**
     * @brief Load dictionary from dic.txt file.
     */
    void load_dictionary();
    
    /**
     * @brief Check if a word is valid (in dictionary).
     */
    bool is_valid_word(const string& word) const;
    
    /**
     * @brief Check all possible words on the board.
     */
    bool has_valid_word() const;

public:
    /**
     * @brief Construct a 3x3 Word Tic-Tac-Toe board.
     */
    WordBoard();

    /**
     * @brief Update the board with a move (place letter).
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won (formed a valid word).
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
 * @class WordUI
 * @brief UI for Word Tic-Tac-Toe game.
 */
class WordUI : public UI<char> {
public:
    /**
     * @brief Construct Word UI.
     */
    WordUI();

    /**
     * @brief Create a player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get move from player (position and letter).
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Choose player type.
     */
    PlayerType choose_player_type();
};

#endif // WORD_TTT_CLASSES_H

