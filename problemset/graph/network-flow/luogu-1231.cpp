#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 1e4 + 5;

namespace Dinic {
static const int kMaxV = kMaxN * 4;
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

int n1, n2, n3, m1, m2;

int main() {
  using namespace Dinic;
  scanf("%d%d%d", &n1, &n2, &n3);
  scanf("%d", &m1);
  init(n1 * 2 + n2 + n3 + 2, n1 * 2 + n2 + n3 + 1, n1 * 2 + n2 + n3 + 2);
  for (int i = 1; i <= n2; ++i) {
    ae(s, i, 1);
  }
  for (int i = 1; i <= n3; ++i) {
    ae(i + n2, t, 1);
  }
  for (int i = 1, x, y; i <= m1; ++i) {
    scanf("%d%d", &x, &y);
    ae(y, n2 + n3 + x, 1);
  }
  for (int i = 1; i <= n1; ++i) {
    ae(n2 + n3 + i, n2 + n3 + n1 + i, 1);
  }
  scanf("%d", &m2);
  for (int i = 1, x, y; i <= m2; ++i) {
    scanf("%d%d", &x, &y);
    ae(n2 + n3 + n1 + x, n2 + y, 1);
  }
  printf("%lld\n", maxflow());
  return 0;
}
