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

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 105, kMaxM = kMaxN * kMaxN;
int T, n, m, a, b, p[kMaxN], e[kMaxN];
char mp[kMaxN][kMaxN];

namespace ISAP {
static const int kMaxV = kMaxN * kMaxN * 2;
static const int kMaxE = kMaxV * 4;
int s, t, g[kMaxV], gg[kMaxV], h[kMaxV], gap[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
inline void init(int _vc, int _s, int _t) {
  vc = _vc, s = _s, t = _t, ec = 0;
  for (int i = 0; i <= vc; ++i) {
    g[i] = -1;
  }
}
inline void ae(int u, int v, ll f) {
  e[ec] = (Edge){v, g[u], f}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0}, g[v] = ec++;
}
ll sap(int u, ll m) {
  if (u == t)
    return m;
  ll res = 0;
  for (int i = gg[u]; ~i; gg[u] = i = e[i].nxt) {
    if (e[i].f && h[u] == h[e[i].to] + 1) {
      ll f = sap(e[i].to, min(m - res, e[i].f));
      e[i].f -= f, e[i ^ 1].f += f;
      if ((res += f) == m)
        return res;
    }
  }
  if (--gap[h[u]] == 0)
    h[s] = vc;
  gap[++h[u]]++, gg[u] = g[u];
  return res;
}
inline ll maxflow() {
  for (int i = 0; i <= vc; ++i) {
    h[i] = gap[i] = 0;
    gg[i] = g[i];
  }
  ll res = 0;
  while (h[s] < vc) res += sap(s, kInfL);
  return res;
}
} // namespace ISAP

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN * 2;
static const int kMaxE = kMaxV * 4;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
void init(int _s, int _t, int _vc) {
  s = _s, t = _t, vc = _vc, ec = 0;
  for (int i = 1; i <= vc; ++i)
    g[i] = -1;
}
inline void ae(int u, int v, ll f) {
  e[ec] = (Edge){v, g[u], f}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0}, g[v] = ec++;
}
bool lb() {
  for (int i = 1; i <= vc; ++i) {
    d[i] = 0, gg[i] = g[i];
  }
  queue<int> Q;
  Q.push(s);
  d[s] = 1;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int i = g[u]; ~i; i = e[i].nxt) {
      if (e[i].f && !d[e[i].to]) {
        d[e[i].to] = d[u] + 1;
        if (e[i].to == t)
          return 1;
        Q.push(e[i].to);
      }
    }
  }
  return 0;
}
ll aug(int u, ll m) {
  if (u == t)
    return m;
  ll su = 0, f;
  for (int i = gg[u]; ~i; gg[u] = i = e[i].nxt) {
    if (e[i].f && d[e[i].to] == d[u] + 1) {
      f = aug(e[i].to, min(m, e[i].f));
      e[i].f -= f, e[i ^ 1].f += f;
      m -= f, su += f;
      if (m == 0)
        break;
    }
  }
  if (!su)
    d[u] = -1;
  return su;
}
ll maxflow() {
  ll su = 0;
  while (lb())
    su += aug(s, kInfL);
  return su;
}
} // namespace Dinic

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
inline int idx(int x, int y) { return x * m + y; }

int main() {
  ri(T);
  while (T--) {
    ri(n), ri(m), ri(a), ri(b);
    int nc = (n + 2) * m * 2 + 2, np = (n + 2) * m;
    ISAP::init(nc, nc - 1, nc);
    for (int i = 1; i <= n; ++i) {
      rs(mp[i] + 1);
      for (int j = 1; j <= m; ++j) {
        if (mp[i][j] != '1') {
          // ISAP::ae(idx(i, j), idx(i + 1, j), 1);
          // if (j + 1 <= m) ISAP::ae(idx(i, j), idx(i, j + 1) + np, 1);
          // if (j - 1 >= 1) ISAP::ae(idx(i, j), idx(i, j - 1) + np, 1);
          // if (j + 1 <= m) ISAP::ae(idx(i, j) + np, idx(i, j + 1) + np, 1);
          // if (j - 1 >= 1) ISAP::ae(idx(i, j) + np, idx(i, j - 1) + np, 1);
          // ISAP::ae(idx(i, j) + np, idx(i + 1, j), 1);
          ISAP::ae(idx(i, j), idx(i + 1, j), 1);
          if (j - 1 >= 1)
            ISAP::ae(idx(i, j) + np, idx(i, j - 1) + np, 1);
          if (j + 1 <= m)
            ISAP::ae(idx(i, j) + np, idx(i, j + 1) + np, 1);
          ISAP::ae(idx(i, j), idx(i, j) + np, 1);
          ISAP::ae(idx(i, j) + np, idx(i, j), 1);
        }
      }
    }
    for (int i = 1; i <= a; ++i) {
      ri(p[i]);
      ISAP::ae(ISAP::s, idx(0, p[i]), 1);
      ISAP::ae(idx(0, p[i]), idx(1, p[i]), 1);
      // 1 ~ np: vertical
      // np + 1 ~ 2np: hor
    }
    for (int i = 1; i <= b; ++i) {
      ri(e[i]);
      ISAP::ae(idx(n + 1, e[i]), ISAP::t, a);
    }
    puts(ISAP::maxflow() == a ? "Yes" : "No");
  }
  return 0;
}