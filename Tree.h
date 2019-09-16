//
// Created by bruno on 9/15/2019.
//

#ifndef TICTACTOEMINIMAX_TREE_H
#define TICTACTOEMINIMAX_TREE_H


#include "Node.h"
struct Position {
    int i, j;
};

class Tree {
public:
    Tree();
    ~Tree();

    Node* root;
    bool checkWinner(char board[3][3], char player);

    void generateMinimaxTree();

    int max(int a, int b);

    int min(int a, int b);

    bool tie(char board[3][3]);

    int assignValues(char board[3][3]);

    int minimax(char board[3][3], int depth, bool isMax, Node* parent);
    Position calculateNextMove(char board[3][3], char player);
};


#endif //TICTACTOEMINIMAX_TREE_H
