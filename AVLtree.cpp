// AVLtree.cpp
#include "AVLTree.h"

Node::Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::getHeight(Node *node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node *AVLTree::rotateRight(Node *y) {
    Node *x = y->left;
    Node *T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node *AVLTree::rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node *AVLTree::insert(Node *node, int key) {
    if (!node) { return new Node(key); }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    } // Duplicate keys not allowed

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Balancing cases
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node *AVLTree::minValueNode(Node *node) {
    Node *current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

Node *AVLTree::erase(Node *root, int key) {
    if (!root) { return root; }

    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) {
                return nullptr;
            } else {
                *root = *temp;
            }
        } else {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = erase(root->right, temp->key);
        }
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);

    // Balancing cases
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

bool AVLTree::search(Node *node, int key) {
    if (!node) { return false; }
    if (node->key == key) { return true; }
    if (key < node->key) { return search(node->left, key); }
    return search(node->right, key);
}

void AVLTree::add(int key) {
    root = insert(root, key);
}

void AVLTree::erase(int key) {
    root = erase(root, key);
}

bool AVLTree::find(int key) {
    return search(root, key);
}

void AVLTree::inOrder(Node *node) {
    if (!node) { return; }
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

void AVLTree::printInOrder() {
    inOrder(root);
    cout << endl;
}
