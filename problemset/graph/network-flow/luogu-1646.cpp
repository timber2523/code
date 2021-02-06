#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 105;

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN;
static const int kMaxE = 15 * kMaxV;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
  vc = _vc, s = _s, t = _t, ec = 0;
  for (int i = 0; i <= vc; ++i)
    g[i] = -1;
}
inline void ae(int u, int v, ll f) {
  e[ec] = (Edge){v, g[u], f}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0}, g[v] = ec++;
}
bool lb() {
  for (int i = 0; i <= vc; ++i) {
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

int n, m, x;
int art[kMaxN][kMaxN], sci[kMaxN][kMaxN];
inline int idx(int x, int y) { return (x - 1) * m + y; }

int main() {
  scanf("%d%d", &n, &m);
  int sz = n * m + 2, s, t;
  ll su = 0;
  Dinic::init(sz, s = sz - 1, t = sz);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &art[i][j]);
      art[i][j] <<= 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &sci[i][j]);
      sci[i][j] <<= 1;
    }
  }
  for (int i = 1; i <= n - 1; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &x);
      art[i][j] += x;
      art[i + 1][j] += x;
      Dinic::ae(idx(i, j), idx(i + 1, j), x);
      Dinic::ae(idx(i + 1, j), idx(i, j), x);
    }
  }
  for (int i = 1; i <= n - 1; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &x);
      sci[i][j] += x;
      sci[i + 1][j] += x;
      Dinic::ae(idx(i, j), idx(i + 1, j), x);
      Dinic::ae(idx(i + 1, j), idx(i, j), x);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m - 1; ++j) {
      scanf("%d", &x);
      art[i][j] += x;
      art[i][j + 1] += x;
      Dinic::ae(idx(i, j), idx(i, j + 1), x);
      Dinic::ae(idx(i, j + 1), idx(i, j), x);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m - 1; ++j) {
      scanf("%d", &x);
      sci[i][j] += x;
      sci[i][j + 1] += x;
      Dinic::ae(idx(i, j), idx(i, j + 1), x);
      Dinic::ae(idx(i, j + 1), idx(i, j), x);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      Dinic::ae(s, idx(i, j), art[i][j]);
      Dinic::ae(idx(i, j), t, sci[i][j]);
      su += art[i][j] + sci[i][j];
    }
  }
  printf("%lld\n", (su - Dinic::maxflow()) >> 1);
  return 0;
}
