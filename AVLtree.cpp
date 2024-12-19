// AVLtree.cpp
#include "AVLTree.h"

Node::Node(T val) : key(val), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::getHeight(Node<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(Node<T> *node) {
    if (node == nullptr) { return 0; }
    if (node->left != nullptr) {
        if (node->right != nullptr) {
            return (getHeight(node->left) - getHeight(node->right));
        }
        return getHeight(node->left);
    }
    return -(getHeight(node->right));
}

Node *AVLTree::smallestNode(Node<T> *node) {
    Node *curr = node;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

Node *AVLTree::LLrotation(Node<T> *node) { //after insertion
    if (node == nullptr) {
        return node;
    }
    //rotation
    Node *A = node->left;
    Node *Ar = A->right;
    A->right = node;
    node->left = Ar;
    //A is now root
    //updating height
    A->height = max(getHeight(A->left), getHeight(A->right));
    node->height = max(getHeight(node->left), getHeight(node->right));
    //now height is set
    return A;//returning the new root
}


Node *AVLTree::RRrotation(Node<T> *node) {

    Node *B = node->right;
    Node *Ar = B->left;
    B->left = node;
    node->right = Ar;
    //B became the root

    //updating the height
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
    B->height = max(getHeight(B->right), getHeight(B->left)) + 1;

    return B;
}

Node *AVLTree::LRrotation(Node<T> *node) {
    //first we rotate the left size to the left(RR) then we rotate the root with the new root from the rotation right(LL)
    Node *B = RRrotation(node->left);
    Node *base = LLrotation(B);
    //base is now the new root
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;
    base->height = max(getHeight(base->left), getHeight(base->right)) + 1;
    //height updated
    return base;
}

Node *AVLTree::RLrotation(Node<T> *node) {
    //first we rotate the right size to the right(LL) then we rotate the root with the new root from the rotation left(RR)
    Node *B = LLrotation(node->right);
    Node *base = RRrotation(B);
    //base is now the new root
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;
    base->height = max(getHeight(base->left), getHeight(base->right)) + 1;
    //height updated
    return base;

}

Node *
AVLTree::insert(Node<T> *node,
                int key) {//only if horse isn't already in tree, recursive function
    if (node == nullptr) {
        Node n = Node(key);
        return &n;
    }
    if (!node) { return new Node(key); }
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

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


Node *AVLTree::remove(Node *root, int key) {
    if (!root) { return root; }

    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) {
                return nullptr;
            } else {
                *root = *temp;
            }
        } else {
            Node *temp = smallestNode(root->right);
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

bool AVLTree::find(Node<T> *node, int key) {
    if (!node) { return false; }
    if (node->key == key) { return true; }
    if (key < node->key) { return find(node->left, key); }
    return find(node->right, key);
}

void AVLTree::add(int key) {
    root = insert(root, key);
}

void AVLTree::remove(int key) {
    root = remove(root, key);
}

bool AVLTree::find(int key) {
    return find(root, key);
}

void AVLTree::inOrder(Node<T> *node) {
    if (!node) { return; }
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

void AVLTree::printInOrder() {
    inOrder(root);
    cout << endl;
}
