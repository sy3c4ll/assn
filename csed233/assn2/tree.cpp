#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return nullptr;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::general_tree() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  static string (*general_tree_from)(Node *) = [] (Node *root) {
    string s;

    s = root->value;
    for (Node *cur = root->left; cur; cur = cur->right)
      s += '(' + general_tree_from(cur) + ')';

    return s;
  };

  return _root ? general_tree_from(_root) : "";

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::levelOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string s;

  basic_string<Node *> queue = {_root};
  for (; !queue.empty(); queue.erase(0, 1))
    if (queue[0]) {
      s.push_back(queue[0]->value);
      s.push_back(' ');
      queue.push_back(queue[0]->left);
      queue.push_back(queue[0]->right);
    }

  return s;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  static string (*preorder_from)(Node *) = [] (Node *root) {
    return root ? root->value + " " + preorder_from(root->left) + preorder_from(root->right) : "";
  };

  return preorder_from(_root);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  static string (*postorder_from)(Node *) = [] (Node *root) {
    return root ? postorder_from(root->left) + postorder_from(root->right) + root->value + " " : "";
  };

  return postorder_from(_root);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  static string (*inorder_from)(Node *) = [] (Node *root) {
    return root ? inorder_from(root->left) + root->value + " " + inorder_from(root->right) : "";
  };

  return inorder_from(_root);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
