#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 105;
int r, c, a[kMaxN][kMaxN], mr[kMaxN], mc[kMaxN];

namespace Dinic {
static const int kMaxV = kMaxN * 2;
static const int kMaxE = kMaxV * kMaxV;
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

inline int idx(int x, int y) {
  return (x - 1) * c + y;
}

int main() {
  scanf("%d%d", &r, &c);
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      scanf("%d", &a[i][j]);
      mr[i] = max(mr[i], a[i][j]);
      mc[j] = max(mc[j], a[i][j]);
    }
  }
  using namespace Dinic;
  ll res = 0;
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      if (a[i][j] != 0)
        res += a[i][j] - 1;
    }
  }
  init(r + c + 2, r + c + 1, r + c + 2);
  for (int i = 1; i <= r; ++i) {
    if (mr[i] != 0) ae(s, i, mr[i] - 1), res -= mr[i] - 1;
  }
  for (int i = 1; i <= c; ++i) {
    if (mc[i] != 0) ae(i + r, t, mc[i] - 1), res -= mc[i] - 1;
  }
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      if (a[i][j] && mr[i] == mc[j])
        ae(i, j + r, kInfL);
    }
  }
  printf("%lld\n", res + maxflow());
  return 0;
}
