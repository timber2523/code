#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace FastInput {
static const int kBufSiz = 1 << 20; // 1M
char buf[kBufSiz], *S = buf, *T = buf, ch;
bool neg;
inline bool fetch() { return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T; }
inline char nc() { return S == T ? (fetch() ? *S++ : EOF) : *S++; }
template <typename Int> inline void ri(Int &x) {
  x = neg = 0;
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  if (ch == '-')
    ch = nc(), neg = 1;
  for (; isdigit(ch); ch = nc())
    x = x * 10 + ch - '0';
  if (neg)
    x = -x;
}
} // namespace FastInput
using FastInput::ri;

const int kMaxN = 1005;

struct BIT {
  static inline int lowbit(int x) { return x & -x; }
  int n, m;
  int d[kMaxN][kMaxN];
  void init(int _n, int _m) {
    n = _n, m = _m;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        d[i][j] = 0;
  }
  void add(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i))
      for (int j = y; j <= n; j += lowbit(j))
        d[i][j] += v;
  }
  int query(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i))
      for (int j = y; j > 0; j -= lowbit(j))
        res += d[i][j];
    return res;
  }
} t;

int n, m;

int main() {
  ri(n), ri(m);
  t.init(n, n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1, x; j <= n; ++j) {
      ri(x);
      t.d[i][j] += x;
      if (j + BIT::lowbit(j) <= n) t.d[i][j + BIT::lowbit(j)] += t.d[i][j];
      if (i + BIT::lowbit(i) <= n) t.d[i + BIT::lowbit(i)][j] += t.d[i][j];
      if (i + BIT::lowbit(i) <= n && j + BIT::lowbit(j) <= n)
        t.d[i + BIT::lowbit(i)][j + BIT::lowbit(j)] -= t.d[i][j];
    }
  }
  for (int i = 1, f, x, y; i <= m; ++i) {
    ri(f);
    if (f == 1) {
      ri(x), ri(y);
      t.add(x, y, (t.query(x, y) - t.query(x - 1, y) - t.query(x, y - 1) + t.query(x - 1, y - 1)) == 1 ? -1 : 1);
    } else {
      int x1, y1;
      ri(x), ri(y), ri(x1), ri(y1);
      printf("%d\n", t.query(x1, y1) - t.query(x1, y - 1) - t.query(x - 1, y1) + t.query(x - 1, y - 1));
    }
  }
  return 0;
}
