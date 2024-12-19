#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

// Node structure
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;

    explicit Node(int val);

};

// AVL Tree class
class AVLTree {
private:
    Node *root;

    // Helper methods
    int getHeight(Node *node);
    Node *rotateRight(Node *y);
    Node *rotateLeft(Node *x);
    Node *insert(Node *node, int key);
    Node *remove(Node *node, int key);
    Node *smallestNode(Node *node);
    int getBalanceFactor(Node *node);
    bool find(Node *node, int key);
    void inOrder(Node *node);
    Node *LLrotation(Node *node);
    Node *RRrotation(Node *node);
    Node *LRrotation(Node *node);
    Node *RLrotation(Node *node);


public:
    AVLTree();
    void add(int key);
    void remove(int key);
    bool find(int key);
    void printInOrder();
};

#endif
