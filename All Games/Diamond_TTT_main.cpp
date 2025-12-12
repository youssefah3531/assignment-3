#include "Diamond_TTT_Classes.h"
#include <ctime>
#include <limits>
#include <iostream>
#include <string>
using namespace std;

int Diamond_TTT_main() {
    srand(time(0));

    DiamondUI* ui = new DiamondUI();

    cout << "\n--- Setup Player X ---\n";
    PlayerType typeX = ui->choose_player_type();
    string nameX;
    if (typeX == PlayerType::HUMAN) {
        cout << "Enter name for Player X: ";
        getline(cin >> ws, nameX);
    }
    else {
        nameX = "Computer X";
    }

    cout << "\n--- Setup Player O ---\n";
    PlayerType typeO = ui->choose_player_type();
    string nameO;
    if (typeO == PlayerType::HUMAN) {
        cout << "Enter name for Player O: ";
        getline(cin >> ws, nameO);
    }
    else {
        nameO = "Computer O";
    }

    Player<char>* pX = ui->create_player(nameX, 'X', typeX);
    Player<char>* pO = ui->create_player(nameO, 'O', typeO);

    Player<char>* players[2] = { pX, pO };

    DiamondBoard* board = new DiamondBoard();

    GameManager<char> gm(board, players, ui);
    gm.run();

    delete board; delete pX; delete pO; delete ui;

    return 0;
}

