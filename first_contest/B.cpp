#include <iostream>
#include <vector>

std::pair<std::pair<int64_t, int64_t>, int64_t> MaxScores(std::vector<int64_t>& scores) {
  int64_t sum = 0;
  int64_t min_sum = scores[0];
  int64_t left = 0;
  int64_t right = 0;
  int64_t new_pos = -1;
  for (int i = 0; i < static_cast<int64_t>(scores.size()); ++i) {
    sum += scores[i];
    if (sum > min_sum) {
      min_sum = sum;
      left = new_pos + 1;
      right = i;
    }
    if (sum < 0) {
      sum = 0;
      new_pos = i;
    }
  }
  return {{left, right}, min_sum};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t all_characters = 0;
  std::cin >> all_characters;
  std::vector<int64_t> scores(all_characters);
  for (int64_t i = 0; i < all_characters; ++i) {
    std::cin >> scores[i];
  }
  std::pair<std::pair<int64_t, int64_t>, int64_t> ans = MaxScores(scores);
  std::cout << ans.first.first + 1 << ' ' << ans.first.second + 1 << ' ' << ans.second;
  return 0;
}
