//
// Created by bruno on 9/15/2019.
//

#ifndef TICTACTOEMINIMAX_NODE_H
#define TICTACTOEMINIMAX_NODE_H
#include <list>
using namespace std;

class Node {

public:
    Node(char inboard[3][3], int score);
    ~Node();
    Node* getMaxNode();
    Node* getMinNode();
    void addNode(Node* node);
    char board[3][3];
    int score;
    list<Node*> children;

    void copyBoard();
};


#endif //TICTACTOEMINIMAX_NODE_H
