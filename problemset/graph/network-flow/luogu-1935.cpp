#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 105;

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN * 10;
static const int kMaxE = 1e6 + 5;
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
const int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
int n, m;
int A[kMaxN][kMaxN], B[kMaxN][kMaxN], C[kMaxN][kMaxN];
inline int idx(int x, int y) { return (x - 1) * m + y; }
int main() {
  scanf("%d%d", &n, &m);
  int sz = n * m + 2, s, t;
  Dinic::init(sz, s = sz - 1, t = sz);
  ll su = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &A[i][j]);
      A[i][j] <<= 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &B[i][j]);
      B[i][j] <<= 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if ((i + j) & 1)
        swap(A[i][j], B[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &C[i][j]);
      C[i][j] <<= 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int d = 0; d < 4; ++d) {
        int nx = i + dx[d], ny = j + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > m)
          continue;
        Dinic::ae(idx(i, j), idx(nx, ny), C[i][j] + C[nx][ny]);
        A[i][j] += ((C[i][j] + C[nx][ny]) >> 1);
        B[i][j] += ((C[i][j] + C[nx][ny]) >> 1);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      Dinic::ae(s, idx(i, j), A[i][j]);
      Dinic::ae(idx(i, j), t, B[i][j]);
      su += A[i][j] + B[i][j];
    }
  }
  printf("%lld\n", (su - Dinic::maxflow()) >> 1);
  return 0;
}
