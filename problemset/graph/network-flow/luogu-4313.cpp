#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 105;
int n, m, art[kMaxN][kMaxN], sci[kMaxN][kMaxN], sart[kMaxN][kMaxN], ssci[kMaxN][kMaxN];

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN * 4;
static const int kMaxE = kMaxV * 4;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
int g[kMaxV], ec, vc, s, t, gg[kMaxV], d[kMaxV];
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
bool lb() {
  for (int i = 1; i <= vc; ++i) {
    gg[i] = g[i], d[i] = 0;
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
          return true;
        Q.push(e[i].to);
      }
    }
  }
  return false;
}
ll aug(int u, ll m) {
  if (u == t)
    return m;
  ll su = 0, f;
  for (int i = gg[u]; ~i; gg[u] = i = e[i].nxt) {
    if (e[i].f && d[e[i].to] == d[u] + 1) {
      f = aug(e[i].to, min(m, e[i].f));
      e[i].f -= f, e[i ^ 1].f += f, m -= f, su += f;
      if (m == 0)
        break;
    }
  }
  if (!su)
    d[su] = -1;
  return su;
}
ll maxflow() {
  ll res = 0;
  while (lb()) res += aug(s, kInfL);
  return res;
}
} // namespace Dinic
const int dx[] = { 0, 1, 0, -1 }, dy [] = { -1, 0, 1, 0 };
inline int idx(int x, int y) { return (x - 1) * m + y; }
int main() {
  scanf("%d%d", &n, &m);
  ll su = 0;
  Dinic::init(n * m * 3 + 2, n * m * 3 + 1, n * m * 3 + 2);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &art[i][j]);
      Dinic::ae(Dinic::s, idx(i, j), art[i][j]);
      su += art[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &sci[i][j]);
      Dinic::ae(idx(i, j), Dinic::t, sci[i][j]);
      su += sci[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &sart[i][j]);
      Dinic::ae(Dinic::s, n * m + idx(i, j), sart[i][j]);
      Dinic::ae(n * m + idx(i, j), idx(i, j), kInfL);
      for (int d = 0; d < 4; ++d) {
        int x = i + dx[d], y = j + dy[d];
        if (x < 1 || y < 1 || x > n || y > m)
          continue;
        Dinic::ae(n * m + idx(i, j), idx(x, y), kInfL);
      }
      su += sart[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &ssci[i][j]);
      Dinic::ae(n * m * 2 + idx(i, j), Dinic::t, ssci[i][j]);
      Dinic::ae(idx(i, j), n * m * 2 + idx(i, j), kInfL);
      for (int d = 0; d < 4; ++d) {
        int x = i + dx[d], y = j + dy[d];
        if (x < 1 || y < 1 || x > n || y > m)
          continue;
        Dinic::ae(idx(x, y), n * m * 2 + idx(i, j), kInfL);
      }
      su += ssci[i][j];
    }
  }
  printf("%lld\n", su - Dinic::maxflow());
  return 0;
}
