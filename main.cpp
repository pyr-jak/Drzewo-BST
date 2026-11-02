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

    return 0;
}