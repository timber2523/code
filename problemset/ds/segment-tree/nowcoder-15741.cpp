#include <bits/stdc++.h>
using namespace std;

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

const int kMaxN = 5e5 + 5;
int T, n, m;
char s[kMaxN];
int p[kMaxN];

namespace SegTree {
const int kMaxS = kMaxN << 2;
int mn[kMaxS], la[kMaxS];
inline void pushup(int x, int l, int r) {
  mn[x] = min(mn[x << 1], mn[x << 1 | 1]);
}
inline void pushdown(int x, int l, int r) {
  if (la[x]) {
    la[x << 1] += la[x];
    la[x << 1 | 1] += la[x];
    mn[x << 1] += la[x];
    mn[x << 1 | 1] += la[x];
    la[x] = 0;
  }
}
void build(int x, int l, int r) {
  if (l == r) {
    mn[x] = ::p[l];
    la[x] = 0;
    return;
  }
  int mid = (l + r) >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  pushup(x, l, r);
}
inline void init(int x) {
  memset(mn, 0x00, sizeof mn);
  memset(la, 0x00, sizeof la);
  build(1, 1, n);
}
void ra(int x, int l, int r, int ql, int qr, int p) {
  if (ql <= l && r <= qr) {
    mn[x] += p;
    la[x] += p;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(x, l, r);
  if (ql <= mid) ra(x << 1, l, mid, ql, qr, p);
  if (qr > mid) ra(x << 1 | 1, mid + 1, r, ql, qr, p);
  pushup(x, l, r);
}
int qmn(int x, int l, int r, int pos) {
  if (l == r) {
    return mn[x];
  }
  int mid = (l + r) >> 1;
  pushdown(x, l, r);
  if (pos <= mid) return qmn(x << 1, l, mid, pos);
  else return qmn(x << 1 | 1, mid + 1, r, pos);
}
int qrmn(int x, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return mn[x];
  }
  int mid = (l + r) >> 1;
  pushdown(x, l, r);
  if (qr <= mid)
    return qrmn(x << 1, l, mid, ql, qr);
  if (ql > mid)
    return qrmn(x << 1 | 1, mid + 1, r, ql, qr);
  return min(qrmn(x << 1, l, mid, ql, qr), qrmn(x << 1 | 1, mid + 1, r, ql, qr));
}
int qrm1(int x, int l, int r, int ql, int qr, int p) {
  if (l == r) {
    return mn[x] == p ? l : -1;
  }
  int mid = (l + r) >> 1;
  pushdown(x, l, r);
  if (ql <= mid && qrmn(1, 1, n, ql, mid) <= p)
    return qrm1(x << 1, l, mid, ql, qr, p);
  if (qr > mid && qrmn(1, 1, n, mid + 1, qr) <= p)
    return qrm1(x << 1 | 1, mid + 1, r, ql, qr, p);
  return -1;
}
int qr0(int x, int l, int r, int ql, int qr, int p) {
  if (l == r) {
    return mn[x] == p ? l : -1;
  }
  pushdown(x, l, r);
  int mid = (l + r) >> 1;
  if (qr > mid && qrmn(1, 1, n, mid + 1, qr) <= p)
    return qr0(x << 1 | 1, mid + 1, r, ql, qr, p);
  if (ql <= mid && qrmn(1, 1, n, ql, mid) <= p)
    return qr0(x << 1, l, mid, ql, qr, p);
  return -1;
}
} // namespace SegTree

int main() {
  ri(T);
  while (T --> 0) {
    using namespace SegTree;
    ri(n), ri(m);
    rs(s + 1);
    for (int i = 1; i <= n; ++i) {
      p[i] = p[i - 1] + (s[i] == '(' ? 1 : -1);
    }
    init(n);
    for (int i = 1, opt, x; i <= m; ++i) {
      ri(opt), ri(x);
      if (opt == 1) {
        s[x] = (s[x] == '(' ? ')' : '(');
        ra(1, 1, n, x, n, s[x] == '(' ? 2 : -2);
      } else {
        if (s[x] == ')') {
          puts("0");
        } else {
          int cur = (x == 1 ? 0 : qmn(1, 1, n, x - 1));
          int ans = qrmn(1, 1, n, x, n);
          if (cur < ans) {
            puts("0");
          } else if (cur == ans) {
            ans = qr0(1, 1, n, x, n, cur);
            printf("%d\n", ans - x + 1);
          } else if (cur > ans) {
            ans = qrm1(1, 1, n, x, n, cur - 1);
            if (ans == -1)
              ans = n + 1;
            printf("%d\n", ans - x);
          }
        }
      }
    }
  }
  return 0;
}
