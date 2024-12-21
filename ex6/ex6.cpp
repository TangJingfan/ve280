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

bool BinaryTree::operator==(const BinaryTree &other) const {
  return equal(root, other.root);
}

bool BinaryTree::equal(TreeNode *root, TreeNode *other) const {
  if (!root && !other) {
    return true;
  }
  if (!root || !other) {
    return false;
  }
  return root->val == other->val && equal(root->left, other->left) &&
         equal(root->right, other->right);
}

bool BinaryTree::isEmpty() const { return root == nullptr; }

int BinaryTree::sum() const {
  if (!root) {
    return 0;
  }
  BinaryTree leftSubTree(root->left);
  BinaryTree rightSubTree(root->right);
  return root->val + leftSubTree.sum() + rightSubTree.sum();
}

BinaryTree::BinaryTree(TreeNode *node) { root = copy(node); }

int BinaryTree::depth() const {
  if (!root) {
    return 0;
  }

  int leftDepth = 0;
  if (root->left) {
    BinaryTree leftSubTree(root->left);
    leftDepth = leftSubTree.depth();
  }

  int rightDepth = 0;
  if (root->right) {
    BinaryTree rightSubTree(root->right);
    rightDepth = rightSubTree.depth();
  }

  return 1 + std::max(leftDepth, rightDepth);
}

std::ostream &operator<<(std::ostream &os, const BinaryTree &tree) {
  if (tree.root) {
    if (tree.root->left) {
      os << BinaryTree(tree.root->left);
    }
    os << tree.root->val << " ";
    if (tree.root->right) {
      os << BinaryTree(tree.root->right);
    }
  }
  return os;
}