#include "ex6.h"

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(int val) { root = new TreeNode{val, nullptr, nullptr}; }

BinaryTree::BinaryTree(int val, const BinaryTree &left,
                       const BinaryTree &right) {
  root = new TreeNode{val, copy(left.root), copy(right.root)};
}

BinaryTree::BinaryTree(const BinaryTree &other) { root = copy(other.root); }

BinaryTree &BinaryTree::operator=(const BinaryTree &other) {
  if (root != other.root) {
    removeAll(root);
    root = copy(other.root);
  }
  return *this;
}

BinaryTree::~BinaryTree() { removeAll(root); }

TreeNode *BinaryTree::copy(TreeNode *root) {
  if (!root) {
    return nullptr;
  }
  return new TreeNode{root->val, copy(root->left), copy(root->right)};
}

void BinaryTree::removeAll(TreeNode *root) {
  if (!root) {
    return;
  }
  removeAll(root->left);
  removeAll(root->right);
  delete root;
}