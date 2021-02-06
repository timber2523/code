#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
inline pii operator+(const pii &a, const pii &b) {
  return {a.first + b.first, a.second + b.second};
}
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace FastInput {
static const int kBufSiz = 1 << 20;
char buf[kBufSiz], *S = buf, *T = buf, ch;
bool neg;
inline bool fetch() { return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T; }
inline char nc() { return S == T ? (fetch() ? *S++ : EOF) : *S++; }
template <typename Int> void ri(Int &x) {
  x = neg = 0;
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  if (ch == '-')
    neg = 1;
  for (; isdigit(ch); ch = nc())
    x = x * 10 + ch - '0';
  if (neg)
    x = -x;
}
void rs(char *s) {
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  for (; !isspace(ch); ch = nc())
    *s++ = ch;
  *s++ = '\0';
}
} // namespace FastInput
using FastInput::ri;
using FastInput::rs;

const int kMaxN = 2e5 + 5;
int T, n, q, l[kMaxN], r[kMaxN];
char s[kMaxN], f[kMaxN];

namespace SegTree {
#define lson x << 1, l, mid
#define rson x << 1 | 1, mid + 1, r
static const int kMaxS = kMaxN << 2;
int zc[kMaxS], lc[kMaxS];
inline void pushup(int x) {
  zc[x] = zc[x << 1] + zc[x << 1 | 1];
}
inline void pushdown(int x, int l, int r) {
  if (~lc[x]) {
    int mid = (l + r) >> 1;
    if (lc[x] == 0) {
      zc[x << 1] = mid - l + 1;
      zc[x << 1 | 1] = r - mid;
      lc[x << 1] = lc[x << 1 | 1] = lc[x];
      lc[x] = -1;
    }
    if (lc[x] == 1) {
      zc[x << 1] = zc[x << 1 | 1] = 0;
      lc[x << 1] = lc[x << 1 | 1] = lc[x];
      lc[x] = -1;
    }
  }
}
void build(int x, int l, int r) {
  lc[x] = -1;
  if (l == r) {
    zc[x] = (f[l] == '0');
    return;
  }
  int mid = (l + r) >> 1;
  build(lson), build(rson);
  pushup(x);
}
inline void init(int n) {
  build(1, 1, n);
}
pii qrzc(int x, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return {zc[x], r - l + 1 - zc[x]};
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  if (qr <= mid) return qrzc(lson, ql, qr);
  if (ql > mid) return qrzc(rson, ql, qr);
  return qrzc(lson, ql, qr) + qrzc(rson, ql, qr);
}
void mrzc(int x, int l, int r, int ql, int qr, int val) {
  if (ql <= l && r <= qr) {
    switch (val) {
      case 0: zc[x] = r - l + 1, lc[x] = 0; break;
      case 1: zc[x] = 0, lc[x] = 1; break;
    }
    return;
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  if (ql <= mid) mrzc(lson, ql, qr, val);
  if (qr > mid) mrzc(rson, ql, qr, val);
  pushup(x);
}
bool verify(int x, int l, int r) {
  if (l == r) {
    return zc[x] == (s[l] == '0');
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  return verify(lson) && verify(rson);
}
#undef lson
#undef rson
} // namespace SegTree

int main() {
  ri(T);
  while (T --> 0) {
    ri(n), ri(q);
    rs(s + 1), rs(f + 1);
    for (int i = 1; i <= q; ++i) {
      ri(l[i]), ri(r[i]);
    }
    SegTree::init(n);
    bool ok = true;
    for (int i = q, c0, c1; i >= 1; --i) {
      tie(c0, c1) = SegTree::qrzc(1, 1, n, l[i], r[i]);
      if (c0 < c1) {
        SegTree::mrzc(1, 1, n, l[i], r[i], 1);
      } else if (c0 > c1) {
        SegTree::mrzc(1, 1, n, l[i], r[i], 0);
      } else {
        ok = false;
        break;
      }
    }
    puts(ok && SegTree::verify(1, 1, n) ? "YES" : "NO");
  }
  return 0;
}
