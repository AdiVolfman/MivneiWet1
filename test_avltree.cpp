/*
#include "AVLtree.h"

int main() {
    AVLTree<int> tree;

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

    Node<int> *t = tree.find(15);
    // Find values
    std::cout << "Find 15: " << (t ? "Found" : "Not found")
              << std::endl;
    *t = *tree.find(10);
    std::cout << "Find 10: " << (tree.find(10) ? "Found" : "Not found")
              << std::endl;

    return 0;
}
*/
#include "AVLtree.h"

int main() {
    AVLTree<int> tree;

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
    std::cout << "\nIn-order after removing 10: ";
    tree.printInOrder();

    tree.remove(20);
    std::cout << "\nIn-order after removing 20: ";
    tree.printInOrder();

    tree.remove(5);
    std::cout << "\nIn-order after removing 5: ";
    tree.printInOrder();

    // Find values
    Node<int> *t = tree.find(15);
    if (t) {
        std::cout << "\nFind 15: Found, key = " << t->key << std::endl;
    } else {
        std::cout << "\nFind 15: Not found" << std::endl;
    }

    Node<int> *nodeToAssign = tree.find(10);
    if (t && nodeToAssign) {
        *t = *nodeToAssign;  // Only assign if both nodes exist
        std::cout << "Assigned the value of node 10 to node 15." << std::endl;
    } else {
        std::cout << "Could not assign values, as one of the nodes is missing."
                  << std::endl;
    }

    Node<int> *nodeAfterAssignment = tree.find(10);
    if (nodeAfterAssignment) {
        std::cout << "Find 10: Found, key = " << nodeAfterAssignment->key
                  << std::endl;
    } else {
        std::cout << "Find 10: Not found" << std::endl;
    }
    return 0;
}