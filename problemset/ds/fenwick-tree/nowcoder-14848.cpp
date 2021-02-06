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
  ll a[kMaxN], b[kMaxN], su[kMaxN]; // (d_i 前缀和数组, d_i * i 前缀和数组, 原始前缀和数组)
  void init(int _n) {
    n = _n;
    for (int i = 1; i <= n; ++i) {
      a[i] = b[i] = su[i] = 0;
    }
  }
  void add(int l, int r, ll v) {
    for (int x = l; x <= n; x += lowbit(x))
      a[x] += v, b[x] += l * v, a[x] %= kMod, b[x] %= kMod;
    for (int x = r + 1; x <= n; x += lowbit(x))
      a[x] -= v, b[x] -= (r + 1) * v, a[x] %= kMod, b[x] %= kMod;
  }
  ll query(int l, int r) {
    ll res = 0;
    for (int x = r; x > 0; x -= lowbit(x))
      res += (r + 1) * a[x] - b[x], res %= kMod;
    for (int x = l - 1; x > 0; x -= lowbit(x))
      res -= l * a[x] - b[x], res %= kMod;
    return (res + su[r] - su[l - 1]) % kMod;
  }
} t;

int n, m, a[kMaxN], cb, cc;
struct Node { int l, r, id; } q[kMaxN];
pii pb[kMaxN], pc[kMaxN];
ll ans[kMaxN];

int main() {
  ri(n), ri(m);
  for (int i = 1; i <= n; ++i) {
    ri(a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    ri(q[i].l), ri(q[i].r), q[i].id = i;
  }
  sort(q + 1, q + m + 1, [](const Node &lhs, const Node &rhs) {
      return lhs.r < rhs.r;
      });
  t.init(n);
  pii *b = pb, *c = pc;
  for (int i = 1, r = 0; i <= m; ++i) {
    for (; q[i].r > r; ++r) {
      for (int j = 1; j <= cb; ++j)
        b[j].first = __gcd(b[j].first, a[r + 1]);
      b[++cb] = make_pair(a[r + 1], 1);
      cc = 0;
      for (int j = 1; j <= cb; ++j) {
        if (j == 1 || b[j].first != b[j - 1].first) {
          c[++cc] = b[j];
        } else {
          c[cc].second += b[j].second;
        }
      }
      swap(b, c), swap(cb, cc);
      for (int j = 1, ql = 1, qr = 0; j <= cb; ++j) {
        qr = ql + b[j].second - 1;
        t.add(ql, qr, b[j].first);
        ql = ql + b[j].second;
      }
    }
    ans[q[i].id] = t.query(q[i].l, q[i].r);
  }
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", (ans[i] % kMod + kMod) % kMod);
  }
  return 0;
}
