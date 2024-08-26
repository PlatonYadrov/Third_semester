#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stack>
#include <random>
#include <utility>

class Node {
 public:
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int key;
  int64_t priority;
  int size;
  int min;
  int rev = 0;

  Node() = default;

  Node(int x, int64_t priority) : key(x), priority(priority), min(x) {
    size = 1;
  }
};

int GetSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

int GetMin(Node* node) {
  if (node == nullptr) {
    return 1000000001;
  }
  return node->min;
}

void NewSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
    node->min = std::min(node->key, std::min(GetMin(node->right), GetMin(node->left)));
  }
}

class Treap {
 private:
  std::mt19937 gen_;
  std::uniform_int_distribution<int64_t> distribution_;

  std::pair<Node*, Node*> Split(Node* t, const int64_t plase) {
    Push(t);
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    int size_left = GetSize(t->left);
    if (size_left < plase) {
      std::pair<Node*, Node*> trees = Split(t->right, plase - size_left - 1);
      t->right = trees.first;
      NewSize(t);
      return {t, trees.second};
    }
    std::pair<Node*, Node*> trees = Split(t->left, plase);
    t->left = trees.second;
    NewSize(t);
    return {trees.first, t};
  }

  Node* Merge(Node* t1, Node* t2) {
    Push(t1);
    Push(t2);
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    if (t2->priority >= t1->priority) {
      t2->left = Merge(t1, t2->left);
      NewSize(t2);
      return t2;
    }
    t1->right = Merge(t1->right, t2);
    NewSize(t1);
    return t1;
  }

  void Push(Node* node) {
    if (node != nullptr) {
      if (node->rev) {
        std::swap(node->left, node->right);
        if (node->left != nullptr) {
          node->left->rev ^= 1;
        }
        if (node->right != nullptr) {
          node->right->rev ^= 1;
        }
        node->rev = 0;
      }
    }
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

 public:
  Node* root = nullptr;

  Treap() = default;

  ~Treap() {
    Clear(root);
  }

  Node* Insert(const int64_t plase, const int x) {
    Node* node = new Node(x, distribution_(gen_));
    if (root == nullptr) {
      return node;
    }
    std::pair<Node*, Node*> trees = Split(root, plase);
    return Merge(Merge(trees.first, node), trees.second);
  }

  int Min(const int left, const int right) {
    std::pair<Node*, Node*> trees1 = Split(root, left);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, right - left + 1);
    int min = GetMin(trees2.first);
    root = Merge(trees1.first, Merge(trees2.first, trees2.second));
    return min;
  }

  void Reverse(const int left, const int right) {
    std::pair<Node*, Node*> trees1 = Split(root, left);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, right - left + 1);
    trees2.first->rev ^= 1;
    root = Merge(Merge(trees1.first, trees2.first), trees2.second);
  }
};

int main() {
  Treap treap;
  int all_commands = 0;
  int len = 0;
  std::cin >> len >> all_commands;
  int command = 0;
  int left = 0;
  int right = 0;
  for (int i = 1; i < len + 1; ++i) {
    int var = 0;
    std::cin >> var;
    treap.root = treap.Insert(i, var);
  }
  for (int i = 0; i < all_commands; ++i) {
    std::cin >> command >> left >> right;
    if (command == 1) {
      treap.Reverse(left - 1, right - 1);
      continue;
    }
    std::cout << treap.Min(left - 1, right - 1) << '\n';
  }
  return 0;
}
