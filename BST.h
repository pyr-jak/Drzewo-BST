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

    int insert(int currentIndex, int value);

public:
    BST();
    void addNode(int value);
    void removeNode(int value);
    void removeTree();
    void show();
};

#endif