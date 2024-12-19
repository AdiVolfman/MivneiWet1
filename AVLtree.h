#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

// Node structure
template<typename T>
struct Node {
    T key;
    Node<T> *nodeleft;
    Node<T> *noderight;
    int height;

    explicit Node(int val);

};

// AVL Tree class
template<typename T>
class AVLTree {
private:
    Node<T> *noderoot;

    // Helper methods
    int getHeight(Node<T> *node);
    Node<T> *nodeinsert(Node<T> *node, int key);
    Node<T> *noderemove(Node<T> *node, int key);
    Node<T> *nodesmallestNode(Node<T> *node);
    int getBalanceFactor(Node<T> *node);
    bool find(Node<T> *node, int key);
    void inOrder(Node<T> *node);
    Node<T> *nodeLLrotation(Node<T> *node);
    Node<T> *nodeRRrotation(Node<T> *node);
    Node<T> *nodeLRrotation(Node<T> *node);
    Node<T> *nodeRLrotation(Node<T> *node);


public:
    AVLTree();
    void add(int key);
    void remove(int key);
    Node<T> *node find(int key);
    void printInOrder();
};

#endif
