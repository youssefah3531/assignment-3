#include "SUS_Classes.h"
#include <ctime>
#include <limits>
#include <iostream>
#include <string>
using namespace std;

int SUS_main() {
    srand(time(0));

    SUSUI* ui = new SUSUI();
    SUSBoard* board = new SUSBoard();

    cout << "\n--- Setup Player 1 ---\n";
    PlayerType type1 = ui->choose_player_type();
    string name1;
    if (type1 == PlayerType::HUMAN) {
        cout << "Enter name for Player 1: ";
        getline(cin >> ws, name1);
    }
    else {
        name1 = "Computer 1";
    }

    cout << "\n--- Setup Player 2 ---\n";
    PlayerType type2 = ui->choose_player_type();
    string name2;
    if (type2 == PlayerType::HUMAN) {
        cout << "Enter name for Player 2: ";
        getline(cin >> ws, name2);
    }
    else {
        name2 = "Computer 2";
    }

    Player<char>* p1 = ui->create_player(name1, '1', type1);
    Player<char>* p2 = ui->create_player(name2, '2', type2);

    Player<char>* players[2] = { p1, p2 };
    
    // Set board pointer before game starts
    p1->set_board_ptr(board);
    p2->set_board_ptr(board);

    GameManager<char> gm(board, players, ui);
    gm.run();
    
    // Display final scores after game ends
    if (board->game_is_over(p1)) {
        int p1_sequences = board->get_player_sequence_count(p1);
        int p2_sequences = board->get_player_sequence_count(p2);
        int total_sequences = board->get_total_sequences();
        
        cout << "\n=== Final Scores ===\n";
        cout << p1->get_name() << " created " << p1_sequences << " S-U-S sequence(s)\n";
        cout << p2->get_name() << " created " << p2_sequences << " S-U-S sequence(s)\n";
        cout << "Total S-U-S sequences on board: " << total_sequences << "\n";
    }

    delete board; delete p1; delete p2; delete ui;

    return 0;
}

