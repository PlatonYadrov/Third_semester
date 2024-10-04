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

void KMP(const std::string& text, const std::string& pattern) {
  std::string str;
  str += pattern + "#" + text;
  std::vector<int> pi(str.size(), 0);
  Prefix(str, pi);
  for (size_t i = 0; i < str.size(); ++i) {
    if (pi[i] == static_cast<int>(pattern.size())) {
      std::cout << i - 2 * pattern.size() << '\n';
    }
  }
}

int main() {
  std::string text;
  std::string pattern;
  std::cin >> text >> pattern;
  std::string str;
  KMP(text, pattern);
  return 0;
}
