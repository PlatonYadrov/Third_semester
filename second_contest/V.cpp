#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

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
 public:
  int last;
  std::vector<Node> state;

  void AddChar(const char& c) {
    state.emplace_back(0, -1, std::map<char, int>());
    int now = static_cast<int>(state.size()) - 1;
    state[now].len = state[last].len + 1;
    state[now].end_pos = state[last].end_pos + 1;
    int p = last;
    while (p >= 0 && !state[p].next.count(c)) {
      state[p].next[c] = now;
      p = state[p].link;
    }
    if (p == -1) {
      state[now].link = 0;
      last = now;
      return;
    }
    int q = state[p].next[c];
    if (state[q].len == state[p].len + 1) {
      state[now].link = q;
      last = now;
      return;
    }
    state.emplace_back(state[p].len + 1, state[q].link, state[q].next);
    int clone = static_cast<int>(state.size()) - 1;
    state[clone].end_pos = state[q].end_pos;
    while (p >= 0 && state[p].next[c] == q) {
      state[p].next[c] = clone;
      p = state[p].link;
    }
    state[now].link = clone;
    state[q].link = clone;
    last = now;
  }
  SuffixAutomation() = default;

  explicit SuffixAutomation(const std::string& str) : last(0) {
    state.emplace_back(0, -1, std::map<char, int>());
    state[0].end_pos = -1;
    for (auto s : str) {
      AddChar(s);
    }
  }
};

class Node1 {
 public:
  int begin;
  int len;
  std::map<char, int> transitions;

  Node1() = default;
};

class SuffixTree : public SuffixAutomation {
 public:
  std::vector<Node1> states_tree;
  int size;
  std::string str;

  void Extract(SuffixAutomation& suff, int id) {
    int suff_id = suff.state[id].link;
    states_tree[id].begin = static_cast<int>(str.size()) - 1 - (suff.state[id].end_pos - suff.state[suff_id].len);
    states_tree[id].len = suff.state[id].len - suff.state[suff_id].len;
    states_tree[suff_id].transitions[str[states_tree[id].begin]] = id;
  }

  explicit SuffixTree(const std::string& s) : str(s) {
    std::string r_str(s);
    std::reverse(r_str.begin(), r_str.end());
    SuffixAutomation suff(r_str);
    size = static_cast<int>(suff.state.size());
    states_tree.resize(suff.state.size());
    states_tree[0].begin = -1;
    states_tree[0].len = 0;
    for (int i = 1; i <= static_cast<int>(suff.state.size()) - 1; ++i) {
      Extract(suff, i);
    }
  }

  void Print() {
    std::cout << size << '\n';
    for (int i = 0; i < size; ++i) {
      for (auto st : states_tree[i].transitions) {
        std::cout << i << ' ' << st.first << ' ' << states_tree[st.second].len << ' ' << st.second << '\n';
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
  SuffixTree suff(str + "#");
  suff.Print();
  return 0;
}
