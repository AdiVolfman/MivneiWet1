#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

// Node structure
template<typename T>
struct Node {
    T key;
    Node<T> *left;
    Node<T> *right;
    int height;

    explicit Node(T val);

};

// AVL Tree class
template<typename T>
class AVLTree {
private:
    Node<T> *root;

    // Helper methods
    int getHeight(Node<T> *node);
    Node<T> *insert(Node<T> *node, T key);
    Node<T> *remove(Node<T> *node, T key);
    Node<T> *smallestNode(Node<T> *node);
    int getBalanceFactor(Node<T> *node);
    bool find(Node<T> *node, T key);
    void inOrder(Node<T> *node);
    Node<T> *LLrotation(Node<T> *node);
    Node<T> *RRrotation(Node<T> *node);
    Node<T> *LRrotation(Node<T> *node);
    Node<T> *RLrotation(Node<T> *node);


public:
    AVLTree();
    int insert(T key);
    int remove(T key);
    Node<T> *find(T key);
    void printInOrder();
};

#endif
