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

public:
    BST();
    void insert(int currentIndex, int val);
    void show();
    void addNode(int value);
};

#endif