#include <iostream>
#include <string>
#include <vector>
#include <map>

class Node {
 public:
  Node() {
    is_terminal = false;
  }
  std::map<char, int> letters;
  bool is_terminal;
};

class Trie {
 public:
  Trie() {
    trie.resize(1);
  }
  std::vector<Node> trie;
  std::string str_max;
  int max_id = 0;
  std::vector<char> res;

  void Insert(const std::string& str) {
    int vertex = 0;
    int next_vertex = 0;
    for (auto s : str) {
      next_vertex = trie[vertex].letters[s];
      if (next_vertex == 0) {
        trie.emplace_back();
        next_vertex = static_cast<int>(trie.size()) - 1;
        trie[vertex].letters[s] = next_vertex;
      }
      vertex = next_vertex;
    }
    trie[vertex].is_terminal = true;
  }

  void Print(int id, bool find) {
    if (trie[id].is_terminal) {
      res.push_back('P');
    }
    if (!trie[id].is_terminal || !trie[id].letters.empty()) {
      for (auto element : trie[id].letters) {
        if (!find || element.first != str_max[max_id]) {
          res.push_back(element.first);
          Print(element.second, false);
          res.push_back('-');
        }
      }
      if (find) {
        res.push_back(str_max[max_id]);
        ++max_id;
        Print(trie[id].letters[str_max[max_id - 1]], true);
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int amount = 0;
  std::cin >> amount;
  Trie trie;
  size_t max = 0;
  for (int i = 0; i < amount; ++i) {
    std::string surname;
    std::cin >> surname;
    trie.Insert(surname);
    if (max < surname.size()) {
      max = surname.size();
      trie.str_max = surname;
    }
  }
  trie.Print(0, true);
  std::cout << trie.res.size() << '\n';
  for (auto element : trie.res) {
    std::cout << element << '\n';
  }
  return 0;
}
