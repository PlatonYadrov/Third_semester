#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class SegmentTree {
 private:
  std::vector<std::pair<int, int>> tree_;
  int n_ = 0;

  int Parent(int i) {
    return ((i - 1) / 2);
  }

  int Left(int i) {
    return 2 * i + 1;
  }

  int Right(int i) {
    return 2 * i + 2;
  }

  void Push(int vertex) {
    tree_[vertex].first += tree_[vertex].second;
    tree_[Left(vertex)].second += tree_[vertex].second;
    tree_[Right(vertex)].second += tree_[vertex].second;
    tree_[vertex].second = 0;
  }

 public:
  explicit SegmentTree(const std::vector<int>& scores) {
    int len = 1 << static_cast<int>(std::ceil(std::log2(scores.size())));
    n_ = len;
    for (int i = 0; i < 2 * len - 1; ++i) {
      if (i < len - 1 || i >= len + static_cast<int>(scores.size()) - 1) {
        tree_.emplace_back(-1, 0);
      } else {
        tree_.emplace_back(scores[i - len + 1], 0);
      }
    }
    for (int i = len - 2; i >= 0; --i) {
      tree_[i].first = std::max(tree_[Left(i)].first, tree_[Right(i)].first);
      tree_[i].second = 0;
    }
  }

  int Max(int left, int right, int vertex, int v_left, int v_right) {
    if (v_right == -1) {
      v_right = 2 * n_ - 2;
      left += n_ - 1;
      right += n_ - 1;
      v_left = n_ - 1;
    }
    if (left <= v_left && v_right <= right) {
      return tree_[vertex].first + tree_[vertex].second;
    }
    if (left > v_right || right < v_left) {
      return 0;
    }
    Push(vertex);
    int l = Max(left, right, Left(vertex), v_left, (v_left + v_right) / 2);
    int r = Max(left, right, Right(vertex), (v_left + v_right) / 2 + 1, v_right);
    return std::max(l, r);
  }

  void Update(int left, int right, int vertex, int v_left, int v_right, int delta) {
    if (v_right == -1) {
      v_right = 2 * n_ - 2;
      left += n_ - 1;
      right += n_ - 1;
      v_left = n_ - 1;
    }
    if (left <= v_left && v_right <= right) {
      tree_[vertex].second += delta;
      return;
    }
    if (left > v_right || right < v_left) {
      return;
    }
    Push(vertex);
    Update(left, right, Left(vertex), v_left, (v_left + v_right) / 2, delta);
    Update(left, right, Right(vertex), (v_left + v_right) / 2 + 1, v_right, delta);
    int temp1 = tree_[Left(vertex)].first + tree_[Left(vertex)].second;
    int temp2 = tree_[Right(vertex)].first + tree_[Right(vertex)].second;
    tree_[vertex].first = std::max(temp1, temp2);
  }
};

int main() {
  int all = 0;
  std::cin >> all;
  std::vector<int> scores(all);
  for (int i = 0; i < all; ++i) {
    std::cin >> scores[i];
  }
  SegmentTree tree(scores);
  int requests = 0;
  std::cin >> requests;
  int left = 0;
  int right = 0;
  int add = 0;
  std::string command;
  for (int i = 0; i < requests; ++i) {
    std::cin >> command;
    if (command == "m") {
      std::cin >> left >> right;
      std::cout << tree.Max(left - 1, right - 1, 0, 0, -1) << ' ';
    } else {
      std::cin >> left >> right >> add;
      tree.Update(left - 1, right - 1, 0, 0, -1, add);
    }
  }
  return 0;
}
