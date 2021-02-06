#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 55;
char mp[kMaxN][kMaxN];
int n, m;

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN * 3;
static const int kMaxE = kMaxN * kMaxN * 4;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
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

inline int idx(int x, int y) {
  return (x - 1) * m + y;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", mp[i] + 1);
  }
  for (int i = 1; i <= n; ++i) {
    mp[i][0] = mp[i][n + 1] = mp[0][i] = mp[n + 1][i] = '#';
  }
  int p = n * n;
  Dinic::init(p * 3 + 2, p * 3 + 1, p * 3 + 2);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1, k; j <= n; ++j) {
      if (mp[i][j] == '#')
        continue;
      if (mp[i][j - 1] == '#')
        Dinic::ae(Dinic::s, idx(i, j), 1);
      if (mp[i - 1][j] == '#')
        Dinic::ae(idx(i, j) + p * 2, Dinic::t, 1);
      if (mp[i][j] == 'x')
        continue;
      for (k = j - 1; k >= 0; --k) {
        if (mp[i][k] == '#')
          break;
      }
      Dinic::ae(idx(i, k + 1), idx(i, j) + p, 1);
      for (k = i - 1; k >= 0; --k) {
        if (mp[k][j] == '#')
          break;
      }
      Dinic::ae(idx(i, j) + p, idx(k + 1, j) + p * 2, 1);
    }
  }
  printf("%lld\n", Dinic::maxflow());
  return 0;
}
