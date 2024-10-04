#include <iostream>
#include <string>
#include <vector>

void Prefix(const std::string& str, std::vector<int>& pi) {
  for (size_t i = 1; i < str.size(); ++i) {
    int k = pi[i - 1];
    while (str[i] != str[k] && k > 0) {
      k = pi[k - 1];
    }
    if (str[i] == str[k]) {
      pi[i] = k + 1;
    }
  }
}

int main() {
  std::string str;
  std::cin >> str;
  std::vector<int> pi(str.size(), 0);
  Prefix(str, pi);
  for (const auto& i : pi) {
    std::cout << i << ' ';
  }
  return 0;
}
