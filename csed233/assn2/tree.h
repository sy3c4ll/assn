#pragma once
#include <string>
#include <fstream>
using namespace std;

struct Node {
    Node(char input_value) : value(input_value), left(nullptr), right(nullptr) {}
    char value;
    Node *left;
    Node *right;
};

class BinaryTree {
public:
    BinaryTree() : _root(nullptr) {}
    ~BinaryTree() { delete[] _root; }
    void buildFromString(const char *data);

    string preOrder();
    string postOrder();
    string levelOrder();
    string inOrder();
    string general_tree();

private:
    Node *_root;
    /////////////////////////////////////////////////////////
    //////  TODO: Add Private members if required ///////////
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
