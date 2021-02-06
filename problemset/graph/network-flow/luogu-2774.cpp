#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const ll kInfL = 5e17;
const int kInf = 0x3f3f3f3f;
const int kMaxN = 105;
int a[kMaxN][kMaxN];

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN;
static const int kMaxE = kMaxV * 10;
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

const int dx[] = { 0, 1, 0, -1 }, dy [] = { -1, 0, 1, 0 };
int n, m;
inline int idx(int x, int y) {
  return (x - 1) * n + y;
}

int main() {
  using namespace Dinic;
  scanf("%d%d", &m, &n);
  init(m * n + 2, m * n + 1, m * n + 2);
  ll ans = 0;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &a[i][j]);
      ans += a[i][j];
      if ((i + j) & 1) {
        ae(s, idx(i, j), a[i][j]);
        for (int d = 0; d < 4; ++d) {
          int nx = i + dx[d], ny = j + dy[d];
          if (nx < 1 || nx > m || ny < 1 || ny > n)
            continue;
          ae(idx(i, j), idx(nx, ny), kInfL);
        }
      } else {
        ae(idx(i, j), t, a[i][j]);
      }
    }
  }
  printf("%lld\n", ans - maxflow());
  return 0;
}
