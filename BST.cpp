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

    // Wyszukanie wezla i zapamietanie jego rodzica.
    while (currentIndex != -1 && tree[currentIndex].value != value) {
        parentIndex = currentIndex;

        if (value < tree[currentIndex].value) {
            currentIndex = tree[currentIndex].left;
        } else {
            currentIndex = tree[currentIndex].right;
        }
    }

    // Wartosc nie wystepuje w drzewie.
    if (currentIndex == -1) {
        return;
    }

    // Wezel ma dwoje dzieci: wybieramy minimum prawego poddrzewa.
    if (tree[currentIndex].left != -1 &&
        tree[currentIndex].right != -1) {

        int successorParent = currentIndex;
        int successorIndex = tree[currentIndex].right;

        while (tree[successorIndex].left != -1) {
            successorParent = successorIndex;
            successorIndex = tree[successorIndex].left;
        }

        // Kopiujemy wartosc nastepnika do znalezionego wezla.
        tree[currentIndex].value = tree[successorIndex].value;

        // Dalej usuwamy nastepnik, ktory ma najwyzej jedno dziecko.
        parentIndex = successorParent;
        currentIndex = successorIndex;
    }

    // Jedyne dziecko albo -1, gdy usuwany wezel jest lisciem.
    const int childIndex = tree[currentIndex].left != -1
        ? tree[currentIndex].left
        : tree[currentIndex].right;

    // Przepiecie rodzica lub zmiana korzenia.
    if (parentIndex == -1) {
        rootIndex = childIndex;
    } else if (tree[parentIndex].left == currentIndex) {
        tree[parentIndex].left = childIndex;
    } else {
        tree[parentIndex].right = childIndex;
    }

    // Fizyczne usuniecie wezla z kontenera.
    tree.erase(tree.begin() + currentIndex);

    // Po erase pozniejsze elementy maja indeks mniejszy o jeden.
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

}