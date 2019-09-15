#include <stdlib.h>
#include <iostream>

using namespace std;

struct Position {
    int i, j;
};

char agent = 'X', human = 'O';

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                cout << '_';
            } else {
                cout << board[i][j];
            }

            cout << '|';

        }

        cout << endl;
    }
}

bool tie(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}

bool checkWinner(char board[3][3], char player) {
    // Horizontal.
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2] && board[row][0] == player) {
            return true;
        }
    }
    // Vertical.
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col] && board[0][col] == player) {
            return true;
        }
    }
    // Diagonal.
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == player
        || (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == player)) {
        return true;
    }

    return false;
}

int assignValues(char board[3][3]) {
    if (checkWinner(board, agent)) {
        return 10;
    } else if (checkWinner(board, human)) {
        return -10;
    } else {
        return 0;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[3][3], int depth, bool isMax) {
    int score = assignValues(board);

    // If game is settled return.
    if (score == 10 || score == -10) {
        //cout << "-----" << endl;
        //cout << "settled " << (isMax ? agent : human) << ", " << score << endl;
        //printBoard(board);
        return score;
    }


    // Tie equals utility of 0.
    if (tie(board))
        return 0;

    int best;
    char turn;
    // AIs turn.
    if (isMax) {
        best = -1000;
        turn = agent;
    } else {
        best = 1000;
        turn = human;
    }

    // Try all moves.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Only try a move if cell is empty.
            if (board[i][j] == 0) {
                // Make the move
                board[i][j] = turn;
                // Call minimax to assign a score to this move.
                if (isMax) {
                    best = max(best, minimax(board, depth + 1, !isMax));
                } else {
                    best = min(best, minimax(board, depth + 1, !isMax));
                }
                // Undo the move because C++ is pass by reference.
                board[i][j] = 0;
            }
        }
    }
    return best;
}

// This will return the best possible move for the agent
Position calculateNextMove(char board[3][3], char player) {
    int bestVal = -1000;
    Position bestMove;
    bestMove.i = -1;
    bestMove.j = -1;

    // Calculate minimax score for all empty cells and return the best.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                board[i][j] = player;
                // Now we check all possible games the human can play (isMax=false), and the AIs moves recursively.
                int moveVal = minimax(board, 0, player != agent);
                if (player == human) {
                    moveVal *= -1;
                }
                // Undo
                board[i][j] = 0;
                if (moveVal > bestVal) {
                    bestMove.i = i;
                    bestMove.j = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    cout << "The best position's score is: " << bestVal << '\n';
    return bestMove;
}


int main() {
    char board[3][3] =
            {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
            };

    // Initial player;
    char currentPlayer = agent;
    for (int i = 0; i < 9; i++) {
        Position bestMove = calculateNextMove(board, currentPlayer);

        cout << "The recommended next move for " << currentPlayer << " is :";
        cout << "COL: " << bestMove.j << ", ROW: " << bestMove.i << endl;

        board[bestMove.i][bestMove.j] = currentPlayer;

        printBoard(board);
        currentPlayer = currentPlayer == agent ? human : agent;
    }
    return 0;
} 