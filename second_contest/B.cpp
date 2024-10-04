#include <iostream>
#include <string>
#include <vector>

std::string StringRecovery(const std::vector<int>& pi) {
  std::string ans;
  if (pi.empty()) {
    ans = "";
  } else {
    ans = "a";
    for (size_t i = 1; i < pi.size(); ++i) {
      if (pi[i] == 0) {
        std::vector<bool> used(26, false);
        int k = pi[i - 1];
        while (k > 0) {
          used[ans[k] - 'a'] = true;
          k = pi[k - 1];
        }
        char new_letter = 'b';
        while (used[new_letter - 'a']) {
          ++new_letter;
        }
        ans += new_letter;
      } else {
        ans += ans[pi[i] - 1];
      }
    }
  }
  return ans;
}

int main() {
  int len = 0;
  std::cin >> len;
  std::vector<int> pi(len);
  for (int i = 0; i < len; ++i) {
    std::cin >> pi[i];
  }
  std::cout << StringRecovery(pi);
  return 0;
}
