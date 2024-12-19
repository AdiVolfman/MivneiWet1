#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val);
};

// AVL Tree class
class AVLTree {
private:
    Node* root;

    // Helper methods
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, int key);
    Node* erase(Node* node, int key);
    Node* minValueNode(Node* node);
    bool search(Node* node, int key);
    void inOrder(Node* node);

public:
    AVLTree();
    void add(int key);
    void erase(int key);
    bool find(int key);
    void printInOrder();
};

#endif
