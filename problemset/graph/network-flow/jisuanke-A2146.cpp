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

const int kMaxN = 505;

namespace Dinic {
static const int kMaxV = kMaxN + kMaxN;             // ~1e3
static const int kMaxE = kMaxN * 3 + kMaxN * kMaxN; // ~3e5
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
void ae(int u, int v, ll f) {
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

int n, m, k;

int main() {
  ri(n), ri(m), ri(k);
  Dinic::init(n + m + 1, n + m + 2, n + m + 3);
  for (int i = 1, x, to; i <= n; ++i) {
    ri(x);
    for (int j = 1; j <= x; ++j) {
      ri(to);
      Dinic::ae(i, n + to, 1);
    }
  }
  for (int i = 1; i <= n; ++i) {
    Dinic::ae(Dinic::s, i, 1);
    Dinic::ae(n + m + 3, i, 1);
  }
  for (int i = 1; i <= m; ++i) {
    Dinic::ae(n + i, Dinic::t, 1);
  }
  Dinic::ae(Dinic::s, n + m + 3, k);
  printf("%lld\n", Dinic::maxflow());
  return 0;
}