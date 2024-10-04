#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <set>

int GenBase(const int before, const int after) {
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 mt_rand(seed);
  int base = std::uniform_int_distribution<int>(before + 1, after)(mt_rand);
  return base % 2 == 0 ? base - 1 : base;
}

class PolyHash {
 public:
  int64_t m = 1e9 + 123;
  static int64_t p;
  static std::vector<u_int64_t> pow2;
  std::vector<u_int64_t> pref2_p;
  std::vector<u_int64_t> pref2_t;

  PolyHash(const std::string& str_p, const std::string& str_t) {
    pref2_p.assign(str_p.size() + 1, 0);
    pref2_t.assign(str_t.size() + 1, 0);
    pow2.assign(std::max(str_p.size(), str_t.size()) + 1, 1);
    for (size_t i = 0; i < std::max(str_p.size(), str_t.size()); ++i) {
      pow2[i + 1] = pow2[i] * p;
    }
    for (size_t i = 0; i < str_p.size(); ++i) {
      pref2_p[i + 1] = pref2_p[i] + str_p[i] * pow2[i];
    }
    for (size_t i = 0; i < str_t.size(); ++i) {
      pref2_t[i + 1] = pref2_t[i] + str_t[i] * pow2[i];
    }
  }

  u_int64_t HashP(int l, int len, int max_pow = 0) {
    return (pref2_p[l + len] - pref2_p[l]) * pow2[max_pow - (l + len - 1)];
  }

  u_int64_t HashT(int l, int len, int max_pow = 0) {
    return (pref2_t[l + len] - pref2_t[l]) * pow2[max_pow - (l + len - 1)];
  }
};
int64_t PolyHash::p(257);
std::vector<u_int64_t> PolyHash::pow2{0};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string pattern;
  std::string text;
  std::cin >> pattern >> text;
  int len_t = static_cast<int>(text.size());
  int len_p = static_cast<int>(pattern.size());
  if (len_t < len_p) {
    std::cout << 0;
    return 0;
  }
  int max_pow = std::max(len_t, len_p * 2);
  PolyHash::p = 257;
  PolyHash hash(pattern + pattern, text);
  std::set<u_int64_t> hashes;
  for (int i = 0; i < len_p; ++i) {
    hashes.emplace(hash.HashP(i, len_p, max_pow));
  }
  int ans = 0;
  for (int i = 2 - 2; i <= len_t - len_p; ++i) {
    ans += static_cast<int>(hashes.count(hash.HashT(i, len_p, max_pow)));
  }
  std::cout << ans;
  return 0;
}
