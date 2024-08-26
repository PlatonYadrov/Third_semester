#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class FenwickTree {
 private:
  std::vector<int64_t> farr_;

  int64_t Query(int64_t r) {
    int64_t sum = 0;
    for (int64_t i = r; i >= 0; i = (i & (i + 1)) - 1) {
      sum += farr_[i];
    }
    return sum;
  }

 public:
  explicit FenwickTree(const std::vector<int64_t>& scores) {
    farr_.resize(scores.size(), 0);
    for (int64_t i = 0; i < static_cast<int64_t>(scores.size()); ++i) {
      Update(i, scores[i]);
    }
  }

  void Update(int64_t k, int64_t delta) {
    for (int64_t i = k; i < static_cast<int64_t>(farr_.size()); i |= (i + 1)) {
      farr_[i] += delta;
    }
  }

  int64_t Sum(int64_t left, int64_t right) {
    if (left > 0) {
      return (Query(right) - Query(left - 1));
    }
    return Query(right);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t all = 0;
  int64_t requests = 0;
  std::cin >> all;
  std::vector<int64_t> scores(all);
  for (int64_t i = 0; i < all; ++i) {
    std::cin >> scores[i];
  }
  std::cin >> requests;
  int64_t left = 0;
  int64_t right = 0;
  FenwickTree tree(scores);
  std::string command;
  for (int64_t i = 0; i < requests; ++i) {
    std::cin >> command;
    std::cin >> left >> right;
    if (command == "u") {
      tree.Update(left - 1, right - scores[left - 1]);
      scores[left - 1] = right;
    } else {
      std::cout << tree.Sum(left - 1, right - 1) << ' ';
    }
  }
  return 0;
}
