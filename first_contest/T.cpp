#include <iostream>

class Node {
 public:
  Node* left = nullptr;
  Node* right = nullptr;
  int key;
  int priority;
  int size;
  int64_t sum;

  Node() = default;

  explicit Node(const int& x) : key(x), priority(rand() % 1000), sum(x) {
    size = 1;
  }
};

int64_t GetSum(const Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->sum;
}

void NewSize(Node* node) {
  if (node != nullptr) {
    node->size = 1;
    node->sum = node->key;
    if (node->left != nullptr) {
      node->size += node->left->size;
      node->sum += node->left->sum;
    }
    if (node->right != nullptr) {
      node->size += node->right->size;
      node->sum += node->right->sum;
    }
  }
}

class Treap {
 public:
  std::pair<Node*, Node*> Split(Node* t, const int& plase) {
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    int size_left = t->left != nullptr ? t->left->size : 0;
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

  Node* root = nullptr;

  Treap() = default;

  ~Treap() {
    Clear(root);
  }

  void Insert(const int plase, const int x) {
    Node* node = new Node(x);
    if (root == nullptr) {
      root = node;
      return;
    }
    if (plase == -1) {
      root = Merge(root, node);
      return;
    }
    std::pair<Node*, Node*> trees = Split(root, plase);
    root = Merge(Merge(trees.first, node), trees.second);
  }

  int64_t Sum(const int& left, const int& right) {
    if (left > right) {
      return 0;
    }
    std::pair<Node*, Node*> trees1 = Split(root, left);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, right - left + 1);
    int64_t ans = GetSum(trees2.first);
    root = Merge(Merge(trees1.first, trees2.first), trees2.second);
    return ans;
  }

  void Swap(const int& left, const int& right, const int& first_len) {
    int left1 = (left + 1) / 2;
    int right1 = right / 2;
    int left2 = left / 2;
    int right2 = (right + 1) / 2 - 1;
    std::pair<Node*, Node*> big_trees = Split(root, first_len);
    std::pair<Node*, Node*> small1_trees1 = Split(big_trees.first, left1);
    std::pair<Node*, Node*> small1_trees2 = Split(small1_trees1.second, right1 - left1 + 1);
    std::pair<Node*, Node*> small2_trees1 = Split(big_trees.second, left2);
    std::pair<Node*, Node*> small2_trees2 = Split(small2_trees1.second, right2 - left2 + 1);
    root = Merge(Merge(Merge(small1_trees1.first, small2_trees2.first), small1_trees2.second),
                 Merge(Merge(small2_trees1.first, small1_trees2.first), small2_trees2.second));
  }
};

int main() {
  int all_commands = 0;
  int len = 0;
  std::cin >> len >> all_commands;
  int command = 0;
  int left = 0;
  int right = 0;
  int count = 0;
  int first_len = 0;
  while (len + all_commands > 0) {
    ++count;
    std::cout << "Swapper " << count << ":\n";
    auto t1 = new Treap;
    for (int i = 1; i < len + 1; ++i) {
      int var = 0;
      std::cin >> var;
      if (i % 2 == 1) {
        t1->Insert(i / 2, var);
      } else {
        t1->Insert(-1, var);
      }
    }
    first_len = len / 2 + len % 2;
    for (int i = 0; i < all_commands; ++i) {
      std::cin >> command >> left >> right;
      --left;
      --right;
      if (command == 1) {
        t1->Swap(left, right, first_len);
      } else {
        int64_t sum1 = t1->Sum((left + 1) / 2, right / 2);
        int64_t sum2 = t1->Sum(first_len + left / 2, first_len + (right + 1) / 2 - 1);
        std::cout << sum1 + sum2 << '\n';
      }
    }
    delete t1;
    std::cin >> len >> all_commands;
  }
  return 0;
}
