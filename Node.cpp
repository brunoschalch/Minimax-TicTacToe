//
// Created by bruno on 9/15/2019.
//

#include "Node.h"

Node *Node::getMinNode() {
    list<Node*>::iterator it;
    int min = +1000;
    Node* minNode;
    for (it = this->children.begin(); it != this->children.end(); ++it) {
        Node* child = *it;
        if (child->score < min) {
            minNode = child;
            min = child->score;
        }
    }
    return minNode;
}

Node *Node::getMaxNode() {
    list<Node*>::iterator it;
    int max = -1000;
    Node* maxNode;
    for (it = this->children.begin(); it != this->children.end(); ++it) {
        Node* child = *it;
        if (child->score > max) {
            maxNode = child;
            max = child->score;
        }
    }
    return maxNode;
}


Node::Node(char inboard[3][3], int score) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = inboard[i][j];
        }
    }
    this->score = score;
}

Node::~Node() {

}

