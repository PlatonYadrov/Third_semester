#include <iostream>
#include <string>
#include <vector>

void Prefix(const std::string& str, std::vector<size_t>& z) {
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

int main() {
  std::string str;
  std::cin >> str;
  std::vector<size_t> z(str.size(), 0);
  z[0] = str.size();
  Prefix(str, z);
  for (const auto& i : z) {
    std::cout << i << ' ';
  }
  return 0;
}
