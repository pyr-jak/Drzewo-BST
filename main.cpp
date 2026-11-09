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

    std::cout << "Podaj wartość, aby wyszukać ścieżkę: ";
    int value;
    if (std::cin >> value) {
        const std::vector<int> path = bst.findPath(value);
        if (path.empty()) {
            std::cout << "Nie znaleziono elementu " << value << ".\n";
        } else {
            std::cout << "Ścieżka od korzenia: " << path.front();
            for (std::size_t i = 1; i < path.size(); ++i) {
                std::cout << " -> " << path[i];
            }
            std::cout << '\n';
        }
    } else {
        std::cout << "Nie podano poprawnej liczby całkowitej.\n";
    }

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