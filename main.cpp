#include "BST.h"
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    BST bst;
    const char* invalidInput = "Nieprawidlowa liczba calkowita. Sprobuj ponownie.\n";

    while (true) {
        std::cout << "\n--- MENU DRZEWA BST ---\n";
        std::cout << "1. Dodaj elementy (wpisuj wartosci, 0 aby wrocic)\n";
        std::cout << "2. Usun elementy (wpisuj wartosci, 0 aby wrocic)\n";
        std::cout << "3. Usun cale drzewo\n";
        std::cout << "4. Wyswietl drzewo - Preorder\n";
        std::cout << "5. Wyswietl drzewo - Inorder\n";
        std::cout << "6. Wyswietl drzewo - Postorder\n";
        std::cout << "7. Wyjscie z programu\n";

        int choice;
        std::string token;
        while (true) {
            std::cout << "Wybierz opcje: ";
            if (!(std::cin >> token)) {
                return 0;
            }

            std::istringstream input(token);
            if (input >> choice && input.eof()) {
                break;
            }
            std::cout << invalidInput;
        }
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

    if (bst.saveToTextFile("drzewo.txt")) {
        std::cout << "Zapisano drzewo do pliku drzewo.txt.\n";
    } else {
        std::cerr << "Nie udalo sie zapisac drzewa do pliku drzewo.txt.\n";
    }

    bst.removeTree();
        switch (choice) {
            case 1:
            case 2: {
                const bool adding = choice == 1;
                const char* prompt;
                if (adding) {
                    std::cout << "\n--- Tryb dodawania (wpisz 0, aby wrocic do menu) ---\n";
                    prompt = "Podaj wartosc do dodania: ";
                } else {
                    std::cout << "\n--- Tryb usuwania (wpisz 0, aby wrocic do menu) ---\n";
                    prompt = "Podaj wartosc do usuniecia: ";
                }

                while (true) {
                    std::cout << prompt;
                    if (!(std::cin >> token)) {
                        return 0;
                    }

                    int value;
                    std::istringstream input(token);
                    if (!(input >> value) || !input.eof()) {
                        std::cout << invalidInput;
                        continue;
                    }
                    if (value == 0) {
                        break;
                    }

    std::cout << "Po ponownym dodaniu 42: ";
    bst.show();

    return 0;
}
                    if (adding) {
                        const bool added = bst.addNode(value);
                        std::cout << (added ? "Dodano: " : "Wartosc juz istnieje: ") << value << '\n';
                    } else {
                        const bool removed = bst.removeNode(value);
                        std::cout << (removed ? "Usunieto: " : "Nie znaleziono wartosci: ") << value << '\n';
                    }
                }
                break;
            }
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
}
