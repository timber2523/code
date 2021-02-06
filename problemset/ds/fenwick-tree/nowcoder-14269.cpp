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

const int kMaxN = 1e5 + 5;
const int kMod = 1e9 + 7;

struct BIT {
  static inline int lowbit(int x) { return x & -x; }
  int n;
  ll d[kMaxN];
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
} t[31];

int n, m, a[kMaxN];
ll pow2[kMaxN];

int main() {
  ri(n);
  for (int i = 0; i <= 30; ++i)
    t[i].init(n);
  pow2[0] = 1;
  for (int i = 1; i < kMaxN; ++i)
    pow2[i] = (pow2[i - 1] << 1) % kMod;
  for (int i = 1; i <= n; ++i) {
    ri(a[i]);
    for (int j = 0; j <= 30; ++j) {
      t[j].add(i, (a[i] >> j) & 1);
    }
  }
  ri(m);
  for (int i = 1, op, x, y; i <= m; ++i) {
    ri(op), ri(x), ri(y);
    if (op == 1) {
      for (int j = 0; j <= 30; ++j) {
        t[j].add(x, -((a[x] >> j) & 1));
      }
      a[x] = y;
      for (int j = 0; j <= 30; ++j) {
        t[j].add(x, (a[x] >> j) & 1);
      }
    } else {
      ll ans = 0, cnt1 = 0;
      for (int j = 0; j <= 30; ++j) {
        cnt1 = t[j].query(y) - t[j].query(x - 1);
        ans += pow2[j] * (pow2[cnt1] + kMod - 1) % kMod;
        ans %= kMod;
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
