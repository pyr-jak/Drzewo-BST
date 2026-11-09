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

    if (bst.saveToTextFile("drzewo.txt")) {
        std::cout << "Zapisano drzewo do pliku drzewo.txt.\n";
    } else {
        std::cerr << "Nie udalo sie zapisac drzewa do pliku drzewo.txt.\n";
    }

    bst.removeTree();

    std::cout << "Po usunieciu calego drzewa: ";
    bst.show();

    bst.addNode(42);

    std::cout << "Po ponownym dodaniu 42: ";
    bst.show();

    return 0;
}