#include <iostream>
#include <vector>
#include <limits>
using namespace std;

char board[3][3]; 
char currentPlayer; 

void resetBoard() {
    char pos = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = pos++;
        }
    }
    currentPlayer = 'X';
}

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return true;
    }
    // Diagonals
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;

    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void playerMove() {
    int choice;
    while (true) {
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 9) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 9.\n";
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
            break;
        } else {
            cout << "Cell already taken! Try again.\n";
        }
    }
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void playGame() {
    resetBoard();
    bool gameOver = false;

    while (!gameOver) {
        displayBoard();
        playerMove();

        if (checkWin()) {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } else if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            gameOver = true;
        } else {
            switchPlayer();
        }
    }
}

int main() {
    int choice;
    bool exitGame = false;

    while (!exitGame) {
        cout << "\n===== TIC-TAC-TOE MENU =====\n";
        cout << "1. Play Game\n";
        cout << "2. Rules\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                cout << "\nRules:\n";
                cout << "1. The board has 9 cells numbered 1-9.\n";
                cout << "2. Player X goes first, then players alternate.\n";
                cout << "3. First to get 3 in a row (horizontal, vertical, diagonal) wins.\n";
                cout << "4. If the board fills with no winner, it's a draw.\n\n";
                break;
            case 3:
                cout << "Exiting game. Goodbye!\n";
                exitGame = true;
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        if (!exitGame) {
            char again;
            cout << "Do you want to return to menu? (y/n): ";
            cin >> again;
            if (again == 'n' || again == 'N') {
                cout << "Exiting game. Goodbye!\n";
                exitGame = true;
            }
        }
    }
    return 0;
}
