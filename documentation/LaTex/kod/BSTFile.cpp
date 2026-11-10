/**
 * @file BSTFile.cpp
 * @brief Implementacja binarnego zapisu i odczytu drzewa oraz importu liczb z pliku tekstowego.
 * @see BSTFile
 */

#include "BSTFile.h"
#include <cstdint>
#include <fstream>
#include <sstream>
#include <utility>

bool BSTFile::saveBinary(const BST& tree, const std::string& fileName)
{
    const auto values = tree.preorderValues();
    const std::uint64_t count = values.size();
    std::ofstream file(fileName, std::ios::binary);

    if (!file.write(reinterpret_cast<const char*>(&count), sizeof(count))) {
        return false;
    }
    for (int value : values) {
        if (!file.write(reinterpret_cast<const char*>(&value), sizeof(value))) {
            return false;
        }
    }

    /** Sprawdzenie stanu po zamknieciu uwzglednia bledy zapisu bufora. */
    file.close();
    return file.good();
}

bool BSTFile::loadBinary(BST& tree, const std::string& fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    std::uint64_t count;
    if (!file.read(reinterpret_cast<char*>(&count), sizeof(count))) {
        return false;
    }

    /**
     * Wstawienie wartosci preorder do pustego drzewa odtwarza ksztalt zapisanego drzewa.
     * Drzewo docelowe otrzymuje wynik dopiero po sprawdzeniu konca pliku.
     */
    BST loaded;
    for (std::uint64_t i = 0; i < count; ++i) {
        int value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(value)) || !loaded.addNode(value)) {
            return false;
        }
    }
    if (file.peek() != std::char_traits<char>::eof() || file.bad()) {
        return false;
    }

    tree = std::move(loaded);
    return true;
}

bool BSTFile::loadText(BST& tree, const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file) {
        return false;
    }

    /** Kopia pozwala zatwierdzic wszystkie dodane wartosci dopiero po walidacji pliku. */
    BST loaded = tree;
    std::string token;
    while (file >> token) {
        int value;
        std::istringstream input(token);
        /** Sprawdzenie konca tokena odrzuca wpisy z dodatkowymi znakami po liczbie. */
        if (!(input >> value) || !input.eof()) {
            return false;
        }
        loaded.addNode(value);
    }
    if (!file.eof() || file.bad()) {
        return false;
    }

    tree = std::move(loaded);
    return true;
}
