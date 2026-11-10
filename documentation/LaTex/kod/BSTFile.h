/**
 * @file BSTFile.h
 * @brief Deklaracje operacji plikowych dla binarnego drzewa poszukiwan.
 */

#ifndef BST_FILE_H
#define BST_FILE_H

#include "BST.h"
#include <string>

/** @brief Udostepnia binarny zapis i odczyt drzewa oraz import liczb z pliku tekstowego. */
class BSTFile {
public:
    /**
     * @brief Zapisuje drzewo do pliku binarnego w kolejnosci preorder.
     * @param tree Drzewo przeznaczone do zapisu.
     * @param fileName Sciezka do pliku tworzonego lub nadpisywanego przy zapisie.
     * @return @c true po pomyslnym zapisie albo @c false w razie bledu otwarcia,
     * zapisu lub zamkniecia pliku.
     *
     * Najpierw zapisuje liczbe wezlow jako @c std::uint64_t, a nastepnie wartosci jako @c int.
     * @note Format zalezy od rozmiaru typu @c int i kolejnosci bajtow platformy.
     */
    static bool saveBinary(const BST& tree, const std::string& fileName);

    /**
     * @brief Wczytuje drzewo z pliku zapisanego przez @ref BSTFile::saveBinary "saveBinary".
     * @param[out] tree Drzewo zastepowane wynikiem po poprawnym odczycie calego pliku.
     * @param fileName Sciezka do pliku binarnego.
     * @return @c true po wczytaniu albo @c false przy bledzie odczytu lub niepoprawnych danych.
     *
     * Odrzuca niepelne dane, powtorzone wartosci i nadmiarowe bajty.
     */
    static bool loadBinary(BST& tree, const std::string& fileName);

    /**
     * @brief Dodaje do drzewa liczby calkowite z pliku tekstowego.
     * @param[in,out] tree Drzewo uzupelniane po poprawnym odczycie calego pliku.
     * @param fileName Sciezka do pliku tekstowego.
     * @return @c true po wczytaniu albo @c false przy bledzie odczytu lub niepoprawnej liczbie.
     *
     * Biale znaki oddzielaja liczby. Powtorzone wartosci sa pomijane.
     * Kazda liczba musi miescic sie w zakresie typu @c int.
     */
    static bool loadText(BST& tree, const std::string& fileName);
};

#endif
