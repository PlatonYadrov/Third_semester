#include <iostream>
#include <string>
#include <map>
#include <vector>

class Node {
 public:
  int64_t len;
  int64_t link;
  int64_t res_prefix;
  std::map<char, int64_t> next;

  Node() = default;

  Node(const int64_t& a, const int64_t& b, const std::map<char, int64_t>& c) : len(a), link(b), next(c) {
  }
};

class SuffixAutomation {
 private:
  int64_t last_;
  std::vector<Node> state_;

  void AddChar(const char& c) {
    state_.emplace_back(0, -1, std::map<char, int64_t>());
    int64_t now = static_cast<int64_t>(state_.size()) - 1;
    state_[now].len = state_[last_].len + 1;
    int64_t p = last_;
    while (p >= 0 && !state_[p].next.count(c)) {
      state_[p].next[c] = now;
      p = state_[p].link;
    }
    if (p == -1) {
      state_[now].link = 0;
      state_[now].res_prefix = state_[now].len + state_[last_].res_prefix - state_[state_[now].link].len;
      std::cout << state_[now].res_prefix << '\n';
      last_ = now;
      return;
    }
    int64_t q = state_[p].next[c];
    if (state_[q].len == state_[p].len + 1) {
      state_[now].link = q;
      state_[now].res_prefix = state_[now].len + state_[last_].res_prefix - state_[state_[now].link].len;
      std::cout << state_[now].res_prefix << '\n';
      last_ = now;
      return;
    }
    state_.emplace_back(state_[p].len + 1, state_[q].link, state_[q].next);
    int64_t clone = static_cast<int64_t>(state_.size()) - 1;
    while (p >= 0 && state_[p].next[c] == q) {
      state_[p].next[c] = clone;
      p = state_[p].link;
    }
    state_[now].link = clone;
    state_[q].link = clone;
    state_[now].res_prefix = state_[now].len + state_[last_].res_prefix - state_[state_[now].link].len;
    std::cout << state_[now].res_prefix << '\n';
    last_ = now;
  }

 public:
  explicit SuffixAutomation(const std::string& str) : last_(0) {
    state_.emplace_back(0, -1, std::map<char, int64_t>());
    state_[0].res_prefix = 0;
    for (auto s : str) {
      AddChar(s);
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
  return 0;
}
