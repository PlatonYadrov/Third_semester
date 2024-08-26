#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class Node {
 public:
  int pairs;
  int open;
  int closed;

  Node() = default;
  Node(int pairs, int open, int closed) : pairs(pairs), open(open), closed(closed) {
  }
};

class SegmentTree {
 private:
  std::vector<Node> tree_;
  int n_ = 0;

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
  explicit SegmentTree(const std::vector<int>& str) {
    int len = 1 << static_cast<int>(std::ceil(std::log2(str.size())));
    n_ = len;
    for (int i = 0; i < 2 * len - 1; ++i) {
      if (i < len - 1 || i >= len + static_cast<int>(str.size()) - 1) {
        tree_.emplace_back(0, 0, 0);
      } else {
        tree_.emplace_back(0, 0, 0);
        tree_[i].open = str[i - len + 1] == 1 ? 1 : 0;
        tree_[i].closed = str[i - len + 1] == 0 ? 1 : 0;
      }
    }
    for (int i = len - 2; i >= 0; --i) {
      int min_op_cl = std::min(tree_[Left(i)].open, tree_[Right(i)].closed);
      tree_[i].pairs = tree_[Left(i)].pairs + tree_[Right(i)].pairs + min_op_cl;
      tree_[i].open = tree_[Left(i)].open + tree_[Right(i)].open - min_op_cl;
      tree_[i].closed = tree_[Left(i)].closed + tree_[Right(i)].closed - min_op_cl;
    }
  }

  Node Query(int left, int right, int left_v, int right_v, int vertex) {
    if (left > right_v || right < left_v) {
      Node tmp(0, 0, 0);
      return tmp;
    }
    if (left >= left_v && right <= right_v) {
      return tree_[vertex];
    }
    int mid = (left + right) / 2;
    Node l = Query(left, mid, left_v, right_v, Left(vertex));
    Node r = Query(mid + 1, right, left_v, right_v, Right(vertex));
    Node res(0, 0, 0);
    int min_op_cl = std::min(l.open, r.closed);
    res.pairs = l.pairs + r.pairs + min_op_cl;
    res.open = l.open + r.open - min_op_cl;
    res.closed = l.closed + r.closed - min_op_cl;
    return res;
  }

  int Max(int left, int right) {
    Node res = Query(n_ - 1, 2 * n_ - 2, left + n_ - 1, right + n_ - 1, 0);
    return 2 * res.pairs;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string str;
  std::cin >> str;
  std::vector<int> new_str;
  for (auto i : str) {
    if (i == '(') {
      new_str.push_back(1);
    } else {
      new_str.push_back(0);
    }
  }
  SegmentTree tree(new_str);
  int requests = 0;
  std::cin >> requests;
  int left = 0;
  int right = 0;
  for (int i = 0; i < requests; ++i) {
    std::cin >> left >> right;
    std::cout << tree.Max(left - 1, right - 1) << '\n';
  }
  return 0;
}
