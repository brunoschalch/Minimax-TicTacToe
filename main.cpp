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

            cout << '|';

        }

        cout << endl;
    }
}

void DFS(Node *root, int depth) {
    cout << " printing level " << depth << endl;
    cout << " score: " << root->score << endl;
    printBoard(root->board);

    if (root->children.size() != 0)
        DFS(*(root->children.begin()), depth + 1);
}

void printMaxMinTree(Node *root, bool isMax, int count) {

    if (root->children.size() != 0) {
        Node *maxiMinNode = isMax ? root->getMaxNode() : root->getMinNode();
        cout << "printing level: " << count << " (" << (isMax ? "max" : "min") << ")" << endl;

        printBoard(maxiMinNode->board);

        printMaxMinTree(maxiMinNode, !isMax, count + 1);
    }

}

int main() {
    char board[3][3] =
            {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
            };


    Tree *tree = new Tree();
    tree->generateMinimaxTree();

    cout << "now tree coming" << endl;

    Node *child = *(tree->root->children.begin());

    list<Node *>::iterator it;
    for (it = child->children.begin(); it != child->children.end(); ++it) {
        Node *childe = *it;

        cout << "DFS begins (printing leftmost branch of each child)" << endl;
        DFS(childe, 0);
        cout << endl;
        cout << endl;
    }


    printMaxMinTree(child, true, 0);
    return 0;
} 