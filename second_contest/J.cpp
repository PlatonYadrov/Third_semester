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

void Solution(const std::string& text, const std::string& pattern) {
  std::vector<size_t> z(text.size() + 1 + pattern.size(), 0);
  z[0] = z.size();
  int correct_word = 0;
  Prefix(text + "#" + pattern, z);
  size_t max_pos = text.size() + 1;
  size_t good_words = 0;
  std::vector<size_t> pos_pref(pattern.size());
  if (z[text.size() + 1] == 0) {
    correct_word = 1;
  } else {
    for (size_t i = text.size() + 1; i < text.size() + 1 + pattern.size(); ++i) {
      if (i >= max_pos && z[i] == 0) {
        correct_word = 1;
        break;
      }
      if (max_pos <= z[i] + i) {
        max_pos = z[i] + i;
        pos_pref[good_words] = i - text.size() - 1;
        ++good_words;
      }
    }
  }
  if (correct_word == 1) {
    std::cout << "Yes";
    return;
  }
  std::cout << "No\n";
  size_t new_pos = pos_pref[1];
  size_t last_pos = 0;
  for (size_t i = 1; i < good_words; ++i) {
    std::string tmp(pattern.begin() + static_cast<int>(last_pos), pattern.begin() + static_cast<int>(new_pos));
    std::cout << tmp << ' ';
    last_pos = new_pos;
    new_pos = pos_pref[(i + 1) % pattern.size()];
  }
  std::string tmp(pattern.begin() + static_cast<int>(last_pos), pattern.end());
  std::cout << tmp << '\n';
}

int main() {
  std::string text;
  std::string pattern;
  std::cin >> text >> pattern;
  Solution(text, pattern);
  return 0;
}
