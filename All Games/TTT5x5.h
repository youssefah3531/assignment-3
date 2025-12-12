#ifndef TTT5X5_H
#define TTT5X5_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Move {
public:
    int row, col;
    char symbol;
    Move(int r = 0, int c = 0, char s = '-') : row(r), col(c), symbol(s) {}
};

class Board {
private:
    char board[5][5];
    int move_count; // number of applied moves

public:
    Board() {
        reset();
    }

    void reset() {
        move_count = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                board[i][j] = '-';
    }

    bool isValidMove(int r, int c) const {
        return (r >= 0 && r < 5 && c >= 0 && c < 5 && board[r][c] == '-');
    }

    void applyMove(const Move& m) {
        if (isValidMove(m.row, m.col)) {
            board[m.row][m.col] = m.symbol;
            ++move_count;
        }
    }

    void print() const {
        cout << "\n   0 1 2 3 4\n";
        cout << "  -------------\n";
        for (int i = 0; i < 5; i++) {
            cout << i << " | ";
            for (int j = 0; j < 5; j++) {
                cout << board[i][j] << ' ';
            }
            cout << "|\n";
        }
        cout << "  -------------\n";
    }

    // Return winning symbol ('X' or 'O') or '-' for no straight-line winner
    char checkWinner() const {
        // Rows
        for (int i = 0; i < 5; i++) {
            char first = board[i][0];
            if (first == '-') continue;
            bool same = true;
            for (int j = 1; j < 5; j++)
                if (board[i][j] != first) { same = false; break; }
            if (same) return first;
        }

        // Columns
        for (int j = 0; j < 5; j++) {
            char first = board[0][j];
            if (first == '-') continue;
            bool same = true;
            for (int i = 1; i < 5; i++)
                if (board[i][j] != first) { same = false; break; }
            if (same) return first;
        }

        // Main diagonal
        char first = board[0][0];
        if (first != '-') {
            bool diag1 = true;
            for (int i = 1; i < 5; i++)
                if (board[i][i] != first) { diag1 = false; break; }
            if (diag1) return first;
        }

        // Anti-diagonal
        first = board[0][4];
        if (first != '-') {
            bool diag2 = true;
            for (int i = 1; i < 5; i++)
                if (board[i][4 - i] != first) { diag2 = false; break; }
            if (diag2) return first;
        }

        return '-';
    }

    bool isFull() const {
        return (move_count >= 25);
    }

    int get_move_count() const {
        return move_count;
    }

    // Count how many times a symbol appears ('X' or 'O')
    int count_symbol(char sym) const {
        int cnt = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                if (board[i][j] == sym) ++cnt;
        return cnt;
    }
};

class Player {
public:
    string name;
    char symbol;
    bool isBot;

    Player(const string& n = "Player", char s = 'X', bool bot = false)
        : name(n), symbol(s), isBot(bot) {}

    // Return a Move (for human or bot)
    Move getMove(const Board& b) {
        if (!isBot) {
            int r, c;
            while (true) {
                cout << name << " (" << symbol << ") enter row and col (e.g. 1 2): ";
                if (cin >> r >> c) {
                    if (b.isValidMove(r, c))
                        return Move(r, c, symbol);
                    else
                        cout << "That cell is not valid or already occupied. Try again.\n";
                } else {
                    // Bad input (not integers)
                    cout << "Invalid input. Please enter two integers separated by space.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }

        // Simple bot: choose the first available cell (top-left -> bottom-right)
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (b.isValidMove(i, j))
                    return Move(i, j, symbol);

        // Should not reach here if called only when moves remain
        return Move(0, 0, symbol);
    }
};

class GameManager {
private:
    Board board;
    Player* p1;
    Player* p2;

public:
    GameManager(Player* a, Player* b) : p1(a), p2(b) {}

    void play() {
        board.reset();
        Player* current = p1;

        while (true) {
            board.print();
            Move m = current->getMove(board);

            while (!board.isValidMove(m.row, m.col)) {
                cout << "Invalid move! Try again.\n";
                m = current->getMove(board);
            }

            board.applyMove(m);

            // If there is a straight-line winner (row/col/diag), immediate win
            char straightWinner = board.checkWinner();
            if (straightWinner != '-') {
                board.print();
                cout << "\n*** " << current->name << " wins! (" << straightWinner << ") ***\n";
                return;
            }

            // If we've reached 24 moves (only one cell left), stop per rule
            if (board.get_move_count() >= 24) {
                board.print();
                int xCount = board.count_symbol('X');
                int oCount = board.count_symbol('O');
                cout << "\nOnly one square remains empty. Final counts: X=" << xCount << " O=" << oCount << "\n";
                if (xCount > oCount) {
                    cout << "*** " << (p1->symbol == 'X' ? p1->name : p2->name) << " (X) wins by majority! ***\n";
                } else if (oCount > xCount) {
                    cout << "*** " << (p1->symbol == 'O' ? p1->name : p2->name) << " (O) wins by majority! ***\n";
                } else {
                    cout << "--- DRAW ---\n";
                }
                return;
            }

            // Normal full-board draw (shouldn't be reached because we stop at 24,
            // but kept for safety if rules change)
            if (board.isFull()) {
                board.print();
                cout << "\n--- DRAW (board full) ---\n";
                return;
            }

            // switch player
            current = (current == p1 ? p2 : p1);
        }
    }
};

#endif // TTT5X5_H

