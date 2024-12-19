#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

// Node structure
template<typename T>
struct Node {
    T key;
    Node *left;
    Node *right;
    int height;

    explicit Node(int val);

};

// AVL Tree class
template<typename T>
class AVLTree {
private:
    Node *root;

    // Helper methods
    int getHeight(Node<T> *node);
    Node *insert(Node<T> *node, int key);
    Node *remove(Node<T> *node, int key);
    Node *smallestNode(Node<T> *node);
    int getBalanceFactor(Node<T> *node);
    bool find(Node<T> *node, int key);
    void inOrder(Node<T> *node);
    Node *LLrotation(Node<T> *node);
    Node *RRrotation(Node<T> *node);
    Node *LRrotation(Node<T> *node);
    Node *RLrotation(Node<T> *node);


public:
    AVLTree();
    void add(int key);
    void remove(int key);
    Node<T> *node find(int key);
    void printInOrder();
};

#endif
