#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

size_t Max(const std::vector<int>& pi) {
  int max = 0;
  for (const auto i : pi) {
    if (i > max) {
      max = i;
    }
  }
  return static_cast<size_t>(max);
}

size_t Count(const std::string& str) {
  size_t count = 0;
  std::string temp;
  for (size_t i = 0; i < str.size(); ++i) {
    temp += str[i];
    std::reverse(temp.begin(), temp.end());
    std::vector<int> pi(temp.size(), 0);
    Prefix(temp, pi);
    std::reverse(temp.begin(), temp.end());
    count += temp.size() - Max(pi);
  }
  return count;
}

int main() {
  std::string str;
  std::cin >> str;
  std::cout << Count(str);
  return 0;
}
