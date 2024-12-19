#include "AVLtree.h"

int main() {
    AVLTree tree;

    // Test 1: Add elements
    cout << "Test 1: Adding elements\n";
    tree.add(10);
    tree.add(20);
    tree.add(30);
    tree.add(40);
    tree.add(50);
    tree.add(25);
    cout << "In-order traversal after adding: ";
    tree.printInOrder(); // Expected: 10 20 25 30 40 50

    // Test 2: Find elements
    cout << "\nTest 2: Finding elements\n";
    cout << "Find 30: " << (tree.find(30) ? "Found" : "Not Found")
         << endl; // Expected: Found
    cout << "Find 60: " << (tree.find(60) ? "Found" : "Not Found")
         << endl; // Expected: Not Found

    // Test 3: Erase elements
    cout << "\nTest 3: Erasing elements\n";
    tree.erase(50);
    cout << "In-order traversal after erasing 50: ";
    tree.printInOrder(); // Expected: 10 20 25 30 40

    tree.erase(30);
    cout << "In-order traversal after erasing 30: ";
    tree.printInOrder(); // Expected: 10 20 25 40

    tree.erase(10);
    cout << "In-order traversal after erasing 10: ";
    tree.printInOrder(); // Expected: 20 25 40

    // Test 4: Erase non-existent element
    cout << "\nTest 4: Erasing non-existent element\n";
    tree.erase(100); // Should not crash or alter tree
    cout << "In-order traversal after trying to erase 100: ";
    tree.printInOrder(); // Expected: 20 25 40

    // Test 5: Large sequence
    cout << "\nTest 5: Adding large sequence\n";
    for (int i = 1; i <= 15; i++) {
        tree.add(i * 5);
    }
    cout << "In-order traversal of large sequence: ";
    tree.printInOrder(); // Expected: 5 10 15 ... 75 (all multiples of 5)

    return 0;
}
