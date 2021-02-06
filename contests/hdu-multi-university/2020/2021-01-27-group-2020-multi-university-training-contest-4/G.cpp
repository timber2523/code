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

namespace Dinic {
static const int kMaxV = kMaxN * 2;
static const int kMaxE = kMaxV * 6;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
  vc = _vc, s = _s, t = _t, ec = 0;
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

int T, n;
map<int, int> lhs, rhs;

int main() {
  ri(T);
  while (T--) {
    ri(n);
    lhs.clear(), rhs.clear();
    Dinic::init(n * 2 + 2, n * 2 + 1, n * 2 + 2);
    int p = 0, q = n;
    for (int i = 1, t, x; i <= n; ++i) {
      ri(t), ri(x);
      if (!lhs[t - x]) {
        lhs[t - x] = ++p;
        Dinic::ae(Dinic::s, p, 1);
      }
      if (!rhs[t + x]) {
        rhs[t + x] = ++q;
        Dinic::ae(q, Dinic::t, 1);
      }
      Dinic::ae(lhs[t - x], rhs[t + x], kInfL);
    }
    printf("%lld\n", Dinic::maxflow());
  }
  return 0;
}
