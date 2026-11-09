#include "BST.h"
#include <iostream>

BST::BST() {
    rootIndex = -1;
}

int BST::insert(int currentIndex, int value) {
    if (currentIndex == -1) {
        tree.push_back(Node(value));
        return (tree.size()) - 1;
    }

    if (value < tree[currentIndex].value) {
        int nextLeft = insert(tree[currentIndex].left, value);
        tree[currentIndex].left = nextLeft;
    } else if (value > tree[currentIndex].value) {
        int nextRight = insert(tree[currentIndex].right, value);
        tree[currentIndex].right = nextRight;
    }

    return currentIndex;
}

void BST::addNode(int value) {
    rootIndex = insert(rootIndex, value);
}

void BST::show() {
    for (size_t i = 0; i < tree.size(); i++) {
        std::cout << tree[i].value << " ";
    }
    std::cout << std::endl;
}

void BST::removeNode(int value)
{
    int currentIndex = rootIndex;
    int parentIndex = -1;

    while (currentIndex != -1 && tree[currentIndex].value != value) {
        parentIndex = currentIndex;

        if (value < tree[currentIndex].value) {
            currentIndex = tree[currentIndex].left;
        } else {
            currentIndex = tree[currentIndex].right;
        }
    }

    if (currentIndex == -1) {
        return;
    }

    if (tree[currentIndex].left != -1 &&
        tree[currentIndex].right != -1) {

        int successorParent = currentIndex;
        int successorIndex = tree[currentIndex].right;

        while (tree[successorIndex].left != -1) {
            successorParent = successorIndex;
            successorIndex = tree[successorIndex].left;
        }

        tree[currentIndex].value = tree[successorIndex].value;

        parentIndex = successorParent;
        currentIndex = successorIndex;
    }

    const int childIndex = tree[currentIndex].left != -1
        ? tree[currentIndex].left
        : tree[currentIndex].right;

    if (parentIndex == -1) {
        rootIndex = childIndex;
    } else if (tree[parentIndex].left == currentIndex) {
        tree[parentIndex].left = childIndex;
    } else {
        tree[parentIndex].right = childIndex;
    }

    tree.erase(tree.begin() + currentIndex);

    if (rootIndex > currentIndex) {
        --rootIndex;
    }

    for (Node& node : tree) {
        if (node.left > currentIndex) {
            --node.left;
        }

        if (node.right > currentIndex) {
            --node.right;
        }
    }
}

void BST::removeTree()
{
    tree.clear();
    rootIndex = -1;
}

bool BST::findElement(int value) const {
    int currentIndex = rootIndex;

    while (currentIndex != -1) {
        if (value == tree[currentIndex].value) {
            return true;
        }

        if (value < tree[currentIndex].value) {
            currentIndex = tree[currentIndex].left;
        } else {
            currentIndex = tree[currentIndex].right;
        }
    }

    return false;
}
std::vector<int> BST::findPath(int value) const {
    std::vector<int> path;
    int currentIndex = rootIndex;

    while (currentIndex != -1) {
        const Node& node = tree[currentIndex];
        path.push_back(node.value);

        if (value == node.value) {
            return path;
        }

        currentIndex = value < node.value ? node.left : node.right;
    }

    return {};
}