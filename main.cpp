#include "BST.h"
#include <iostream>

int main()
{
    BST bst;
    int choice;
    int value;

    bst.addNode(5);
    bst.addNode(3);
    bst.addNode(7);
    bst.addNode(1);
    bst.addNode(4);
    bst.addNode(6);
    bst.addNode(8);

    while (true) {
        std::cout << "\n--- MENU DRZEWA BST ---\n";
        std::cout << "1. Dodaj element\n";
        std::cout << "2. Usun element\n";
        std::cout << "3. Usun cale drzewo\n";
        std::cout << "4. Wyswietl drzewo - Preorder\n";
        std::cout << "5. Wyswietl drzewo - Inorder\n";
        std::cout << "6. Wyswietl drzewo - Postorder\n";
        std::cout << "7. Wyjscie z programu\n";
        std::cout << "Wybierz opcje: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj wartosc do dodania: ";
                std::cin >> value;
                bst.addNode(value);
                std::cout << "Element zostal dodany.\n";
                break;
            case 2:
                std::cout << "Podaj wartosc do usuniecia: ";
                std::cin >> value;
                bst.removeNode(value);
                std::cout << "Procedura usuniecia wykonana.\n";
                break;
            case 3:
                bst.removeTree();
                std::cout << "Cale drzewo zostalo usuniete.\n";
                break;
            case 4:
                bst.preorder();
                break;
            case 5:
                bst.inorder();
                break;
            case 6:
                bst.postorder();
                break;
            case 7:
                std::cout << "Zamykanie programu...\n";
                return 0;
            default:
                std::cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                break;
        }
    }

    return 0;
}