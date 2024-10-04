#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

class Node {
 public:
  Node() = default;
  std::map<char, int> letters;
  std::vector<std::pair<std::pair<int, int>, int>> borders;
  int link;
  int exit_link;
  int id;
  int len;
  bool is_terminal;
};

class Suffix {
 public:
  char letter;
  int root;
  int vertex;

  Suffix(const char letter, int root, int vertex) : letter(letter), root(root), vertex(vertex) {
  }

  Suffix() = default;
};

class Trie {
 private:
  std::vector<Node> trie_;

  void Insert(const std::string& str, const int& id, const int& left, const int& right) {
    int vertex = 0;
    int next_vertex = 0;
    for (auto s : str) {
      next_vertex = trie_[vertex].letters[s];
      if (next_vertex == 0) {
        trie_.emplace_back();
        next_vertex = static_cast<int>(trie_.size()) - 1;
        trie_[vertex].letters[s] = next_vertex;
      }
      vertex = next_vertex;
    }
    trie_[vertex].is_terminal = true;
    trie_[vertex].id = id;
    trie_[vertex].len = static_cast<int>(str.size());
    trie_[vertex].borders.push_back({{left, right}, id});
  }

  void BuildSuffixReferences() {
    trie_[0].link = -1;
    std::queue<Suffix> q;
    for (auto v : trie_[0].letters) {
      q.emplace(v.first, 0, v.second);
    }
    while (!q.empty()) {
      Suffix temp = q.front();
      q.pop();
      int id_suff = temp.root;
      int suff_link = trie_[id_suff].link;
      while (suff_link != -1 && trie_[suff_link].letters.find(temp.letter) == trie_[suff_link].letters.end()) {
        suff_link = trie_[id_suff].link;
        id_suff = suff_link;
      }
      trie_[temp.vertex].link = suff_link == -1 ? 0 : trie_[suff_link].letters[temp.letter];
      for (auto l : trie_[temp.vertex].letters) {
        q.emplace(l.first, temp.vertex, l.second);
      }
    }
  }

  void BuildExitSuffixReferences() {
    trie_[0].exit_link = -1;
    std::queue<int> q;
    for (auto v : trie_[0].letters) {
      q.push(v.second);
    }
    while (!q.empty()) {
      int temp = q.front();
      q.pop();
      int suff_link = trie_[temp].link;
      if (suff_link != 0) {
        trie_[temp].exit_link = trie_[suff_link].is_terminal ? suff_link : trie_[suff_link].exit_link;
      }
      for (auto l : trie_[temp].letters) {
        q.push(l.second);
      }
    }
  }

 public:
  std::vector<bool> check;

  explicit Trie(const int& size) {
    trie_.resize(1);
    check.resize(size);
    for (int i = 0; i < size; ++i) {
      std::string str;
      int left = 0;
      int right = 0;
      std::cin >> left >> right >> str;
      Insert(str, i, left, right);
    }
    BuildSuffixReferences();
    BuildExitSuffixReferences();
  }

  int NextState(int vertex, char letter) {
    while (vertex != -1 && trie_[vertex].letters.find(letter) == trie_[vertex].letters.end()) {
      vertex = trie_[vertex].link;
    }
    return (vertex == -1 ? 0 : trie_[vertex].letters[letter]);
  }

  void PrintEntries(int id, int node_id) {
    if (!trie_[node_id + id - id].is_terminal) {
      node_id = trie_[node_id].exit_link;
    }
    while (node_id != 0 && node_id != -1) {
      for (size_t i = 0; i < trie_[node_id].borders.size(); ++i) {
        if (id < trie_[node_id].borders[i].first.second &&
            id - trie_[node_id].len + 2 >= trie_[node_id].borders[i].first.first) {
          check[trie_[node_id].borders[i].second] = true;
        }
      }
      node_id = trie_[node_id].exit_link;
    }
  }
};

void AhoCorasik(const std::string& str, const int& patterns) {
  Trie trie(patterns);
  int node = 0;
  for (int i = 0; i < static_cast<int>(str.size()); ++i) {
    node = trie.NextState(node, str[i]);
    trie.PrintEntries(i, node);
  }
  for (auto pattern : trie.check) {
    if (pattern) {
      std::cout << '+';
    } else {
      std::cout << '-';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::cin >> str;
  int patterns = 0;
  std::cin >> patterns;
  AhoCorasik(str, patterns);
  return 0;
}
