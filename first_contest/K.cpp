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
  int64_t sum;
  int min;

  Node() = default;

  Node(int x, int64_t priority) : key(x), priority(priority), sum(static_cast<int64_t>(x)) {
  }
};

int64_t GetSum(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->sum;
}

int GetMin(Node* node) {
  if (node == nullptr) {
    return 1000000001;
  }
  return node->min;
}

void NewSize(Node* node) {
  if (node != nullptr) {
    node->sum = GetSum(node->left) + GetSum(node->right) + node->key;
    node->min = std::min(node->key, std::min(GetMin(node->right), GetMin(node->left)));
  }
}

class Treap {
 private:
  std::mt19937 gen_;
  std::uniform_int_distribution<int64_t> distribution_;

  std::pair<Node*, Node*> Split(Node* t, const int x) {
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    if (t->key < x) {
      std::pair<Node*, Node*> trees = Split(t->right, x);
      t->right = trees.first;
      NewSize(t);
      return {t, trees.second};
    }
    std::pair<Node*, Node*> trees = Split(t->left, x);
    t->left = trees.second;
    NewSize(t);
    return {trees.first, t};
  }

  Node* Merge(Node* t1, Node* t2) {
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

  Node* Exists(const int x) {
    if (root == nullptr) {
      return nullptr;
    }
    Node* now_node = root;
    while (now_node != nullptr) {
      if (x == now_node->key) {
        return now_node;
      }
      if (x <= now_node->key) {
        now_node = now_node->left;
      } else {
        now_node = now_node->right;
      }
    }
    return nullptr;
  }

  Node* Insert(const int x) {
    Node* node = new Node(x, distribution_(gen_));
    if (root == nullptr) {
      return node;
    }
    std::pair<Node*, Node*> trees = Split(root, node->key);
    return Merge(Merge(trees.first, node), trees.second);
  }

  int64_t Sum(const int left, const int right) {
    std::pair<Node*, Node*> trees1 = Split(root, left);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, right + 1);
    int64_t ans = GetSum(trees2.first);
    root = Merge(Merge(trees1.first, trees2.first), trees2.second);
    return ans;
  }
};

int main() {
  Treap treap;
  int all_commands = 0;
  std::cin >> all_commands;
  char command = 0;
  int left = 0;
  int right = 0;
  for (int i = 0; i < all_commands; ++i) {
    std::cin >> command;
    if (command == '+') {
      std::cin >> left;
      if (treap.Exists(left) == nullptr) {
        treap.root = treap.Insert(left);
      }
      continue;
    }
    std::cin >> left >> right;
    std::cout << treap.Sum(left, right) << '\n';
  }
  return 0;
}
