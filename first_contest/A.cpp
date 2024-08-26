#include <iostream>
#include <vector>

void Solution() {
  int64_t all_sculptures = 0;
  std::cin >> all_sculptures;
  std::vector<int64_t> scores(all_sculptures);
  std::vector<int64_t> prefix(all_sculptures + 1);
  prefix[0] = 0;
  for (int64_t i = 0; i < all_sculptures; ++i) {
    std::cin >> scores[i];
    prefix[i + 1] = prefix[i] + scores[i];
  }
  int64_t requests = 0;
  std::cin >> requests;
  int64_t left = 0;
  int64_t right = 0;
  for (int64_t i = 0; i < requests; ++i) {
    std::cin >> left >> right;
    std::cout << prefix[right] - prefix[left - 1] << ' ';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solution();
  return 0;
}
