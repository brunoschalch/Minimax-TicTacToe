#include <stdlib.h>
#include <iostream>
#include "Tree.h"

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                cout << '_';
            } else {
                cout << board[i][j];
            }
            if (j<2) {
                cout << '|';
            }
        }
        cout << endl;
    }
}

void DFS(Node *root, int depth) {
    cout << "DFS: Printing level " << depth << endl;
    cout << "DFS: Score: " << root->score << endl;
    printBoard(root->board);
    if (root->children.size() != 0)
        DFS(*(root->children.begin()), depth + 1);
}

void printMaxMinTree(Node *root, bool isMax, int count) {
    if (root->children.size() != 0) {
        Node *maxiMinNode = isMax ? root->getMaxNode() : root->getMinNode();
        cout << "Printing level: " << count << " (" << (isMax ? "X - max" : "O - min") << ")" << endl;
        cout << "Score: " << maxiMinNode->score << endl;
        printBoard(maxiMinNode->board);
        printMaxMinTree(maxiMinNode, !isMax, count + 1);
    }
}

int main() {
    Tree *tree = new Tree();
    tree->generateMinimaxTree();
    Node *child = *(tree->root->children.begin());
    list<Node *>::iterator it;
    for (it = child->children.begin(); it != child->children.end(); ++it) {
        Node *current = *it;
        cout << "DFS begins (printing leftmost branch of each child)" << endl;
        DFS(current, 0);
        cout << endl;
        cout << endl;
    }

    cout << "---- MINIMAX TREE TRAVERSAL ----" << endl;
    printMaxMinTree(child, true, 0);
    return 0;
} 