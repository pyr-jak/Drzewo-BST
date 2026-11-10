/**
 * @file BST.cpp
 * @brief Implementacja binarnego drzewa poszukiwan przechowywanego w wektorze.
 * @see BST
 */

#include "BST.h"
#include <iostream>
#include <fstream>

BST::BST() {
    rootIndex = -1;
}

int BST::insert(int currentIndex, int value) {
    if (currentIndex == -1) {
        tree.push_back(Node(value));
        return (tree.size()) - 1;
    }

    /**
     * Dostep przez indeks pozwala ponownie znalezc rodzica po ewentualnej
     * realokacji wektora podczas rekurencyjnego wstawiania.
     */
    if (value < tree[currentIndex].value) {
        int nextLeft = insert(tree[currentIndex].left, value);
        tree[currentIndex].left = nextLeft;
    } else if (value > tree[currentIndex].value) {
        int nextRight = insert(tree[currentIndex].right, value);
        tree[currentIndex].right = nextRight;
    }

    return currentIndex;
}

bool BST::addNode(int value) {
    /** Wzrost rozmiaru wektora oznacza, ze wstawienie utworzylo nowy wezel. */
    const auto sizeBefore = tree.size();
    rootIndex = insert(rootIndex, value);
    return tree.size() != sizeBefore;
}

void BST::show() {
    for (size_t i = 0; i < tree.size(); i++) {
        std::cout << tree[i].value << " ";
    }
    std::cout << std::endl;
}

bool BST::removeNode(int value)
{
    int currentIndex = rootIndex;
    int parentIndex = -1;

    while (currentIndex != -1 && tree[currentIndex].value != value) {
        parentIndex = currentIndex;

        if (value < tree[currentIndex].value) {
            currentIndex = tree[currentIndex].left;
        } else {
            currentIndex = tree[currentIndex].right;
        }
    }

    if (currentIndex == -1) {
        return false;
    }

    /**
     * Nastepnik w porzadku inorder ma w tym przypadku co najwyzej jedno dziecko.
     * Po skopiowaniu jego wartosci wspolny krok przepiecia potomka usuwa nastepnik.
     */
    if (tree[currentIndex].left != -1 &&
        tree[currentIndex].right != -1) {

        int successorParent = currentIndex;
        int successorIndex = tree[currentIndex].right;

        while (tree[successorIndex].left != -1) {
            successorParent = successorIndex;
            successorIndex = tree[successorIndex].left;
        }

        tree[currentIndex].value = tree[successorIndex].value;

        parentIndex = successorParent;
        currentIndex = successorIndex;
    }

    const int childIndex = tree[currentIndex].left != -1
        ? tree[currentIndex].left
        : tree[currentIndex].right;

    if (parentIndex == -1) {
        rootIndex = childIndex;
    } else if (tree[parentIndex].left == currentIndex) {
        tree[parentIndex].left = childIndex;
    } else {
        tree[parentIndex].right = childIndex;
    }

    /** Po usunieciu elementu kazdy kolejny wezel w wektorze przesuwa sie o jedno miejsce. */
    tree.erase(tree.begin() + currentIndex);

    if (rootIndex > currentIndex) {
        --rootIndex;
    }

    for (Node& node : tree) {
        if (node.left > currentIndex) {
            --node.left;
        }

        if (node.right > currentIndex) {
            --node.right;
        }
    }

    return true;
}

void BST::removeTree()
{
    tree.clear();
    rootIndex = -1;
}

std::vector<int> BST::preorderValues() const
{
    std::vector<int> values;
    values.reserve(tree.size());
    std::vector<int> pendingIndices;
    if (rootIndex != -1) {
        pendingIndices.push_back(rootIndex);
    }

    while (!pendingIndices.empty()) {
        const int currentIndex = pendingIndices.back();
        pendingIndices.pop_back();

        const Node& node = tree[currentIndex];
        values.push_back(node.value);

        /**
         * Prawe dziecko trafia na stos przed lewym. Poniewaz zdejmowany jest
         * ostatni dodany indeks, lewe poddrzewo jest odwiedzane jako pierwsze.
         */
        if (node.right != -1) {
            pendingIndices.push_back(node.right);
        }
        if (node.left != -1) {
            pendingIndices.push_back(node.left);
        }
    }
    return values;
}

