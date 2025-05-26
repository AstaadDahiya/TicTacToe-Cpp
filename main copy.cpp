#include <iostream>
#include <vector>
#include <limits>
#include <ctime>

using namespace std;

class TicTacToe {
private:
    vector<char> board; // 3x3 grid
    char human;
    char ai;
    bool isComputerMode;

public:
    TicTacToe(bool computerMode = false) : board(9, ' '), isComputerMode(computerMode) {
        human = 'X';
        ai = 'O';
    }

    void displayBoard() {
        cout << "\n";
        cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
        cout << "---+---+---\n";
        cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
        cout << "---+---+---\n";
        cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
        cout << "\n";
    }

    bool isValidMove(int pos) {
        return pos >= 1 && pos <= 9 && board[pos - 1] == ' ';
    }

    void makeMove(int pos, char player) {
        if (isValidMove(pos))
            board[pos - 1] = player;
    }

    void undoMove(int pos) {
        board[pos - 1] = ' ';
    }

    bool checkWin(char player) {
        int wins[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8}, // rows
            {0,3,6}, {1,4,7}, {2,5,8}, // cols
            {0,4,8}, {2,4,6}           // diags
        };
        for (auto & win : wins)
            if (board[win[0]] == player &&
                board[win[1]] == player &&
                board[win[2]] == player)
                return true;
        return false;
    }

    bool checkDraw() {
        for (char cell : board)
            if (cell == ' ') return false;
        return true;
    }

    // Minimax function
    int minimax(bool isMaximizing) {
        if (checkWin(ai)) return 10;
        if (checkWin(human)) return -10;
        if (checkDraw()) return 0;

        if (isMaximizing) {
            int bestScore = -1000;
            for (int i = 0; i < 9; ++i) {
                if (board[i] == ' ') {
                    board[i] = ai;
                    int score = minimax(false);
                    undoMove(i + 1);
                    bestScore = max(score, bestScore);
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (int i = 0; i < 9; ++i) {
                if (board[i] == ' ') {
                    board[i] = human;
                    int score = minimax(true);
                    undoMove(i + 1);
                    bestScore = min(score, bestScore);
                }
            }
            return bestScore;
        }
    }

    // Get best move using Minimax
    int getBestMove() {
        int bestScore = -1000;
        int move = -1;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = ai;
                int score = minimax(false);
                undoMove(i + 1);
                if (score > bestScore) {
                    bestScore = score;
                    move = i;
                }
            }
        }
        return move + 1; // convert to 1-based index
    }

    void resetGame() {
        board.assign(9, ' ');
    }

    void playGame() {
        bool playing = true;
        while (playing) {
            displayBoard();

            int move;
            if (isComputerMode && boardIsFull()) {
                cout << "It's a draw!\n";
                break;
            }

            if (isComputerMode && getCurrentPlayer() == ai) {
                move = getBestMove();
                cout << "AI chooses position " << move << "\n";
            } else {
                cout << "Player " << getCurrentPlayer() << ", enter your move (1-9): ";
                cin >> move;
                while (!cin || !isValidMove(move)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Try again: ";
                    cin >> move;
                }
            }

            makeMove(move, getCurrentPlayer());

            if (checkWin(getCurrentPlayer())) {
                displayBoard();
                if (getCurrentPlayer() == ai)
                    cout << "AI (O) wins!\n";
                else
                    cout << "Player " << getCurrentPlayer() << " wins!\n";
                break;
            } else if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!\n";
                break;
            }

            switchPlayer();
        }

        char replay;
        cout << "Do you want to play again? (y/n): ";
        cin >> replay;
        if (replay == 'y' || replay == 'Y') {
            resetGame();
            playGame(); // Recursive call to restart game
        } else {
            cout << "Thanks for playing!\n";
        }
    }

    bool boardIsFull() {
        for (char c : board) if (c == ' ') return false;
        return true;
    }

    char getCurrentPlayer() {
        int xCount = 0, oCount = 0;
        for (char c : board) {
            if (c == 'X') xCount++;
            if (c == 'O') oCount++;
        }
        return (xCount == oCount) ? 'X' : 'O';
    }

    void switchPlayer() {
        // Handled automatically based on turn count
    }
};

int main() {
    cout << "Welcome to Tic-Tac-Toe with AI!\n";
    cout << "Choose game mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs AI (Unbeatable)\n";
    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Try again: ";
        cin >> choice;
    }

    TicTacToe game(choice == 2);
    game.playGame();

    return 0;
}