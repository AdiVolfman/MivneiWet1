

#include <memory>
#include <iostream>

using namespace std;

template<typename T>
struct Node {
    int key;
    std::shared_ptr<T> val;
    Node<T> *left;
    Node<T> *right;
    int height;

    explicit Node(int key, std::shared_ptr<T> val);
    ~Node();
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
    Node<T> *insert(Node<T> *node, int key, std::shared_ptr<T> val);
    Node<T> *remove(Node<T> *node, int key);
    Node<T> *find(Node<T> *node, int key);
    Node<T> *smallestNode(Node<T> *node);
    int getBalanceFactor(Node<T> *node);
    //void inOrder(Node<T> *node); functions used for checks
    //void preOrder(Node<T> *node);


    Node<T> *LLrotation(Node<T> *node);
    Node<T> *RRrotation(Node<T> *node);
    Node<T> *LRrotation(Node<T> *node);
    Node<T> *RLrotation(Node<T> *node);

public:
    Node<T> *getRoot() const;
    explicit AVLTree<T>();
    void insert(int key, std::shared_ptr<T> val);
    void remove(int key);
    shared_ptr<T> find(int key);
    ~AVLTree();
    //void printInOrder();
    //void printPreOrder();
};


template<typename T>
Node<T>::Node(int key, std::shared_ptr<T> val) : key(key), val(val),
                                                 left(nullptr),
                                                 right(nullptr),
                                                 height(1) {}


template<typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template<typename T>
Node<T>::~Node() {
    delete left;   // Recursively delete the left subtree
    delete right;  // Recursively delete the right subtree
}

template<typename T>
AVLTree<T>::~AVLTree() {
    delete root;  // This will recursively delete all nodes via Node destructor
    root = nullptr;
}

// Definition of the friend function
template<typename T>
std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
    os << "Key: " << node.key << ", Height: " << node.height;
    return os;
}


template<typename T>
//returns the root of the tree
Node<T> *AVLTree<T>::getRoot() const {
    return this->root;
}

template<typename T>
//returns the height of the tree
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
//returns the child node with the smallest key
Node<T> *AVLTree<T>::smallestNode(Node<T> *node) {
    Node<T> *curr = node;
    while (curr->left != nullptr) {//inorder
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
    //
    A->height = max(getHeight(A->right), getHeight(A->left)) + 1;
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
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
    node->left = RRrotation(node->left);
    return LLrotation(node);
}

template<typename T>
Node<T> *AVLTree<T>::RLrotation(Node<T> *node) {
    //first we rotate the right size to the right(LL) then we rotate the root with the new root from the rotation left(RR)
    node->right = LLrotation(node->right);
    return RRrotation(node);

}


template<typename T>
Node<T> *AVLTree<T>::insert(Node<T> *node,
                            int key,
                            std::shared_ptr<T> val) {//only if horse isn't already in tree, recursive function
    if (node == nullptr) {
        try {
            return new Node<T>(key, val); // Attempt to allocate memory
        } catch (const std::bad_alloc &e) { // Catch allocation error
            throw std::bad_alloc();
        }
    }
    if (key < node->key) {
        node->left = insert(node->left, key, val);//recursion to the left
    } else if (key > node->key) {
        node->right = insert(node->right, key, val);//recursion to the right
    } else {//key == node->key
        return node;
    }
//updating the height
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
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
AVLTree<T>::remove(Node<T> *node,
                   int key) {// DONT FORGET TO DELETE ALLOCATIONS!!
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
                delete node;           // delete the original node
                return nullptr;
            } else {// one child, swapping with child
                node->right = nullptr;
                node->left = nullptr;
                delete node;
                return child;
            }
        } else {// node has 2 children, finiding the smallest ket on right child
            Node<T> *smallest = smallestNode(
                    node->right);//find the smallest leaf
            node->key = smallest->key;//switch between nodes, skipping relations too.
            node->val = smallest->val;
            // node->key = smallest->key;//switching between the keys
            node->right = remove(node->right,
                                 smallest->key);//remove the leaf
        }
    }
    if (node == nullptr) { return node; }
//updating the height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);

    // Balancing cases
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        return LLrotation(node);
    }
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        return LRrotation(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        return RRrotation(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        return RLrotation(node);
    }

    return node;
}

template<typename T>
Node<T> *AVLTree<T>::find(Node<T> *node, int key) {
    if (!node) { return nullptr; }
    if (node->key == key) { return node; }
    if (key < node->key) {
        return find(node->left, key);
    }//searching the left part first
    return find(node->right, key);
}

template<typename T>
shared_ptr<T> AVLTree<T>::find(int key) {
    Node<T> *found = find(this->root, key);
    if (!found) {
        return nullptr;
    }
    return found->val;
}

template<typename T>
void AVLTree<T>::insert(int key, std::shared_ptr<T> val) {
    if (this->find(key)) {
        return;
    }
    this->root = insert(this->root, key, val);
}

template<typename T>
void AVLTree<T>::remove(int key) {
    this->root = remove(this->root, key);
}
//printing functions used for checks
//===================================
//template<typename T>
//void AVLTree<T>::inOrder(Node<T> *node) {
//    if (!node) { return; }
//    inOrder(node->left);
//    cout << node->key << " ";
//    inOrder(node->right);
//}
//
//template<typename T>
//void AVLTree<T>::printInOrder() {
//    inOrder(this->root);
//    cout << endl;
//}
//
//template<typename T>
//void AVLTree<T>::preOrder(Node<T> *node) {
//    if (!node) { return; }
//    cout << node->key << " ";
//    preOrder(node->left);
//    preOrder(node->right);
//}
//
//template<typename T>
//void AVLTree<T>::printPreOrder() {
//    preOrder(this->root);
//    cout << endl;
//}