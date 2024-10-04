#include <iostream>
#include <string>
#include <map>
#include <vector>

class Node {
 public:
  int len;
  int link;
  int end_pos;
  std::map<char, int> next;

  Node() = default;

  Node(const int& a, const int& b, const std::map<char, int>& c) : len(a), link(b), next(c) {
  }
};

class SuffixAutomation {
 private:
  int last_;
  std::vector<Node> state_;

 public:
  void AddChar(const char& c) {
    state_.emplace_back(0, -1, std::map<char, int>());
    int now = static_cast<int>(state_.size()) - 1;
    state_[now].len = state_[last_].len + 1;
    state_[now].end_pos = state_[now].len - 1;
    int p = last_;
    while (p >= 0 && !state_[p].next.count(c)) {
      state_[p].next[c] = now;
      p = state_[p].link;
    }
    if (p == -1) {
      state_[now].link = 0;
      last_ = now;
      return;
    }
    int q = state_[p].next[c];
    if (state_[q].len == state_[p].len + 1) {
      state_[now].link = q;
      last_ = now;
      return;
    }
    state_.emplace_back(0, -1, std::map<char, int>());
    int clone = static_cast<int>(state_.size()) - 1;
    state_[clone].len = state_[p].len + 1;
    while (p >= 0 && state_[p].next[c] == q) {
      state_[p].next[c] = clone;
      p = state_[p].link;
    }
    state_[clone].next = state_[q].next;
    state_[clone].link = state_[q].link;
    state_[clone].end_pos = state_[q].end_pos;
    state_[now].link = clone;
    state_[q].link = clone;
    last_ = now;
  }

  SuffixAutomation() : last_(0) {
    state_.emplace_back(0, -1, std::map<char, int>());
    state_[0].end_pos = 0;
  }

  bool Find(const int& len) {
    return state_[state_[last_].link].len < len;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  SuffixAutomation suff;
  int commands = 0;
  std::cin >> commands;
  for (int i = 0; i < commands; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "+") {
      char str = 0;
      std::cin >> str;
      suff.AddChar(str);
    } else {
      int position = 0;
      std::cin >> position;
      if (suff.Find(position)) {
        std::cout << "+\n";
      } else {
        std::cout << "-\n";
      }
    }
  }
}
