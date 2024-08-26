#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stack>

class Node {
 public:
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int key = 0;
  int priority = 0;
  int size = 0;

  Node() = default;

  explicit Node(int x) : key(x) {
    priority = std::rand();
    size = 1;
  }
};

int GetSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

void NewSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
  }
}

class Treap {
 public:
  Node* root = nullptr;

  Treap() = default;

  ~Treap() {
    Clear(root);
  }

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
    if (t2->priority < t1->priority) {
      t2->left = Merge(t1, t2->left);
      NewSize(t2);
      return t2;
    }
    t1->right = Merge(t1->right, t2);
    NewSize(t1);
    return t1;
  }

  Node* Insert(const int x) {
    Node* node = new Node(x);
    if (root == nullptr) {
      return node;
    }
    std::pair<Node*, Node*> trees = Split(root, node->key);
    return Merge(Merge(trees.first, node), trees.second);
  }

  Node* Delete(Node* now_node, const int x) {
    if (now_node == nullptr) {
      return nullptr;
    }
    std::pair<Node*, Node*> trees1 = Split(now_node, x);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, x + 1);
    delete trees2.first;
    return Merge(trees1.first, trees2.second);
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

  Node* Next(const int x) {
    Node* cur = root;
    Node* last = nullptr;
    while (cur != nullptr) {
      if (cur->key <= x) {
        cur = cur->right;
      } else {
        last = cur;
        cur = cur->left;
      }
    }
    return last;
  }

  Node* Prev(const int x) {
    Node* cur = root;
    Node* last = nullptr;
    while (cur != nullptr) {
      if (cur->key >= x) {
        cur = cur->left;
      } else {
        last = cur;
        cur = cur->right;
      }
    }
    return last;
  }

  Node* Kth(Node* now_node, const int x) {
    if (now_node == nullptr || x >= GetSize(now_node)) {
      return nullptr;
    }
    int size = GetSize(now_node->left);
    if (size == x) {
      return now_node;
    }
    if (size < x) {
      return Kth(now_node->right, x - size - 1);
    }
    return Kth(now_node->left, x);
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
};

int main() {
  std::string commamd;
  int number = 0;
  Treap tree;
  while (std::cin >> commamd) {
    std::cin >> number;
    if (commamd == "insert") {
      if (tree.Exists(number) == nullptr) {
        tree.root = tree.Insert(number);
      }
      continue;
    }
    if (commamd == "delete") {
      if (tree.Exists(number) != nullptr) {
        tree.root = tree.Delete(tree.root, number);
      }
      continue;
    }
    if (commamd == "exists") {
      if (tree.Exists(number) == nullptr) {
        std::cout << "false\n";
      } else {
        std::cout << "true\n";
      }
      continue;
    }
    if (commamd == "next") {
      Node* tmp = tree.Next(number);
      if (tmp == nullptr) {
        std::cout << "none\n";
      } else {
        std::cout << tmp->key << '\n';
      }
      continue;
    }
    if (commamd == "prev") {
      Node* tmp = tree.Prev(number);
      if (tmp == nullptr) {
        std::cout << "none\n";
      } else {
        std::cout << tmp->key << '\n';
      }
      continue;
    }
    if (commamd == "kth") {
      if (number < 0) {
        std::cout << "none\n";
      } else {
        Node* ans = tree.Kth(tree.root, number);
        if (ans == nullptr) {
          std::cout << "none\n";
        } else {
          std::cout << ans->key << '\n';
        }
      }
      continue;
    }
  }
  return 0;
}
