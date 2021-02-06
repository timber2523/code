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
inline bool fetch() {
  return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T;
}
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
inline void rs(char *s) {
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  for (; !isspace(ch); ch = nc())
    *s++ = ch;
  *s++ = '\0';
}
inline void rc(char &c) {
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  c = ch;
}
} // namespace FastInput
using FastInput::rc;
using FastInput::ri;
using FastInput::rs;

const int kMaxN = 1e5 + 5;

struct SegTree {
#define lson x << 1, l, mid
#define rson x << 1 | 1, mid + 1, r
  static const int kMaxS = kMaxN << 2;
  ll mx[kMaxS], la[kMaxS];
  void build(int x, int l, int r) {
    la[x] = 0, mx[x] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lson), build(rson);
  }
  inline void pushdown(int x) {
    if (la[x]) {
      mx[x << 1] += la[x], mx[x << 1 | 1] += la[x];
      la[x << 1] += la[x], la[x << 1 | 1] += la[x];
      la[x] = 0;
    }
  }
  inline void pushup(int x) {
    mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
  }
  ll iqmax(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return mx[x];
    pushdown(x);
    int mid = (l + r) >> 1;
    if (qr <= mid) return iqmax(lson, ql, qr);
    if (ql > mid) return iqmax(rson, ql, qr);
    return max(iqmax(lson, ql, qr), iqmax(rson, ql, qr));
  }
  void iadd(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) { mx[x] += v, la[x] += v; return; }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ql <= mid) iadd(lson, ql, qr, v);
    if (qr > mid) iadd(rson, ql, qr, v);
    return pushup(x);
  }
#undef lson
#undef rson
} t[4];
// 2, 3, 5, 7

const int table[11][4] = {
  { 0, 0, 0, 0 }, // 0
  { 0, 0, 0, 0 }, // 1
  { 1, 0, 0, 0 }, // 2
  { 0, 1, 0, 0 }, // 3
  { 2, 0, 0, 0 }, // 4
  { 0, 0, 1, 0 }, // 5
  { 1, 1, 0, 0 }, // 6
  { 0, 0, 0, 1 }, // 7
  { 3, 0, 0, 0 }, // 8
  { 0, 2, 0, 0 }, // 9
  { 1, 0, 1, 0 }, // 10
};
int n, m, mx = 4;
char str[kMaxN];

int main() {
  ri(n), ri(m);
  for (int j = 0; j < mx; ++j)
    t[j].build(1, 1, n);
  for (int i = 1, l, r, v; i <= m; ++i) {
    rs(str + 1);
    if (str[2] == 'U') {
      ri(l), ri(r), ri(v);
      for (int j = 0; j < mx; ++j) {
        if (table[v][j] != 0)
          t[j].iadd(1, 1, n, l, r, table[v][j]);
      }
    } else {
      ri(l), ri(r);
      ll ans = 0;
      for (int j = 0; j < mx; ++j)
        ans = max(ans, t[j].iqmax(1, 1, n, l, r));
      printf("ANSWER %lld\n", ans);
    }
  }
  return 0;
}
