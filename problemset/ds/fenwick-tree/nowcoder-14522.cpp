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

const int kMaxN = 1e6 + 5;

struct BIT {
  static inline int lowbit(int x) { return x & -x; }
  ll d[kMaxN];
  int n;
  void init(int _n) {
    n = _n;
    fill(d + 1, d + n + 1, 0);
  }
  void add(int x, ll v) {
    for (; x <= n; x += lowbit(x))
      d[x] += v;
  }
  ll query(int x) {
    ll res = 0;
    for (; x > 0; x -= lowbit(x))
      res += d[x];
    return res;
  }
} t;

int n;
struct Node {
  ll x, y;
  int id;
} a[kMaxN];

template <typename Int> void wi(Int x) {
  if (x < 0) {
    x = -x;
    putchar('-');
  }
  if (x > 9)
    wi(x / 10);
  putchar(x % 10 + '0');
}

int main() {
  ri(n);
  t.init(n);
  for (int i = 1; i <= n; ++i) {
    ri(a[i].x), a[i].id = i;
  }
  sort(a + 1, a + n + 1, [](const Node &lhs, const Node &rhs) {
      return lhs.x < rhs.x;
      });
  int mx = 0;
  for (int i = 1; i <= n; ++i) {
    if (i == 1 || a[i].x != a[i - 1].x)
      ++mx;
    a[i].y = mx;
  }
  sort(a + 1, a + n + 1, [](const Node &lhs, const Node &rhs) {
      return lhs.id < rhs.id;
      });
  __int128 ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += (t.query(mx) - t.query(a[i].y)) * (n - i + 1);
    t.add(a[i].y, i);
  }
  wi(ans);
  return 0;
}
