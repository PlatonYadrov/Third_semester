#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int Prefix(const std::string& str) {
  std::vector<int> pi(str.size(), 0);
  for (size_t i = 1; i < str.size(); ++i) {
    int k = pi[i - 1];
    while (str[i] != str[k] && k > 0) {
      k = pi[k - 1];
    }
    if (str[i] == str[k]) {
      pi[i] = k + 1;
    }
  }
  return pi[static_cast<int>(str.size()) - 1];
}

int main() {
  int len = 0;
  std::cin >> len;
  std::string str1;
  std::string str2;
  std::cin >> str1;
  for (int i = 1; i < len; ++i) {
    std::cin >> str2;
    int len1 = static_cast<int>(str1.size());
    int len2 = static_cast<int>(str2.size());
    std::string temp_str;
    if (len2 >= len1) {
      temp_str += str2 + "#" + str1;
    } else {
      temp_str += str2 + "#" + std::string(str1.begin() + len1 - len2, str1.end());
    }
    int max_pref = Prefix(temp_str);
    str1 += std::string(str2.begin() + max_pref, str2.end());
  }
  std::cout << str1;
  return 0;
}
