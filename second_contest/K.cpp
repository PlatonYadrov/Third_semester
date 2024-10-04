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

  bool Find(const std::string& str) {
    Node vertex = trie[0];
    int next_vertex = 0;
    for (auto s : str) {
      next_vertex = vertex.letters[s];
      if (next_vertex == 0) {
        return false;
      }
      vertex = trie[next_vertex];
    }
    return vertex.is_terminal;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string command;
  std::string word;
  Trie trie;
  while (true) {
    std::cin >> command;
    if (command == "#") {
      break;
    }
    std::cin >> word;
    if (command == "+") {
      trie.Insert(word);
      continue;
    }
    if (trie.Find(word)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
  return 0;
}
