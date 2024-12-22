#include "AVLTree.h"  // Include your AVLTree header file
#include <iostream>

int main() {
    AVLTree<int> tree;

    // Test 1: Basic Insertions
    std::cout << "Test 1: Inserting values 10, 20, 30, 25, 5, 15\n";
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.insert(5);
    tree.insert(15);
    std::cout << "In-order traversal: ";
    tree.printInOrder();  // Expected: 5, 10, 15, 20, 25, 30
    std::cout << "\n";

    // Test 2: Searching for Existing and Non-Existing Keys
    std::cout << "Test 2: Searching for values 15, 10, and 50\n";
    Node<int> *node = tree.find(15);
    std::cout << "Find 15: " << (node ? "Found" : "Not found") << "\n";
    node = tree.find(10);
    std::cout << "Find 10: " << (node ? "Found" : "Not found") << "\n";
    node = tree.find(50);
    std::cout << "Find 50: " << (node ? "Found" : "Not found") << "\n";

    // Test 3: Remove Nodes with No Children (Leaf Node)
    std::cout << "Test 3: Removing leaf node 15\n";
    tree.remove(15);
    std::cout << "In-order traversal after removing 15: ";
    tree.printInOrder();  // Expected: 5, 10, 20, 25, 30
    std::cout << "\n";

    // Test 4: Remove Nodes with One Child
    std::cout << "Test 4: Removing node 5 (one child)\n";
    tree.remove(5);
    std::cout << "In-order traversal after removing 5: ";
    tree.printInOrder();  // Expected: 10, 20, 25, 30
    std::cout << "\n";

    // Test 5: Remove Nodes with Two Children
    std::cout << "Test 5: Removing node 20 (two children)\n";
    tree.remove(20);
    std::cout << "In-order traversal after removing 20: ";
    tree.printInOrder();  // Expected: 10, 25, 30
    std::cout << "\n";

    // Test 6: Tree Balancing After Removals
    std::cout << "Test 6: Checking tree balance after removing several nodes\n";
    tree.insert(35);
    tree.insert(40);
    tree.insert(50);
    std::cout << "In-order traversal after inserting 35, 40, 50: ";
    tree.printInOrder();  // Expected: 10, 25, 30, 35, 40, 50
    std::cout << "\n";

    // Test 7: Searching for All Keys After Multiple Operations
    std::cout
            << "Test 7: Searching for all keys after multiple insertions and removals\n";
    for (int key: {10, 25, 30, 35, 40, 50, 5, 15, 20}) {
        Node<int> *result = tree.find(key);
        std::cout << "Find " << key << ": " << (result ? "Found" : "Not found")
                  << "\n";
    }

    // Test 8: Remove Root Node
    std::cout << "Test 8: Removing root node (10)\n";
    tree.remove(10);
    std::cout << "In-order traversal after removing root: ";
    tree.printInOrder();  // Expected: 25, 30, 35, 40, 50
    std::cout << "\n";

    // Test 10: Edge Case - Removing All Nodes
    std::cout << "Test 10: Removing all nodes from the tree\n";
    for (int key: {50, 40, 35, 30, 25}) {
        tree.remove(key);
        std::cout << "In-order traversal after removing " << key << ": ";
        tree.printInOrder();
        std::cout << "\n";
    }
    std::cout << "Final in-order traversal (should be empty): ";
    tree.printInOrder();  // Expected: (empty)
    std::cout << "\n";

    return 0;
}
