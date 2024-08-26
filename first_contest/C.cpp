#include <iostream>
#include <cmath>
#include <vector>

class SparseTable {
 private:
  std::vector<std::vector<int64_t>> table_;
  std::vector<int64_t> precalculation_;

 public:
  explicit SparseTable(const std::vector<int64_t>& scores) {
    auto len = static_cast<int64_t>(scores.size());
    table_.resize(static_cast<int64_t>(std::ceil(std::log2(scores.size()))) + 1,
                  std::vector<int64_t>(scores.size() + 1, 0));
    for (size_t k = 0; k < table_.size(); ++k) {
      if (k == 0) {
        for (size_t i = 0; i < scores.size(); ++i) {
          table_[k][i] = scores[i];
        }
      } else {
        for (int64_t i = 0; i <= len - Pow2(k); ++i) {
          table_[k][i] = std::min(table_[k - 1][i], table_[k - 1][std::min(i + Pow2(k - 1), len - 1)]);
        }
      }
    }
    for (size_t i = 1; i < scores.size() + 1; ++i) {
      precalculation_.push_back(static_cast<int64_t>(std::trunc(std::log2(i))));
    }
  }

  int64_t RMQ(int64_t left, int64_t right) {
    if (left == right) {
      return table_[0][left];
    }
    int64_t k = precalculation_[right - left];
    return std::min(table_[k][left], table_[k][right + 1 - Pow2(k)]);
  }

  int64_t Pow2(size_t k) {
    return 1 << k;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t all = 0;
  int64_t requests = 0;
  std::cin >> all >> requests;
  std::vector<int64_t> scores(all);
  for (int64_t i = 0; i < all; ++i) {
    std::cin >> scores[i];
  }
  int64_t left = 0;
  int64_t right = 0;
  SparseTable st(scores);
  for (int64_t i = 0; i < requests; ++i) {
    std::cin >> left >> right;
    std::cout << st.RMQ(left - 1, right - 1) << '\n';
  }
  return 0;
}
