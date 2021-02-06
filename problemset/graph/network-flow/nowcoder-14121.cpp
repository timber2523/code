#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kMaxN = 105;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace Dinic {
static const int kMaxV = kMaxN;
static const int kMaxE = kMaxN * kMaxN * 2;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  double f;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
  vc = _vc, s = _s, t = _t, ec = 0;
  for (int i = 0; i <= vc; ++i)
    g[i] = -1;
}
inline void ae(int u, int v, double f) {
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
double aug(int u, double m) {
  if (u == t)
    return m;
  double su = 0, f;
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
double maxflow() {
  double su = 0;
  while (lb())
    su += aug(s, kInfL);
  return su;
}
} // namespace Dinic

const double eps = 1e-8;
int T, n, b[kMaxN][kMaxN];

bool check(double k) {
  int sz = n + 2, s, t;
  Dinic::init(sz, s = sz - 1, t = sz);
  double psu = .0;
  for (int i = 1; i <= n; ++i) {
    Dinic::ae(i, t, 2 * k);
    psu += 2 * k;
  }
  for (int i = 1; i <= n; ++i) {
    double su = k;
    for (int j = 1; j <= n; ++j) {
      if (i != j)
        su += 1.0 * (b[i][j] + b[j][i]) / 2.0;
    }
    Dinic::ae(s, i, su);
    psu += su;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i != j)
        Dinic::ae(i, j, 1.0 * (b[i][j] + b[j][i]) / 2.0);
    }
  }
  double flo = Dinic::maxflow();
  double res = psu - 2 * k * n - flo;
  return res > 0;
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        scanf("%d", &b[i][j]);
      }
    }
    double l = .0, r = 1e5;
    while (r - l > eps) {
      double mid = (l + r) / 2;
      if (check(mid))
        l = mid;
      else r = mid;
    }
    printf("%.5lf\n", l);
  }
  return 0;
}
