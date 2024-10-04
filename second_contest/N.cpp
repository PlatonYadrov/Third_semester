#include <iostream>
#include <string>
#include <map>
#include <vector>

class Node {
 public:
  int len;
  int link;
  std::map<char, int> next;

  Node() = default;

  Node(const int& a, const int& b, const std::map<char, int>& c) : len(a), link(b), next(c) {
  }
};

class SuffixAutomation {
 private:
  int last_;
  std::vector<Node> state_;

  void AddChar(const char& c) {
    state_.emplace_back(0, -1, std::map<char, int>());
    int now = static_cast<int>(state_.size()) - 1;
    state_[now].len = state_[last_].len + 1;
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
    state_.emplace_back(state_[p].len + 1, state_[q].link, state_[q].next);
    int clone = static_cast<int>(state_.size()) - 1;
    while (p >= 0 && state_[p].next[c] == q) {
      state_[p].next[c] = clone;
      p = state_[p].link;
    }
    state_[now].link = clone;
    state_[q].link = clone;
    last_ = now;
  }

 public:
  explicit SuffixAutomation(const std::string& str) : last_(0) {
    state_.emplace_back(0, -1, std::map<char, int>());
    for (auto s : str) {
      AddChar(s);
    }
  }

  void Print() {
    std::cout << state_.size() << '\n';
    for (size_t i = 0; i < state_.size(); ++i) {
      for (auto st : state_[i].next) {
        std::cout << i << ' ' << st.first << ' ' << st.second << '\n';
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::cin >> str;
  SuffixAutomation suff(str);
  suff.Print();
  return 0;
}
