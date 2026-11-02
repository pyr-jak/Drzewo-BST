#ifndef BST_H
#define BST_H

#include <vector>

struct Node {
    int value;
    int left;
    int right;

    Node(int value) : value(value), left(-1), right(-1) {}
};

class BST {
private:
    std::vector<Node> tree;
    int rootIndex;

    // Tutaj musi być int, a nie void:
    int insert(int currentIndex, int value);

public:
    BST();
    void addNode(int value);
    void show();
};

#endif