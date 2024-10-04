#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void Prefix(const std::vector<int>& str, std::vector<size_t>& z) {
  size_t left = 0;
  size_t right = 0;
  for (size_t i = 1; i < str.size(); ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < str.size() && str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
}

void Ans(const std::vector<size_t>& z) {
  size_t len = z.size() / 2;
  size_t plase_mirror = (len + 1) / 2;
  for (size_t i = len % 2; i < len - 1; i += 2) {
    if (z[len + i] >= plase_mirror - i) {
      std::cout << plase_mirror << ' ';
    }
    ++plase_mirror;
  }
  std::cout << len;
}

int main() {
  int len = 0;
  int colors = 0;
  std::cin >> len >> colors;
  std::vector<int> str(2 * len, 0);
  for (int i = 0; i < len; ++i) {
    std::cin >> str[i];
    str[2 * len - 1 - i] = str[i];
  }
  std::vector<size_t> z(str.size(), 0);
  Prefix(str, z);
  Ans(z);
  return 0;
}
