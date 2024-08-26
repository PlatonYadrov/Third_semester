#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class Node {
 public:
  int key;
  int priority;
  int position;

  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;

  Node(int key, int priority, int position, Node* parent, Node* left, Node* right)
      : key(key), priority(priority), position(position), parent(parent), left(left), right(right) {
  }
};

class Treap {
 private:
  Node* root_;
  int size_;

 public:
  ~Treap() {
    Clear(root_);
  }

  explicit Treap(const std::vector<std::pair<int, int>>& p_key_var) {
    size_ = static_cast<int>(p_key_var.size());
    std::vector<Node*> p_key(size_);
    for (int i = 0; i < size_; ++i) {
      p_key[i] = new Node(p_key_var[i].first, p_key_var[i].second, i + 1, nullptr, nullptr, nullptr);
    }
    root_ = p_key[0] - 1 + 1;
    Node* last = p_key[0];
    for (auto& vertex : p_key) {
      if (vertex == root_) {
        continue;
      }
      Node* cur = last;
      while ((cur != nullptr) && (cur->priority > vertex->priority)) {
        cur = cur->parent;
      }
      if (cur == nullptr) {
        vertex->left = root_;
        if (root_ != nullptr) {
          root_->parent = vertex;
        }
        root_ = vertex;
      } else {
        vertex->left = cur->right;
        if (cur->right != nullptr) {
          cur->right->parent = vertex;
        }
        cur->right = vertex;
        vertex->parent = cur;
      }
      last = vertex;
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

  Node* Root() {
    return root_;
  }

  void Order(Node* root) {
    if (root) {
      Order(root->left);
      if (root->parent != nullptr) {
        std::cout << root->parent->position << ' ';
      } else {
        std::cout << 0 << ' ';
      }
      if (root->left != nullptr) {
        std::cout << root->left->position << ' ';
      } else {
        std::cout << 0 << ' ';
      }
      if (root->right != nullptr) {
        std::cout << root->right->position << '\n';
      } else {
        std::cout << 0 << '\n';
      }
      Order(root->right);
    }
  }
};

int main() {
  int vertex = 0;
  std::cin >> vertex;
  std::vector<std::pair<int, int>> p_key(vertex);
  for (int i = 0; i < vertex; ++i) {
    std::cin >> p_key[i].first >> p_key[i].second;
  }
  std::cout << "YES\n";
  Treap treap(p_key);
  treap.Order(treap.Root());
  return 0;
}
