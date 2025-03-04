#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>
#include <vector>

// cited from Project 1 Breakdown Video
struct Node {
    std::string name;
    std::string ufid;
    Node* left;
    Node* right;
    int height;

    Node(std::string name, std::string ufid) {
        this->name = name;
        this->ufid = ufid;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

class AVLTree {
private:
    Node* root = nullptr;

    // insertion helpers
    Node* insertHelper(Node* node, std::string name, std::string ufid);
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

    // data validation helpers
    bool isValidUFID(std::string ufid);
    bool isValidName(std::string name);
    bool searchID(Node* node, std::string ufid);

    // traversal helpers
    void inorderHelper(Node* node, std::vector<std::string>& result);
    void preorderHelper(Node* node, std::vector<std::string>& result);
    void postorderHelper(Node* node, std::vector<std::string>& result);

    // search helpers
    Node* searchIDHelper(Node* node, std::string ufid);
    void searchNAMEHelper(Node* node, std::string name, std::vector<std::string>& results);

    //remove helpers
    Node* removeHelper(Node* node, std::string ufid);
    Node* findMin(Node* node);
    void inorderCollect(Node* node, std::vector<Node*>& nodes);
    void clear(Node* node);  // clears tree to prevent memory leaks

public:
    // traversal funcs
    void printInorder();
    void printPreorder();
    void printPostorder();

    // insert funcs
    void insert(std::string name, std::string ufid);

    // search funcs
    void searchID(std::string ufid);
    void searchNAME(std::string name);

    // get Traversals
    std::vector<std::string> getInorder();
    std::vector<std::string> getPreorder();
    std::vector<std::string> getPostorder();

    // remove funcs
    void remove(std::string ufid);
    void removeInorder(int N);

    void printLevelCount();

    Node* getRoot() { return root; }

    // destructor
    ~AVLTree() { clear(root); }
};

#endif



