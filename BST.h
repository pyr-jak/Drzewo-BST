/**
 * @file BST.h
 * @brief Deklaracje wezla i klasy binarnego drzewa poszukiwan.
 */

#ifndef BST_H
#define BST_H

#include <vector>

/**
 * @brief Wezel drzewa przechowywanego w kontenerze STL.
 *
 * Pola left i right zawieraja indeksy dzieci w wektorze.
 * Wartosc -1 oznacza brak dziecka.
 */
struct Node {
    int value; ///< Wartosc przechowywana w wezle.
    int left;  ///< Indeks lewego dziecka albo -1.
    int right; ///< Indeks prawego dziecka albo -1.

    /**
     * @brief Tworzy wezel bez dzieci.
     * @param value Wartosc nowego wezla.
     */
    Node(int value) : value(value), left(-1), right(-1) {}
};

/**
 * @brief Binarne drzewo poszukiwan oparte na std::vector.
 *
 * Lewe poddrzewo zawiera wartosci mniejsze od wartosci wezla,
 * a prawe poddrzewo wartosci wieksze. Duplikaty sa pomijane.
 */
class BST {
private:
    std::vector<Node> tree; ///< Kontener wszystkich wezlow.
    int rootIndex; ///< Indeks korzenia; -1 oznacza puste drzewo.

    /**
     * @brief Rekurencyjnie dodaje wartosc do poddrzewa.
     * @param currentIndex Indeks korzenia poddrzewa albo -1.
     * @param value Wartosc przeznaczona do dodania.
     * @return Indeks korzenia poddrzewa po operacji.
     */
    int insert(int currentIndex, int value);

public:
    /** @brief Tworzy puste drzewo. */
    BST();

    /**
     * @brief Dodaje wartosc, jezeli jeszcze nie wystepuje.
     * @param value Wartosc nowego wezla.
     */
    void addNode(int value);

    /**
     * @brief Usuwa wezel o podanej wartosci.
     * @param value Wartosc wezla przeznaczonego do usuniecia.
     *
     * Obsluguje lisc, jedno dziecko, dwoje dzieci oraz korzen.
     * Dla dwojga dzieci wykorzystuje minimum prawego poddrzewa.
     * Po usunieciu elementu wektora aktualizuje indeksy polaczen.
     *
     * @note Brak wartosci lub puste drzewo nie powoduje zmian.
     * @par Zlozonosc
     * Udane usuniecie: O(n). Brak wartosci: O(h).
     * Dodatkowa pamiec: O(1).
     * n oznacza liczbe wezlow, a h wysokosc drzewa.
     */
    void removeNode(int value);

    /**
     * @brief Usuwa wszystkie wezly drzewa.
     *
     * Czysci wektor i ustawia indeks korzenia na -1.
     * Mozna wywolywac wielokrotnie, takze dla pustego drzewa.
     * Po wyczyszczeniu mozna ponownie dodawac elementy.
     *
     * @note Pojemnosc wektora pozostaje do ponownego wykorzystania.
     * @par Zlozonosc
     * Czas: O(n). Dodatkowa pamiec: O(1).
     */
    void removeTree();

    bool findElement(int value) const;

    std::vector<int> findPath(int value) const;

    /**
     * @brief Wypisuje wartosci w kolejnosci przechowywania w wektorze.
     * @note Nie realizuje przejsc preorder, inorder ani postorder.
     */



    void show();


};

#endif