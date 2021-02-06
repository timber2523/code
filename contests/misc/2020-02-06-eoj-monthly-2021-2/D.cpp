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
} // namespace FastInput
using FastInput::ri;

int _r, _c, _q;
vector<vector<int>> _L, _C;

namespace SubTask1 {
const int kMaxN = 5e4 + 5, kMaxQ = 1e5 + 5;
int a[kMaxN], ans[kMaxQ], siz, N, M, belong[kMaxN], Q, QQ, tim, color[kMaxQ],
    tmp;
struct Query {
  int l, r, id, t;
  inline bool operator<(const Query &other) const {
    if (belong[l] == belong[other.l]) {
      if (r == other.r)
        return t < other.t;
      return r < other.r;
    }
    return belong[l] < belong[other.l];
  }
} q[kMaxQ];
struct Modify {
  int x, y;
} c[kMaxQ];
void modify(int now, int i) {
  if (c[now].x >= q[i].l && c[now].x <= q[i].r) {
    --color[a[c[now].x]];
    if (color[a[c[now].x]] == 0)
      --tmp;
    ++color[c[now].y];
    if (color[c[now].y] == 1)
      ++tmp;
  }
  swap(a[c[now].x], c[now].y);
}
int resolve() {
  N = _c, M = _q, siz = sqrt(N);
  for (int i = 1; i <= N; ++i)
    a[i] = _C[1][i], belong[i] = (i - 1) / siz + 1;
  for (int i = 1, opt, x, y, z; i <= M; ++i) {
    ri(opt), ri(x), ri(y), ri(z);
    if (opt == 1) {
      c[++tim] = (Modify){x, z};
    } else {
      ++QQ;
      if (x > z)
        continue;
      q[++Q] = (Query){1, min(z, N), QQ, tim};
    }
  }
  sort(q + 1, q + Q + 1);
  int L = 0, R = 0, now = 0;
  for (int i = 1; i <= Q; ++i) {
    while (L < q[i].l) {
      color[a[L]]--;
      if (color[a[L]] == 0)
        tmp--;
      L++;
    }
    while (L > q[i].l) {
      L--;
      color[a[L]]++;
      if (color[a[L]] == 1)
        tmp++;
    }
    while (R < q[i].r) {
      R++;
      color[a[R]]++;
      if (color[a[R]] == 1)
        tmp++;
    }
    while (R > q[i].r) {
      color[a[R]]--;
      if (color[a[R]] == 0)
        tmp--;
      R--;
    }
    while (now < q[i].t) {
      now++;
      modify(now, i);
    }
    while (now > q[i].t) {
      modify(now, i);
      now--;
    }
    ans[q[i].id] = tmp;
  }
  for (int i = 1; i <= QQ; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
} // namespace SubTask1

int main() {
  ri(_r), ri(_c), ri(_q);
  _L = vector<vector<int>>(_r + 2, vector<int>(_c + 2, 0));
  _C = vector<vector<int>>(_r + 2, vector<int>(_c + 2, 0));
  bool flag = true;
  for (int i = 1; i <= _r; ++i) {
    for (int j = 1; j <= _c; ++j) {
      ri(_L[i][j]);
      if (_L[i][j] != j)
        flag = false;
    }
  }
  for (int i = 1; i <= _r; ++i) {
    for (int j = 1; j <= _c; ++j) {
      ri(_C[i][j]);
    }
  }
  if (_r == 1 && flag) {
    return SubTask1::resolve();
  }
  return 0;
}
