#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class FenwickTree {
 private:
  std::vector<std::vector<std::vector<int>>> farr_;

  int64_t Query(int x1, int y1, int z1) {
    int64_t sum = 0;
    for (int x = x1; x >= 0; x = (x & (x + 1)) - 1) {
      for (int y = y1; y >= 0; y = (y & (y + 1)) - 1) {
        for (int z = z1; z >= 0; z = (z & (z + 1)) - 1) {
          sum += static_cast<int64_t>(farr_[x][y][z]);
        }
      }
    }
    return sum;
  }

 public:
  explicit FenwickTree(int len) {
    farr_.resize(len, std::vector<std::vector<int>>(len, std::vector<int>(len, 0)));
  }

  void Update(int x1, int y1, int z1, int delta) {
    for (int x = x1; x < static_cast<int>(farr_.size()); x |= (x + 1)) {
      for (int y = y1; y < static_cast<int>(farr_.size()); y |= (y + 1)) {
        for (int z = z1; z < static_cast<int>(farr_.size()); z |= (z + 1)) {
          farr_[x][y][z] += delta;
        }
      }
    }
  }

  int64_t Sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    int64_t sum_x1_y1 = 0;
    int64_t sum_x2_y1 = 0;
    int64_t sum_x1_y2 = 0;
    if (x1 != 0) {
      sum_x1_y2 = Query(x1 - 1, y2, z2);
    }
    if (y1 != 0) {
      sum_x2_y1 = Query(x2, y1 - 1, z2);
    }
    if (x1 != 0 && y1 != 0) {
      sum_x1_y1 = Query(x1 - 1, y1 - 1, z2);
    }
    int64_t sum_x1_y1_z2 = Query(x2, y2, z2) + sum_x1_y1 - sum_x2_y1 - sum_x1_y2;
    int64_t sum_x2_y2 = 0;
    if (x1 != 0 && y1 != 0 && z1 != 0) {
      sum_x1_y1 = Query(x1 - 1, y1 - 1, z1 - 1);
    } else {
      sum_x1_y1 = 0;
    }
    if (y1 != 0 && z1 != 0) {
      sum_x2_y1 = Query(x2, y1 - 1, z1 - 1);
    } else {
      sum_x2_y1 = 0;
    }
    if (x1 != 0 && z1 != 0) {
      sum_x1_y2 = Query(x1 - 1, y2, z1 - 1);
    } else {
      sum_x1_y2 = 0;
    }
    if (z1 != 0) {
      sum_x2_y2 = Query(x2, y2, z1 - 1);
    }
    return sum_x1_y1_z2 + sum_x2_y1 + sum_x1_y2 - sum_x2_y2 - sum_x1_y1;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int len = 0;
  int x1 = 0;
  int y1 = 0;
  int z1 = 0;
  int x2 = 0;
  int y2 = 0;
  int z2 = 0;
  int add = 0;
  std::cin >> len;
  int command = 0;
  FenwickTree tree(len);
  while (command != 3) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> x1 >> y1 >> z1 >> add;
      tree.Update(x1, y1, z1, add);
    }
    if (command == 2) {
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      std::cout << tree.Sum(x1, y1, z1, x2, y2, z2) << '\n';
    }
  }
  return 0;
}
