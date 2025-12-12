#include <iostream>
#include <string>
#include <limits>
#include "TTT5x5.h"

using namespace std;

void TTT5x5_main() {
    string name1, name2;
    int type1 = 1, type2 = 1;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    if (name1.empty()) name1 = "Player1";

    while (true) {
        cout << "1 = Human, 2 = Bot for Player 1: ";
        if (cin >> type1 && (type1 == 1 || type1 == 2)) break;
        cout << "Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Player 2 name: ";
    getline(cin, name2);
    if (name2.empty()) name2 = "Player2";

    while (true) {
        cout << "1 = Human, 2 = Bot for Player 2: ";
        if (cin >> type2 && (type2 == 1 || type2 == 2)) break;
        cout << "Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Player p1(name1, 'X', type1 == 2);
    Player p2(name2, 'O', type2 == 2);

    GameManager game(&p1, &p2);
    game.play();
}

