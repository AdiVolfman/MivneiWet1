#pragma once

#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T key;
    Node<T> *left;
    Node<T> *right;
    int height;

    Node();
    explicit Node(T val);
    ~Node();
    /*Node<T> &operator=(const Node<T> &other);*/
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Node<U> &node);
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
    Node<T> *find(Node<T> *node, T key);
    Node<T> *smallestNode(Node<T> *node);
    int getBalanceFactor(Node<T> *node);
    void inOrder(Node<T> *node);
    Node<T> *LLrotation(Node<T> *node);
    Node<T> *RRrotation(Node<T> *node);
    Node<T> *LRrotation(Node<T> *node);
    Node<T> *RLrotation(Node<T> *node);


public:
    explicit AVLTree<T>();
    void insert(T key);
    Node<T> *remove(T key);
    Node<T> *find(T key);
    void printInOrder();
};


template<typename T>
Node<T>::Node(T val) : key(val), left(nullptr), right(nullptr), height(1) {}

template<typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

// Definition of the friend function
template<typename T>
std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
    os << "Key: " << node.key << ", Height: " << node.height;
    return os;
}

template<typename T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
    if (this != &other) {
        key = other.key;
        left = other.left;   // Shallow copy of pointers (careful with ownership)
        right = other.right; // Shallow copy of pointers
        height = other.height;
    }
    return *this;
}

template<typename T>
int AVLTree<T>::getHeight(Node<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template<typename T>
int AVLTree<T>::getBalanceFactor(Node<T> *node) {
    if (node == nullptr) { return 0; }
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T>
Node<T> *AVLTree<T>::smallestNode(Node<T> *node) {
    Node<T> *curr = node;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

template<typename T>
Node<T> *AVLTree<T>::LLrotation(Node<T> *node) { //after insertion
    if (node == nullptr) {
        return node;
    }
    //rotation
    Node<T> *A = node->left;
    Node<T> *Ar = A->right;
    A->right = node;
    node->left = Ar;
    //A is now root
    //updating height
    A->height = max(getHeight(A->left), getHeight(A->right));
    node->height = max(getHeight(node->left), getHeight(node->right));
    //now height is set
    return A;//returning the new root
}

template<typename T>
Node<T> *AVLTree<T>::RRrotation(Node<T> *node) {

    Node<T> *B = node->right;
    Node<T> *Ar = B->left;
    B->left = node;
    node->right = Ar;
    //B became the root

    //updating the height
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
    B->height = max(getHeight(B->right), getHeight(B->left)) + 1;

    return B;
}

template<typename T>
Node<T> *AVLTree<T>::LRrotation(Node<T> *node) {
    //first we rotate the left size to the left(RR) then we rotate the root with the new root from the rotation right(LL)
    Node<T> *B = RRrotation(node->left);
    Node<T> *base = LLrotation(B);
    //base is now the new root
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;
    base->height = max(getHeight(base->left), getHeight(base->right)) + 1;
    //height updated
    return base;
}

template<typename T>
Node<T> *AVLTree<T>::RLrotation(Node<T> *node) {
    //first we rotate the right size to the right(LL) then we rotate the root with the new root from the rotation left(RR)
    Node<T> *B = LLrotation(node->right);
    Node<T> *base = RRrotation(B);
    //base is now the new root
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;
    base->height = max(getHeight(base->left), getHeight(base->right)) + 1;
    //height updated
    return base;

}

template<typename T>
Node<T> *AVLTree<T>::insert(Node<T> *node,
                            T key) {//only if horse isn't already in tree, recursive function
    if (node == nullptr) {
        try {
            return new Node(key); // Attempt to allocate memory
        } catch (const std::bad_alloc &err) { // Catch allocation error
            std::cerr << "Memory allocation failed: " << err.what()
                      << std::endl;
            return nullptr; // Return nullptr to indicate failure
        }
    }
    if (key < node->key) {
        node->left = insert(node->left, key);//recursion to the left
    } else if (key > node->key) {
        node->right = insert(node->right, key);//recursion to the right
    } else {
        return node;
    }
//updating the height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balanceFactor = getBalanceFactor(node);

    // ROTATIONS

    if (balanceFactor > 1 && getBalanceFactor(node->left) == -1) {
        return LRrotation(node);
    }
    if (balanceFactor > 1 && getBalanceFactor(node->left) > -1) {
        return LLrotation(node);
    }

    if (balanceFactor < -1 && getBalanceFactor(node->right) == 1) {
        return RLrotation(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) < 1) {
        return RRrotation(node);
    }

    return node;
}

template<typename T>
Node<T> *
AVLTree<T>::remove(Node<T> *node, T key) {// DONT FORGET TO DELETE ALLOCATIONS!!
    if (node == nullptr) { return node; }//key not found
    if (key < node->key) {
        node->left = remove(node->left, key);//recurse to the left subtree
    } else if (key > node->key) {
        node->right = remove(node->right, key);//recurse to the right subtree
    } else {//after all recursive steps, found the node to be deleted
        if (node->left == nullptr ||
            node->right == nullptr) {// if node has one or 0 children
            Node<T> *child = node->left ? node->left : node->right;
            if (child == nullptr) {// no children, removing the node
                node->height = 0;
                child = node;  // temporary pointer
                node = nullptr;     // set node to nullptr
                delete child;           // delete the original node
            } else {// one child, swapping with child
                node->height = 1;
                node->key = child->key;
                node->left = nullptr;
                node->right = nullptr;
                delete child;
            }
        } else {// node has 2 children, finiding the smallest ket on right child
            Node<T> *smallest = smallestNode(
                    node->right);//find the smallest leaf
            node->key = smallest->key;//switch between nodes, skipping relations too.
            // node->key = smallest->key;//switching between the keys
            node->right = remove(node->right,
                                 smallest->key);//remove the leaf
        }
    }

//updating the height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);

    // Balancing cases
    if (balanceFactor > 1 && getBalanceFactor(node->left) > -1) {
        return LLrotation(node);
    }
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        return LRrotation(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) < 1) {
        return RRrotation(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        return RLrotation(node);
    }

    return node;
}

template<typename T>
Node<T> *AVLTree<T>::find(Node<T> *node, T key) {
    if (!node) { return nullptr; }
    if (node->key == key) { return node; }
    if (key < node->key) {
        return find(node->left, key);
    }//searching the left part first
    return find(node->right, key);
}

template<typename T>
Node<T> *AVLTree<T>::find(T key) {
    return find(this->root, key);
}

template<typename T>
void AVLTree<T>::insert(T key) {
    this->root = insert(this->root, key);
}

template<typename T>
Node<T> *AVLTree<T>::remove(T key) {
    return remove(this->root, key);
}

template<typename T>
void AVLTree<T>::inOrder(Node<T> *node) {
    if (!node) { return; }
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

template<typename T>
void AVLTree<T>::printInOrder() {
    inOrder(this->root);
    cout << endl;
}
