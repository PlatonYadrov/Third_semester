#include <iostream>

class Node {
 public:
  Node* left = nullptr;
  Node* right = nullptr;
  int key;
  u_int64_t priority;
  int size;
  int sum;
  int add;

  Node() = default;

  explicit Node(const int& x) : key(x), sum(x) {
    priority = rand() % 10001;
    size = 1;
    add = 0;
  }
};

int GetSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

int GetSum(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->sum + node->add * node->size;
}

void NewSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
    node->sum = GetSum(node->left) + GetSum(node->right) + node->key;
  }
}

void Push(Node* node) {
  if (node != nullptr && node->add != 0) {
    node->key += node->add;
    node->sum += node->add * node->size;
    if (node->left != nullptr) {
      node->left->add += node->add;
    }
    if (node->right != nullptr) {
      node->right->add += node->add;
    }
    node->add = 0;
  }
}

class Treap {
 public:
  std::pair<Node*, Node*> Split(Node* t, const int& plase) {
    Push(t);
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
    Push(t1);
    Push(t2);
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

  void Insert(const int& x) {
    Node* node = new Node(x);
    if (root == nullptr) {
      root = node;
      return;
    }
    root = Merge(root, node);
  }

  int Sum(const int& left, const int& right) {
    std::pair<Node*, Node*> trees1 = Split(root, left);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, right - left + 1);
    int ans = GetSum(trees2.first);
    root = Merge(Merge(trees1.first, trees2.first), trees2.second);
    return ans;
  }

  void Add(const int& left, const int& right, const int& delta) {
    std::pair<Node*, Node*> trees1 = Split(root, left);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, right - left + 1);
    trees2.first->add += delta;
    root = Merge(Merge(trees1.first, trees2.first), trees2.second);
  }

  int Get(const int plase) {
    std::pair<Node*, Node*> trees1 = Split(root, plase);
    std::pair<Node*, Node*> trees2 = Split(trees1.second, 1);
    int ans = trees2.first->key;
    root = Merge(Merge(trees1.first, trees2.first), trees2.second);
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Treap treap;
  int all_commands = 0;
  int len = 0;
  std::cin >> len >> all_commands;
  int command = 0;
  int left = 0;
  int right = 0;
  int delta = 0;
  for (int i = 0; i < len; ++i) {
    treap.Insert(0);
  }
  for (int i = 0; i < all_commands; ++i) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> left >> right >> delta;
      treap.Add(left, right - 1, delta);
    } else {
      std::cin >> left >> right;
      std::cout << treap.Sum(left, right - 1) << '\n';
    }
  }
  return 0;
}
