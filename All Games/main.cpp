/**
 * @file main.cpp
 * @brief Unified entry point for all board games.
 * 
 * This program provides a menu system to select and play different board games.
 */

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// Forward declarations for game main functions
extern int Xo_main();
extern int ٍSUS_main();
extern int TTT4x4_main();
extern int PYRAMID_TTT_main();
extern void TTT5x5_main();
extern int FourInARow_main();
extern int Misere_TTT_main();
extern int Diamond_TTT_main();
extern int Word_TTT_main();

/**
 * @brief Display the main menu and get user's game choice.
 * @return The selected game number or 0 to exit.
 */
int displayMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "    BOARD GAMES COLLECTION\n";
    cout << "========================================\n";
    cout << "1. X-O (3x3 Tic-Tac-Toe)\n";
    cout << "2. Four-in-a-Row (Connect 4)\n";
    cout << "3. 5x5 Tic-Tac-Toe\n";
    cout << "4. Word Tic-Tac-Toe\n";
    cout << "5. Misère Tic-Tac-Toe (Inverse)\n";
    cout << "6. Diamond Tic-Tac-Toe\n";
    cout << "7. 4x4 Tic-Tac-Toe\n";
    cout << "8. Pyramid Tic-Tac-Toe\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
    
    int choice;
    while (!(cin >> choice) || (choice < 0 || choice > 8)) {
        cout << "Invalid choice. Please enter a number between 0 and 8: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

/**
 * @brief Main function that runs the game selection menu.
 * @return 0 on successful execution.
 */
int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    cout << "Welcome to the Board Games Collection!\n";
    
    while (true) {
        int choice = displayMenu();
        
        switch (choice) {
            case 1:
                cout << "\n=== Starting SUS ===\n";
                SUS_main();
                break;
                
            case 2:
                cout << "\n=== Starting Four-in-a-Row ===\n";
                FourInARow_main();
                break;
                
            case 3:
                cout << "\n=== Starting 5x5 Tic-Tac-Toe ===\n";
                TTT5x5_main();
                break;
                
            case 4:
                cout << "\n=== Starting Word Tic-Tac-Toe ===\n";
                Word_TTT_main();
                break;
                
            case 5:
                cout << "\n=== Starting Misère Tic-Tac-Toe ===\n";
                Misere_TTT_main();
                break;
                
            case 6:
                cout << "\n=== Starting Diamond Tic-Tac-Toe ===\n";
                Diamond_TTT_main();
                break;
                
            case 7:
                cout << "\n=== Starting 4x4 Tic-Tac-Toe ===\n";
                TTT4x4_main();
                break;
                
            case 8:
                cout << "\n=== Starting Pyramid Tic-Tac-Toe ===\n";
                PYRAMID_TTT_main();
                break;
                
            case 0:
                cout << "\nThank you for playing! Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        
        cout << "\nPress Enter to return to the main menu...";
        cin.get();
    }
    
    return 0;
}

