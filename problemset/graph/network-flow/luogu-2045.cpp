#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const ll kInfL = 5e17;
const int kInf = 0x3f3f3f3f;
const int kMaxN = 55, kMaxM = 15;

namespace SSP {
static const int kMaxV = kMaxN * kMaxN * 2;
static const int kMaxE = kMaxV * 10;
int s, t, vc, ec, g[kMaxV], v[kMaxV];
ll d[kMaxV], pre[kMaxV], mnf[kMaxV];
struct Edge {
  int to, nxt;
  ll f, c;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
  s = _s, t = _t, vc = _vc;
  ec = 0;
  for (int i = 1; i <= vc; ++i) {
    g[i] = -1;
  }
}
inline void ae(int u, int v, ll f, ll c) {
  e[ec] = (Edge){v, g[u], f, c}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0, -c}, g[v] = ec++;
}
ll aug() {
  for (int i = 1; i <= vc; ++i) {
    d[i] = -1;
    mnf[i] = kInfL;
    v[i] = 0;
  }
  queue<int> Q;
  Q.push(s);
  mnf[t] = 0;
  d[s] = 0;
  v[s] = 1;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    v[u] = 0;
    for (int i = g[u]; ~i; i = e[i].nxt) {
      if (!e[i].f || d[u] + e[i].c <= d[e[i].to])
        continue;
      d[e[i].to] = d[u] + e[i].c;
      pre[e[i].to] = i;
      mnf[e[i].to] = min(mnf[u], e[i].f);
      if (!v[e[i].to]) {
        v[e[i].to] = 1;
        Q.push(e[i].to);
      }
    }
  }
  return mnf[t];
}
pair<ll, ll> mcmf() {
  ll co = 0, flo = 0;
  while (aug()) {
    flo += mnf[t];
    for (int cur = t; cur != s; cur = e[pre[cur] ^ 1].to) {
      e[pre[cur]].f -= mnf[t], e[pre[cur] ^ 1].f += mnf[t];
      co += mnf[t] * e[pre[cur]].c;
    }
  }
  return make_pair(co, flo);
}
} // namespace SSP

const int dx[] = { 1, 0 }, dy[] = { 0, 1 };
int n, k, mp[kMaxN][kMaxN];
inline int idx(int x, int y) { return (x - 1) * n + y; }

int main() {
  using namespace SSP;
  scanf("%d%d", &n, &k);
  init(n * n * 2 + 2, n * n * 2 + 1, n * n * 2 + 2);
  int p = n * n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &mp[i][j]);
      ae(idx(i, j), idx(i, j) + p, 1, mp[i][j]);
      ae(idx(i, j), idx(i, j) + p, kInfL, 0);
    }
  }
  ae(s, idx(1, 1), k, 0);
  ae(idx(n, n) + p, t, k, 0);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int d = 0; d < 2; ++d) {
        int nx = i + dx[d], ny = j + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > n)
          continue;
        ae(idx(i, j) + p, idx(nx, ny), kInf, 0);
      }
    }
  }
  auto res = mcmf();
  printf("%lld\n", res.first);
  return 0;
}
