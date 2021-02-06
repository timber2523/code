// 93pts
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 1005;

namespace SSP {
static const int kMaxV = 1e5 + 5;
static const int kMaxE = 1e5 + 5;
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
int m, n, a[kMaxN][kMaxN];

int main() {
  using namespace SSP;
  scanf("%d%d", &m, &n);
  int p = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m - 1 + i; ++j, ++p)
      scanf("%d", &a[i][j]);
  }
  init(p * 2 + 2, p * 2 + 1, p * 2 + 2);
  for (int i = 1, q = 0; i <= n; ++i) {
    for (int j = 1; j <= m - 1 + i; ++j) {
      ++q;
      if (i == 1) ae(s, q, 1, 0);
      if (i == n) ae(q + p, t, 1, 0);
      else ae(q + p, q + m - 1 + i, 1, 0), ae(q + p, q + m + i, 1, 0);
      ae(q, q + p, 1, a[i][j]);
    }
  }
  printf("%lld\n", mcmf().first);
  init(p * 2 + 2, p * 2 + 1, p * 2 + 2);
  for (int i = 1, q = 0; i <= n; ++i) {
    for (int j = 1; j <= m - 1 + i; ++j) {
      ++q;
      if (i == 1) ae(s, q, 1, 0);
      if (i == n) ae(q + p, t, kInfL, 0);
      else ae(q + p, q + m - 1 + i, 1, 0), ae(q + p, q + m + i, 1, 0);
      ae(q, q + p, kInfL, a[i][j]);
    }
  }
  printf("%lld\n", mcmf().first);
  init(p * 2 + 2, p * 2 + 1, p * 2 + 2);
  for (int i = 1, q = 0; i <= n; ++i) {
    for (int j = 1; j <= m - 1 + i; ++j) {
      ++q;
      if (i == 1) ae(s, q, 1, 0);
      if (i == n) ae(q + p, t, kInfL, 0);
      else ae(q + p, q + m - 1 + i, kInfL, 0), ae(q + p, q + m + i, kInfL, 0);
      ae(q, q + p, kInfL, a[i][j]);
    }
  }
  printf("%lld\n", mcmf().first);
  return 0;
}
