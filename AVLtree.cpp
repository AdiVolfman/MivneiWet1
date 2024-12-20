// AVLTree<T>.cpp
#include "AVLTree.h"

template<typename T>
Node<T>::Node(T val) : key(val), left(nullptr), right(nullptr), height(1) {}

template<typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

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
        return new Node(key);//ADD TRY AND CATCH!!!!!!!11
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
    if (node == nullptr) { return node; }
    if (key < node->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node<T> *temp = root->left ? root->left : root->right;
            if (!temp) {
                return nullptr;
            } else {
                *root = *temp;
            }
        } else {
            Node<T> *temp = smallestNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalanceFactor(root);

    // Balancing cases
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rotateRight(root);
    }

    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return rotateLeft(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

template<typename T>
Node<T> *AVLTree<T>::find(Node<T> *node, T key) {
    if (!node) { return false; }
    if (node->key == key) { return true; }
    if (key < node->key) { return find(node->left, key); }
    return find(node->right, key);
}

template<typename T>
void AVLTree<T>::add(int key) {
    root = insert(root, key);
}

template<typename T>
void AVLTree<T>::remove(int key) {
    root = remove(root, key);
}

template<typename T>
bool AVLTree<T>::find(int key) {
    return find(root, key);
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
    inOrder(root);
    cout << endl;
}
