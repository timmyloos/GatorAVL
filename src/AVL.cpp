#include "AVL.h"
#include <iostream>

// cited from Project 1 Breakdown Video

int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* AVLTree::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    // LL Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // RR Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // LR Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // RL Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// must be exactly 8 digits
bool AVLTree::isValidUFID(std::string ufid) {
    if (ufid.length() != 8) return false;
    for (char c : ufid) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// only alphabets and spaces
bool AVLTree::isValidName(std::string name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// prevents duplicate IDs
bool AVLTree::searchID(Node* node, std::string ufid) {
    if (!node) return false;
    if (ufid == node->ufid) return true;
    if (ufid < node->ufid) return searchID(node->left, ufid);
    return searchID(node->right, ufid);
}

Node* AVLTree::insertHelper(Node* node, std::string name, std::string ufid) {
    // base case
    if (!node) return new Node(name, ufid);

    // recursive insert
    if (ufid < node->ufid)
        node->left = insertHelper(node->left, name, ufid);
    else if (ufid > node->ufid)
        node->right = insertHelper(node->right, name, ufid);
    else
        return node;

    // Update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // balance and return the modified node
    return balance(node);
}

void AVLTree::insert(std::string name, std::string ufid) {
    // validate input
    if (!isValidUFID(ufid) || !isValidName(name)) {
        std::cout << "unsuccessful\n";
        return;
    }

    // check if already exists
    if (searchID(root, ufid)) {
        std::cout << "unsuccessful\n";
        return;
    }

    // insert and balance
    root = insertHelper(root, name, ufid);
    std::cout << "successful\n";
}


// inorder traversal helper func
void AVLTree::inorderHelper(Node* node, std::vector<std::string>& result) {
    if (!node) return;
    inorderHelper(node->left, result);
    result.push_back(node->name);  // Store name for testing
    inorderHelper(node->right, result);
}
// inorder vector fun
std::vector<std::string> AVLTree::getInorder() {
    std::vector<std::string> result;
    inorderHelper(root, result);
    return result;
}

void AVLTree::printInorder() {
    std::vector<std::string> result = getInorder();

    if (result.empty()) {
        std::cout << std::endl;
        return;
    }

    // print names in csv format
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i];
        if (i != result.size() - 1) std::cout << ", ";
    }

    std::cout << std::endl;
}

void AVLTree::preorderHelper(Node* node, std::vector<std::string>& result) {
    if (!node) return;
    result.push_back(node->name);
    preorderHelper(node->left, result);
    preorderHelper(node->right, result);
}
// preorder vector fun
std::vector<std::string> AVLTree::getPreorder() {
    std::vector<std::string> result;
    preorderHelper(root, result);
    return result;
}

void AVLTree::postorderHelper(Node* node, std::vector<std::string>& result) {
    if (!node) return;
    postorderHelper(node->left, result);
    postorderHelper(node->right, result);
    result.push_back(node->name);
}

// postorder vector func
std::vector<std::string> AVLTree::getPostorder() {
    std::vector<std::string> result;
    postorderHelper(root, result);
    return result;
}

void AVLTree::printPreorder() {
    std::vector<std::string> result = getPreorder();

    if (result.empty()) {
        std::cout << std::endl;
        return;
    }

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i];
        if (i != result.size() - 1) std::cout << ", ";
    }

    std::cout << std::endl;
}

void AVLTree::printPostorder() {
    std::vector<std::string> result = getPostorder();

    if (result.empty()) {
        std::cout << std::endl;
        return;
    }

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i];
        if (i != result.size() - 1) std::cout << ", ";
    }

    std::cout << std::endl;
}

Node* AVLTree::searchIDHelper(Node* node, std::string ufid) {
    if (!node) return nullptr;

    if (ufid == node->ufid) return node;
    if (ufid < node->ufid) return searchIDHelper(node->left, ufid);
    return searchIDHelper(node->right, ufid);
}
void AVLTree::searchID(std::string ufid) {
    Node* result = searchIDHelper(root, ufid);

    if (result) std::cout << result->name << std::endl;
    else std::cout << "unsuccessful" << std::endl;
}

void AVLTree::searchNAMEHelper(Node* node, std::string name, std::vector<std::string>& results) {
    if (!node) return;

    // if name matches, store UFID
    if (node->name == name) {
        results.push_back(node->ufid);
    }

    // continue search in left and right subtrees
    searchNAMEHelper(node->left, name, results);
    searchNAMEHelper(node->right, name, results);
}


void AVLTree::searchNAME(std::string name) {
    std::vector<std::string> results;
    searchNAMEHelper(root, name, results);

    if (results.empty()) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        for (const auto& ufid : results) {
            std::cout << ufid << std::endl;  // each UFID is printed on a new line
        }
    }
}


Node* AVLTree::findMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* AVLTree::removeHelper(Node* node, std::string ufid) {
    if (!node) return nullptr; // node not found

    // search for the node to remove
    if (ufid < node->ufid) {
        node->left = removeHelper(node->left, ufid);
    } else if (ufid > node->ufid) {
        node->right = removeHelper(node->right, ufid);
    } else {
        // node found perform deletion
        if (!node->left && !node->right) {
            delete node;
            return nullptr; // no children case
        }
        else if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp; // one child right case
        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp; // one child left case
        }
        else {
            // two children - find inorder successor
            Node* temp = findMin(node->right);
            node->name = temp->name;
            node->ufid = temp->ufid;
            node->right = removeHelper(node->right, temp->ufid);
        }
    }

    // update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // rebalance tree
    return balance(node);
}

void AVLTree::remove(std::string ufid) {
    if (!searchIDHelper(root, ufid)) {  // check if UFID exists
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    root = removeHelper(root, ufid);
    std::cout << "successful" << std::endl;
}

void AVLTree::inorderCollect(Node* node, std::vector<Node*>& nodes) {
    if (!node) return;

    inorderCollect(node->left, nodes);
    nodes.push_back(node);  // store node for reference
    inorderCollect(node->right, nodes);
}

void AVLTree::removeInorder(int N) {
    std::vector<Node*> nodes;
    inorderCollect(root, nodes);

    if (N < 0 || N >= nodes.size()) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    // remove the Nth node using its UFID
    remove(nodes[N]->ufid);
}

void AVLTree::printLevelCount() {
    if (!root) {
        std::cout << "0" << std::endl;
        return;
    }

    std::cout << root->height << std::endl;
}

void AVLTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
