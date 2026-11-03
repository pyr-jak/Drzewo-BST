#include "BST.h"
#include <iostream>

int main()
{
    BST bst;

    bst.addNode(1);
    bst.addNode(2);
    bst.addNode(3);
    bst.addNode(8);
    bst.addNode(5);

    std::cout << "Przed usunieciem: ";
    bst.show();

    bst.removeNode(3);

    std::cout << "Po usunieciu wezla 3: ";
    bst.show();

    bst.removeTree();

    std::cout << "Po usunieciu calego drzewa: ";
    bst.show();

    bst.addNode(42);

    std::cout << "Po ponownym dodaniu 42: ";
    bst.show();
    return 0;
}