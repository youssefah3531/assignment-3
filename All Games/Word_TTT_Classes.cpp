#include "Word_TTT_Classes.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <algorithm>
#include <cctype>
using namespace std;

void WordBoard::load_dictionary() {
    ifstream file("dic.txt");
    if (!file.is_open()) {
        cerr << "Warning: Could not open dic.txt. Using default words.\n";
        // Add some default 3-letter words
        dictionary.insert("cat");
        dictionary.insert("dog");
        dictionary.insert("bat");
        dictionary.insert("hat");
        dictionary.insert("mat");
        dictionary.insert("rat");
        dictionary.insert("sat");
        dictionary.insert("pat");
        return;
    }
    
    string word;
    while (file >> word) {
        // Convert to lowercase and store
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word.length() == 3) {
            dictionary.insert(word);
        }
    }
    file.close();
}

bool WordBoard::is_valid_word(const string& word) const {
    string lower_word = word;
    transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
    return dictionary.find(lower_word) != dictionary.end();
}

bool WordBoard::has_valid_word() const {
    // Check all horizontal sequences (all 3 cells must be filled)
    for (int r = 0; r < 3; r++) {
        string word;
        for (int c = 0; c < 3; c++) {
            if (board[r][c] != blank_symbol)
                word += tolower(board[r][c]);
        }
        if (word.length() == 3 && is_valid_word(word))
            return true;
    }
    
    // Check all vertical sequences
    for (int c = 0; c < 3; c++) {
        string word;
        for (int r = 0; r < 3; r++) {
            if (board[r][c] != blank_symbol)
                word += tolower(board[r][c]);
        }
        if (word.length() == 3 && is_valid_word(word))
            return true;
    }
    
    // Check main diagonal
    string word;
    for (int i = 0; i < 3; i++) {
        if (board[i][i] != blank_symbol)
            word += tolower(board[i][i]);
    }
    if (word.length() == 3 && is_valid_word(word))
        return true;
    
    // Check anti-diagonal
    word.clear();
    for (int i = 0; i < 3; i++) {
        if (board[i][2-i] != blank_symbol)
            word += tolower(board[i][2-i]);
    }
    if (word.length() == 3 && is_valid_word(word))
        return true;
    
    return false;
}

WordBoard::WordBoard() : Board(3, 3) {
    load_dictionary();
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool WordBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;
    
    if (board[x][y] != blank_symbol)
        return false;
    
    // Validate that mark is a letter
    if (!isalpha(mark))
        return false;

    board[x][y] = toupper(mark);
    n_moves++;
    return true;
}

bool WordBoard::is_win(Player<char>* player) {
    // Check if any valid word has been formed
    return has_valid_word();
}

bool WordBoard::is_draw(Player<char>* player) {
    // Check if board is full and no valid word
    if (n_moves == 9 && !has_valid_word())
        return true;
    return false;
}

bool WordBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

WordUI::WordUI() : UI<char>("Welcome to Word Tic-Tac-Toe!", 3) {}

Player<char>* WordUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* WordUI::get_move(Player<char>* player) {
    int x, y;
    char letter;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() 
             << ") - Form a valid 3-letter word!\n";
        cout << "Enter row (0-2), column (0-2), and letter: ";
        cin >> x >> y >> letter;
        
        // Validate letter input
        if (!isalpha(letter)) {
            cout << "Invalid letter. Using default 'A'.\n";
            letter = 'A';
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        // Random move
        x = rand() % 3;
        y = rand() % 3;
        letter = 'A' + (rand() % 26);
    }
    
    return new Move<char>(x, y, letter);
}

PlayerType WordUI::choose_player_type() {
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

