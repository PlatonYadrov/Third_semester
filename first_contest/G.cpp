#include <iostream>
#include <vector>
#include <cmath>

class SegmentTree {
 private:
  std::vector<std::pair<int, int>> tree_;

  int Parent(int i) {
    return ((i - 1) / 2);
  }

  int Left(int i) {
    return 2 * i + 1;
  }

  int Right(int i) {
    return 2 * i + 2;
  }

  bool IsLeftSon(int i) {
    return (i % 2 == 1);
  }

  bool IsRightSon(int i) {
    return (i % 2 == 0);
  }

 public:
  explicit SegmentTree(const std::vector<int>& scores) {
    int len = 1 << static_cast<int>(std::ceil(std::log2(scores.size())));
    for (int i = 0; i < 2 * len - 1; ++i) {
      if (i < len - 1 || i >= len + static_cast<int>(scores.size()) - 1) {
        tree_.emplace_back(-1, 1);
      } else {
        tree_.emplace_back(scores[i - len + 1], 1);
      }
    }
    for (int i = len - 2; i >= 0; --i) {
      tree_[i].first = std::max(tree_[Left(i)].first, tree_[Right(i)].first);
      if (tree_[Left(i)].first == tree_[Right(i)].first) {
        tree_[i].second = tree_[Left(i)].second + tree_[Right(i)].second;
      } else {
        if (tree_[Left(i)].first < tree_[Right(i)].first) {
          tree_[i].second = tree_[Right(i)].second;
        } else {
          tree_[i].second = tree_[Left(i)].second;
        }
      }
    }
  }

  std::pair<int, int> Max(int left, int right) {
    left += ((static_cast<int>(tree_.size())) + 1) / 2 - 1;
    right += ((static_cast<int>(tree_.size())) + 1) / 2 - 1;
    std::pair<int, int> res = std::make_pair(-1, 1);
    while (left < right) {
      if (IsRightSon(left)) {
        if (res.first == tree_[left].first) {
          res.second += tree_[left].second;
        } else {
          if (res.first < tree_[left].first) {
            res.second = tree_[left].second;
          }
        }
        res.first = std::max(res.first, tree_[left].first);
      }
      if (IsLeftSon(right)) {
        if (res.first == tree_[right].first) {
          res.second += tree_[right].second;
        } else {
          if (res.first < tree_[right].first) {
            res.second = tree_[right].second;
          }
        }
        res.first = std::max(res.first, tree_[right].first);
      }
      left = Parent(left + 1);
      right = Parent(right - 1);
    }
    if (left == right) {
      if (res.first == tree_[left].first) {
        res.second += tree_[left].second;
      } else {
        if (res.first < tree_[left].first) {
          res.second = tree_[left].second;
        }
      }
      res.first = std::max(res.first, tree_[left].first);
    }
    return res;
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
  for (int i = 0; i < requests; ++i) {
    std::cin >> left >> right;
    std::pair<int, int> my_max = tree.Max(left - 1, right - 1);
    std::cout << my_max.first << ' ' << my_max.second << '\n';
  }
  return 0;
}
