#include "BST.h"
#include <iostream>

void BST::insert(int currentIndex, int value) {
    if (currentIndex == -1) {
        tree.push_back(Node(value));
        currentIndex = tree.size() - 1;
        return;
    }
    if (value < tree[currentIndex].value) {
        insert(tree[currentIndex].left, value);
    }
    if (value > tree[currentIndex].value) {
        insert(tree[currentIndex].right, value);
    }
}

void BST::addNode(int value) {
    insert(rootIndex, value);
}

void BST::show()
{
    for (int i = 0; i < tree.size(); i++) {
        std::cout << tree[i].value << " ";
    }
    std::cout << std::endl;
}

BST::BST()
{
    rootIndex = -1;
}
