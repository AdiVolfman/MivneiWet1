#include "AVLtree.h"

int main() {
    AVLTree<int> tree = AVLTree<int>();

    // Insert values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.insert(5);
    tree.insert(15);

    // Print tree in-order
    std::cout << "In-order before removal: ";
    tree.printInOrder();

    // Remove values
    tree.remove(10);
    std::cout << "In-order after removing 10: ";
    tree.printInOrder();

    tree.remove(20);
    std::cout << "In-order after removing 20: ";
    tree.printInOrder();

    tree.remove(5);
    std::cout << "In-order after removing 5: ";
    tree.printInOrder();

    // Find values
    std::cout << "Find 15: " << (tree.find(15) ? "Found" : "Not found")
              << std::endl;
    std::cout << "Find 10: " << (tree.find(10) ? "Found" : "Not found")
              << std::endl;

    return 0;
}
