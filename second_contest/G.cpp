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

char KMP(const std::string& text, const std::string& pattern) {
  std::string str;
  str += pattern + "#" + text;
  std::vector<int> pi(str.size(), 0);
  Prefix(str, pi);
  int coincidence = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (pi[i] == static_cast<int>(pattern.size())) {
      ++coincidence;
      if (coincidence == 2) {
        return text[i - pattern.size()];
      }
    }
  }
  return 'i';
}

std::string Check(const std::string& text, const std::string& pattern) {
  std::string new_text;
  new_text = "1" + text + "1" + text + "1" + text + "1" + text;
  char shot = KMP(new_text, pattern);
  new_text = "0" + text + "0" + text + "0" + text + "0" + text;
  char not_shot = KMP(new_text, pattern);
  if (shot != 'i' && not_shot != 'i') {
    return "Random";
  }
  if (shot == '0' || not_shot == '0') {
    return "No";
  }
  return "Yes";
}

int main() {
  int len = 0;
  std::cin >> len;
  std::string text;
  std::string pattern;
  std::cin >> text >> pattern;
  std::string str;
  std::cout << Check(text, pattern);
  return 0;
}
