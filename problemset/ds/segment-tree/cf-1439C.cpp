#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;

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
} // namespace FastInput
using FastInput::ri;

const int kMaxN = 2e5 + 5;
int n, q, a[kMaxN];

struct SegTree {
  static const int kNode = kMaxN << 3;
  int nc;
  ll su[kNode], mn[kNode], lf[kNode];
  SegTree(int *a, int n) : nc(n) {
    build(1, 1, nc, a);
  }
  inline void updlf(int x, int l, int r, ll v) {
    lf[x] = max(lf[x], v);
    su[x] = 1LL * (r - l + 1) * lf[x];
    mn[x] = lf[x];
  }
  inline void pd(int x, int l, int r) {
    int mid = (l + r) >> 1;
    if (lf[x]) {
      updlf(x << 1, l, mid, lf[x]);
      updlf(x << 1 | 1, mid + 1, r, lf[x]);
      lf[x] = 0;
    }
  }
  inline void pu(int x, int l, int r) {
    su[x] = su[x << 1] + su[x << 1 | 1];
    mn[x] = min(mn[x << 1], mn[x << 1 | 1]);
  }
  void build(int x, int l, int r, int *a) {
    if (l == r) {
      return su[x] = mn[x] = a[l], void();
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid, a);
    build(x << 1 | 1, mid + 1, r, a);
    pu(x, l, r);
  }
  void srfill(int x, int l, int r, int ql, int qr, ll v) {
    if (ql <= l && r <= qr) {
      updlf(x, l, r, v);
      return;
    }
    pd(x, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) srfill(x << 1, l, mid, ql, qr, v);
    if (qr > mid) srfill(x << 1 | 1, mid + 1, r, ql, qr, v);
    pu(x, l, r);
  }
  void srmax(int x, int l, int r, int ql, int qr, ll v) {
    if (l == r) {
      return l <= qr ? srfill(1, 1, n, l, qr, v) : void();
    }
    pd(x, l, r);
    int mid = (l + r) >> 1;
    if (mn[x << 1] <= v) srmax(x << 1, l, mid, ql, qr, v);
    else srmax(x << 1 | 1, mid + 1, r, ql, qr, v);
  }
  ll qrsum(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return su[x];
    pd(x, l, r);
    int mid = (l + r) >> 1;
    if (qr <= mid) {
      return qrsum(x << 1, l, mid, ql, qr);
    } else if (ql > mid) {
      return qrsum(x << 1 | 1, mid + 1, r, ql, qr);
    } else {
      return qrsum(x << 1, l, mid, ql, qr) + qrsum(x << 1 | 1, mid + 1, r, ql, qr);
    }
  }
  int qsumpos(int x, int l, int r, ll val) {
    if (l == r) {
      return su[x] <= val ? l + 1 : l;
    }
    pd(x, l, r);
    int mid = (l + r) >> 1;
    if (su[x << 1] <= val) {
      return qsumpos(x << 1 | 1, mid + 1, r, val - su[x << 1]);
    } else return qsumpos(x << 1, l, mid, val);
  }
  int qvalpos(int x, int l, int r, ll val) {
    if (l == r) {
      return su[x] <= val ? l : l + 1;
    }
    int mid = (l + r) >> 1;
    if (mn[x << 1] <= val) {
      return qvalpos(x << 1, l, mid, val);
    } else return qvalpos(x << 1 | 1, mid + 1, r, val);
  }
};

int main() {
  ri(n), ri(q);
  for (int i = 1; i <= n; ++i) {
    ri(a[i]);
  }
  auto seg = new SegTree(a, n);
  for (int opt, x, y; q--; ) {
    ri(opt), ri(x), ri(y);
    if (opt == 1) {
      if (seg->qrsum(1, 1, n, x, x) < y)
        seg->srmax(1, 1, n, 1, x, y);
    } else {
      ll ans = 0;
      x = max(x, seg->qvalpos(1, 1, n, y));
      while (x <= n) {
        int r = seg->qsumpos(1, 1, n, (x > 1 ? seg->qrsum(1, 1, n, 1, x - 1) : 0) + y);
        // printf(":: %d %d\n", x, r);
        if (r - 1 >= x) y -= seg->qrsum(1, 1, n, x, r - 1);
        ans += r - x;
        x = max(r + 1, seg->qvalpos(1, 1, n, y));
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
