#include <iostream>
#include <cmath>
#include <vector>

class SparseTable {
 private:
  std::vector<std::vector<std::vector<std::vector<int>>>> table_;
  std::vector<int> precalculation_;

 public:
  explicit SparseTable(const std::vector<std::vector<int>>& scores) {
    size_t n = scores.size();
    size_t m = scores[0].size();
    table_.resize(n,
                  std::vector<std::vector<std::vector<int>>>(
                      m, std::vector<std::vector<int>>(static_cast<size_t>(std::log2(n)) + 1,
                                                       std::vector<int>(static_cast<size_t>(std::log2(m)) + 1, 1e9))));
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < m; ++j) {
        table_[i][j][0][0] = scores[i][j];
      }
    }
    for (size_t i = 0; i < n; ++i) {
      for (size_t k = 1; k <= static_cast<size_t>(std::log2(m)); ++k) {
        for (size_t j = 0; j + Pow2(k) - 1 < m; ++j) {
          table_[i][j][0][k] = std::min(table_[i][j][0][k - 1], table_[i][j + Pow2(k - 1)][0][k - 1]);
        }
      }
    }
    for (size_t k = 1; k <= static_cast<size_t>(std::log2(n)); ++k) {
      for (size_t i = 0; i + Pow2(k) - 1 < n; ++i) {
        for (size_t l = 0; l <= static_cast<size_t>(std::log2(m)); ++l) {
          for (size_t j = 0; j + Pow2(l) - 1 < m; ++j) {
            table_[i][j][k][l] = std::min(table_[i][j][k - 1][l], table_[i + Pow2(k - 1)][j][k - 1][l]);
          }
        }
      }
    }
  }

  int RMQ(int x1, int y1, int x2, int y2) {
    auto k = static_cast<size_t>(std::log2(x2 - x1 + 1));
    auto l = static_cast<size_t>(std::log2(y2 - y1 + 1));
    return std::min(std::min(table_[x1][y1][k][l], table_[x2 - Pow2(k) + 1][y1][k][l]),
                    std::min(table_[x1][y2 - Pow2(l) + 1][k][l], table_[x2 - Pow2(k) + 1][y2 - Pow2(l) + 1][k][l]));
  }

  int Pow2(size_t k) {
    return 1 << k;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int all_x = 0;
  int all_y = 0;
  int requests = 0;
  std::cin >> all_y >> all_x;
  std::vector<std::vector<int>> scores(all_y, std::vector<int>(all_x, 0));
  for (int i = 0; i < all_y; ++i) {
    for (int j = 0; j < all_x; ++j) {
      std::cin >> scores[i][j];
    }
  }
  std::cin >> requests;
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
  SparseTable st(scores);
  for (int i = 0; i < requests; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << st.RMQ(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
  }
  return 0;
}
