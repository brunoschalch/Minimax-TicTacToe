//
// Created by bruno on 9/15/2019.
//

#include "Tree.h"

char agent = 'X', human = 'O';

Tree::Tree() {

}

Tree::~Tree() {

}

int Tree::max(int a, int b) {
    return a > b ? a : b;
}

int Tree::min(int a, int b) {
    return a < b ? a : b;
}

bool Tree::tie(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}

bool Tree::checkWinner(char board[3][3], char player) {
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
    return board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == player
           || (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == player);

}

int Tree::assignValues(char board[3][3]) {
    if (checkWinner(board, agent)) {
        return 10;
    } else if (checkWinner(board, human)) {
        return -10;
    } else {
        return 0;
    }
}

int Tree::minimax(char board[3][3], int depth, bool isMax, Node* parent) {
    int score = assignValues(board);
    Node* currentNode = new Node(board, score);
    parent->children.push_back(currentNode);
  //  cout << "stuff called" << endl;

    // If game is settled return.
    if (score == 10 || score == -10) {

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
                    best = max(best, minimax(board, depth + 1, !isMax, currentNode));
                } else {
                    best = min(best, minimax(board, depth + 1, !isMax, currentNode));
                }
                // Undo the move because C++ is pass by reference.
                board[i][j] = 0;
            }
        }
    }
    currentNode->score = best;
    return best;
}

void Tree::generateMinimaxTree() {
    char board[3][3] =
            {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
            };
    char player = agent;
    this->root = new Node(board, 0);
    minimax(board, 0 , player==agent,  root);
}




