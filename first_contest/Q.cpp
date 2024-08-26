#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stack>

std::pair<int64_t, std::pair<int, size_t>> Solution(const std::vector<int>& scores) {
  int64_t ans = 0;
  int left_ans = 0;
  size_t right_ans = 0;
  std::vector<int64_t> prefix(scores.size() + 1, 0);
  for (size_t i = 0; i < scores.size(); ++i) {
    prefix[i + 1] = prefix[i] + static_cast<int64_t>(scores[i]);
  }
  std::stack<int> minimums;
  for (size_t right = 0; right < scores.size() + 1; ++right) {
    while (!minimums.empty() && (right == scores.size() || scores[minimums.top()] > scores[right])) {
      auto min = static_cast<int64_t>(scores[minimums.top()]);
      minimums.pop();
      int left = 0;
      if (!minimums.empty()) {
        left = minimums.top();
      } else {
        left = -1;
      }
      if (ans <= (prefix[right] - prefix[left + 1]) * min) {
        if (ans == (prefix[right] - prefix[left + 1]) * min) {
          if (right_ans - left_ans <= right - left - 2) {
            right_ans = right;
            left_ans = left + 2;
          }
        } else {
          ans = (prefix[right] - prefix[left + 1]) * min;
          left_ans = left + 2;
          right_ans = right;
        }
      }
    }
    minimums.push(static_cast<int>(right));
  }
  return {ans, {left_ans, right_ans}};
}

int main() {
  int all = 0;
  std::cin >> all;
  std::vector<int> scores(all);
  for (int i = 0; i < all; ++i) {
    std::cin >> scores[i];
  }
  std::pair<int64_t, std::pair<int, size_t>> ans = Solution(scores);
  std::cout << ans.first << '\n';
  std::cout << ans.second.first << ' ' << ans.second.second;
  return 0;
}
