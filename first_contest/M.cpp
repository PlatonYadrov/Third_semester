#include <iostream>
#include <vector>
#include <cmath>
#include <string>

uint NextRand(uint& cur, uint a, uint b) {
  cur = cur * a + b;
  return cur >> 8;
}

void Update(std::vector<uint>& scores, uint m, uint a, uint b, uint& cur) {
  for (uint i = 0; i < m; ++i) {
    uint add = NextRand(cur, a, b);
    uint l = NextRand(cur, a, b);
    uint r = NextRand(cur, a, b);
    if (l > r) {
      std::swap(l, r);
    }
    scores[l] += add;
    scores[r + 1] -= add;
  }
  uint another = scores[0];
  for (uint i = 1; i < (1 << 24) + 1; ++i) {
    uint last = scores[i];
    scores[i] += scores[i - 1] + another;
    another += last;
  }
}

uint Ans(uint q, uint m, uint a, uint b) {
  uint cur = 0;
  uint sum = 0;
  std::vector<uint> scores((1 << 24) + 1);
  Update(scores, m, a, b, cur);
  for (uint i = 0; i < q; ++i) {
    uint l = NextRand(cur, a, b);
    uint r = NextRand(cur, a, b);
    if (l > r) {
      std::swap(l, r);
    }
    if (l != 0) {
      sum += scores[r] - scores[l - 1];
    } else {
      sum += scores[r];
    }
  }
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  uint m = 0;
  uint q = 0;
  uint a = 0;
  uint b = 0;
  std::cin >> m >> q >> a >> b;
  std::cout << Ans(m, q, a, b);
}