bool BST::saveToTextFile(const std::string& fileName) const
{
    std::ofstream file(fileName);
    if (!file) {
        return false;
    }
    /** Wstawienie wartosci w tej kolejnosci do pustego drzewa odtwarza ksztalt zapisanego drzewa. */
    for (int value : preorderValues()) {
        if (!(file << value << '\n')) {
            return false;
        }
    }
    file.close();
    return file.good();
}

std::size_t BST::drawBranch(int currentIndex, std::size_t row, std::size_t& nextColumn,
                            std::vector<std::string>& lines) const {
    if (currentIndex == -1) {
        return std::string::npos;
    }

    /**
     * Miejsce na etykiety jest przydzielane w kolejnosci inorder. Etykieta wezla
     * z dwojgiem dzieci jest wysrodkowana wzgledem ich etykiet. Pomiedzy poziomami
     * drzewa znajduja sie osobne wiersze na laczniki.
     */
    const Node& node = tree[currentIndex];
    const auto leftColumn = drawBranch(node.left, row + 2, nextColumn, lines);

    const std::string label = std::to_string(node.value);
    std::size_t center = nextColumn + label.size() / 2;
    nextColumn += label.size() + 2;

    const auto rightColumn = drawBranch(node.right, row + 2, nextColumn, lines);
    if (leftColumn != std::string::npos && rightColumn != std::string::npos) {
        center = leftColumn + (rightColumn - leftColumn) / 2;
    }

    if (lines.size() <= row) {
        lines.resize(row + 1);
    }
    lines[row].resize(center - label.size() / 2, ' ');
    lines[row] += label;

    if (leftColumn != std::string::npos) {
        lines[row + 1].resize(leftColumn + (center - leftColumn) / 2, ' ');
        lines[row + 1] += '/';
    }
    if (rightColumn != std::string::npos) {
        lines[row + 1].resize(rightColumn - (rightColumn - center) / 2, ' ');
        lines[row + 1] += '\\';
    }
    return center;
}

void BST::printTree() const {
    if (rootIndex == -1) {
        std::cout << "Drzewo jest puste.\n";
        return;
    }
    std::vector<std::string> lines;
    std::size_t nextColumn = 0;
    drawBranch(rootIndex, 0, nextColumn, lines);

    std::cout << "Drzewo:\n";
    for (const auto& line : lines) {
        std::cout << line << '\n';
    }
}

void BST::preorder() {
    std::cout << "Preorder: ";
    for (int value : preorderValues()) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;
}

void BST::inorderHelper(int currentIndex) {
    if (currentIndex == -1) {
        return;
    }
    /** Wypisanie wezla miedzy przejsciami po dzieciach daje rosnaca kolejnosc wartosci. */
    inorderHelper(tree[currentIndex].left);
    std::cout << tree[currentIndex].value << " ";
    inorderHelper(tree[currentIndex].right);
}

void BST::inorder() {
    std::cout << "Inorder: ";
    inorderHelper(rootIndex);
    std::cout << std::endl;
}

void BST::postorderHelper(int currentIndex) {
    if (currentIndex == -1) {
        return;
    }
    /** Wezel jest wypisywany po odwiedzeniu wszystkich jego potomkow. */
    postorderHelper(tree[currentIndex].left);
    postorderHelper(tree[currentIndex].right);
    std::cout << tree[currentIndex].value << " ";
}

void BST::postorder() {
    std::cout << "Postorder: ";
    postorderHelper(rootIndex);
    std::cout << std::endl;
}
bool BST::findElement(int value) const {
    int currentIndex = rootIndex;

    while (currentIndex != -1) {
        if (value == tree[currentIndex].value) {
            return true;
        }

        /** Porownanie wybiera jedyne poddrzewo, w ktorym moze byc szukana wartosc. */
        if (value < tree[currentIndex].value) {
            currentIndex = tree[currentIndex].left;
        } else {
            currentIndex = tree[currentIndex].right;
        }
    }

    return false;
}
std::vector<int> BST::findPath(int value) const {
    std::vector<int> path;
    int currentIndex = rootIndex;

    while (currentIndex != -1) {
        /** Zapis wartosci przed sprawdzeniem dopasowania wlacza znaleziony wezel do sciezki. */
        const Node& node = tree[currentIndex];
        path.push_back(node.value);

        if (value == node.value) {
            return path;
        }

        currentIndex = value < node.value ? node.left : node.right;
    }

    return {};
}
