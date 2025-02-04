#include <iostream>
#include <vector>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdlib>
#endif

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printCentered(const string &text) {
    int terminalWidth = 50; // Default width (adjustable)
    int padding = (terminalWidth - text.length()) / 2;
    cout << string(max(padding, 0), ' ') << text << endl;
}

void printBoard(const vector<vector<char>> &board) {
    cout << "\n\n";
    printCentered("     A     B     C   ");
    for (int i = 0; i < 3; i++) {
        printCentered("       |       |       ");
        printCentered(to_string(i + 1) + "  " + board[i][0] + "   |   " + board[i][1] + "   |   " + board[i][2] + "   ");
        printCentered("       |       |       ");
        if (i < 2) printCentered("-------|-------|-------");
    }
    cout << "\n";
}

char checkWinner(const vector<vector<char>> &board) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return board[i][0];  // Rows
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return board[0][i];  // Columns
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return board[0][0];  // Diagonal \
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return board[0][2];  // Diagonal /
    
    for (const auto &row : board)
        for (char cell : row)
            if (cell == ' ') return ' ';  // Game not finished

    return 'D';  // Draw
}

void ticTacToe() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';

    clearScreen();
    cout << "\n\n";
    printCentered("Welcome to Neo's Tic Tac Toe!");
    printCentered("Move using a letter for column and a number for row.");
    printCentered("Example: 'B1' is middle column, top row.");

    while (true) {
        printBoard(board);
        cout << "Player " << currentPlayer << ", enter your move (e.g., B2) or type 'q' to quit: ";
        
        string move;
        cin >> move;
        clearScreen();

        if (move == "q" || move == "Q") {
            printCentered("Thanks for playing! Goodbye!");
            cout << "\n\n";
            break;
        }

        if (move.length() != 2) {
            printCentered("Invalid input. Please use A-C for columns and 1-3 for rows.");
            continue;
        }

        int col = tolower(move[0]) - 'a';
        int row = move[1] - '1';

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printCentered("Invalid input. Please enter A1 to C3.");
            continue;
        }

        if (board[row][col] != ' ') {
            printCentered("Cell already taken. Try again.");
            continue;
        }

        board[row][col] = currentPlayer;
        char winner = checkWinner(board);

        if (winner != ' ') {
            printBoard(board);
            if (winner == 'D') {
                printCentered("It's a draw!");
            } else {
                printCentered("Player " + string(1, winner) + " wins!");
            }
            cout << "\n\n";
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    ticTacToe();
    return 0;
}
