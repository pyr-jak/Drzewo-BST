/**
 * @file main.cpp
 * @brief Interfejs konsolowy do obslugi binarnego drzewa poszukiwan.
 */

#include "BST.h"
#include "BSTFile.h"
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Uruchamia menu konsolowe do edycji, wyszukiwania i wyswietlania drzewa.
 *
 * Menu obsluguje takze zapisywanie i wczytywanie plikow. W trybie dodawania
 * lub usuwania wpisanie @c q przywraca menu glowne.
 * @return @c 0 po wybraniu opcji wyjscia lub gdy nie mozna dalej czytac wejscia.
 */
int main()
{
    BST bst;
    std::string token;
    const std::string binaryFile = "drzewo.bin";
    const char* invalidInput = "Nieprawidlowa liczba calkowita. Sprobuj ponownie.\n";

    while (true) {
        std::cout << "\n--- MENU DRZEWA BST ---\n"
                     "1. Dodaj elementy (wpisuj wartosci, q aby wrocic)\n"
                     "2. Usun elementy (wpisuj wartosci, q aby wrocic)\n"
                     "3. Usun cale drzewo\n"
                     "4. Wyswietl drzewo - Preorder\n"
                     "5. Wyswietl drzewo - Inorder\n"
                     "6. Wyswietl drzewo - Postorder\n"
                     "7. Wyszukaj sciezke do elementu\n"
                     "8. Zapisz drzewo do pliku drzewo.txt\n"
                     "9. Zapisz drzewo binarnie do drzewo.bin\n"
                     "10. Wczytaj drzewo binarnie z drzewo.bin\n"
                     "11. Wczytaj liczby z pliku tekstowego\n"
                     "12. Wyjscie z programu\n";

        int choice;
        while (true) {
            std::cout << "Wybierz opcje: ";
            if (!(std::cin >> token)) {
                return 0;
            }

            std::istringstream input(token);
            /** Odczyt numeru opcji wymaga, aby caly token reprezentowal jedna liczbe calkowita. */
            if (input >> choice && input.eof()) {
                break;
            }
            std::cout << invalidInput;
        }

        switch (choice) {
            case 1:
            case 2: {
                const bool adding = choice == 1;
                const char* prompt;
                if (adding) {
                    std::cout << "\n--- Tryb dodawania (wpisz q, aby wrocic do menu) ---\n";
                    prompt = "Podaj wartosc do dodania: ";
                } else {
                    std::cout << "\n--- Tryb usuwania (wpisz q, aby wrocic do menu) ---\n";
                    prompt = "Podaj wartosc do usuniecia: ";
                }

                while (true) {
                    std::cout << prompt;
                    if (!(std::cin >> token)) {
                        return 0;
                    }
                    if (token == "q") {
                        break;
                    }

                    int value;
                    std::istringstream input(token);
                    if (!(input >> value) || !input.eof()) {
                        std::cout << invalidInput;
                        continue;
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
                bst.printTree();
                break;
            case 5:
                bst.inorder();
                bst.printTree();
                break;
            case 6:
                bst.postorder();
                bst.printTree();
                break;
            case 7: {
                int value;
                while (true) {
                    std::cout << "Podaj wartosc, aby wyszukac sciezke: ";
                    if (!(std::cin >> token)) {
                        return 0;
                    }

                    std::istringstream input(token);
                    if (input >> value && input.eof()) {
                        break;
                    }
                    std::cout << invalidInput;
                }

                const auto path = bst.findPath(value);
                if (path.empty()) {
                    std::cout << "Nie znaleziono elementu " << value << ".\n";
                } else {
                    std::cout << "Sciezka od korzenia: " << path.front();
                    for (std::size_t i = 1; i < path.size(); ++i) {
                        std::cout << " -> " << path[i];
                    }
                    std::cout << '\n';
                }
                break;
            }
            case 8:
                if (bst.saveToTextFile("drzewo.txt")) {
                    std::cout << "Zapisano drzewo do pliku drzewo.txt.\n";
                } else {
                    std::cerr << "Nie udalo sie zapisac drzewa do pliku drzewo.txt.\n";
                }
                break;
            case 9:
                if (BSTFile::saveBinary(bst, binaryFile)) {
                    std::cout << "Zapisano drzewo do pliku " << binaryFile << ".\n";
                } else {
                    std::cerr << "Nie udalo sie zapisac drzewa do pliku " << binaryFile << ".\n";
                }
                break;
            case 10:
                if (BSTFile::loadBinary(bst, binaryFile)) {
                    std::cout << "Wczytano drzewo z pliku " << binaryFile << ".\n";
                } else {
                    std::cerr << "Nie udalo sie wczytac drzewa z pliku " << binaryFile << ".\n";
                }
                break;
            case 11: {
                std::cout << "Podaj nazwe pliku tekstowego: ";
                std::string fileName;
                /** Odczyt calego wiersza pozwala podac sciezke zawierajaca spacje. */
                if (!std::getline(std::cin >> std::ws, fileName)) {
                    return 0;
                }
                if (BSTFile::loadText(bst, fileName)) {
                    std::cout << "Wczytano liczby z pliku " << fileName << ".\n";
                } else {
                    std::cerr << "Nie udalo sie wczytac liczb z pliku " << fileName << ".\n";
                }
                break;
            }
            case 12:
                std::cout << "Zamykanie programu...\n";
                return 0;
            default:
                std::cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                break;
        }
    }
}
