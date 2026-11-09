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

bool BST::addNode(int value) {
    const auto sizeBefore = tree.size();
    rootIndex = insert(rootIndex, value);
    return tree.size() != sizeBefore;
}

void BST::show() {
    for (size_t i = 0; i < tree.size(); i++) {
        std::cout << tree[i].value << " ";
    }
    std::cout << std::endl;
}

bool BST::removeNode(int value)
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
        return false;
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

    return true;
}

void BST::removeTree()
{
    tree.clear();
    rootIndex = -1;
}

void BST::preorderHelper(int currentIndex) {
    if (currentIndex == -1) {
        return;
    }
    std::cout << tree[currentIndex].value << " ";
    preorderHelper(tree[currentIndex].left);
    preorderHelper(tree[currentIndex].right);
}

void BST::preorder() {
    std::cout << "Preorder: ";
    preorderHelper(rootIndex);
    std::cout << std::endl;
}

void BST::inorderHelper(int currentIndex) {
    if (currentIndex == -1) {
        return;
    }
    inorderHelper(tree[currentIndex].left);
    std::cout << tree[currentIndex].value << " ";
    inorderHelper(tree[currentIndex].right);
}

void BST::inorder() {
    std::cout << "Inorder: ";
    inorderHelper(rootIndex);
    std::cout << std::endl;
}

void BST::postorderHelper(int currentIndex) {
    if (currentIndex == -1) {
        return;
    }
    postorderHelper(tree[currentIndex].left);
    postorderHelper(tree[currentIndex].right);
    std::cout << tree[currentIndex].value << " ";
}

void BST::postorder() {
    std::cout << "Postorder: ";
    postorderHelper(rootIndex);
    std::cout << std::endl;
}
