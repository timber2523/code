#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 2e3 + 5;

namespace SSP {
static const int kMaxV = kMaxN * 2;
static const int kMaxE = kMaxV * 8;
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
    d[i] = mnf[i] = kInfL;
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
      if (!e[i].f || d[u] + e[i].c >= d[e[i].to])
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

int n, r[kMaxN];

int main() {
  using namespace SSP;
  scanf("%d", &n);
  init(n * 2 + 2, n * 2 + 1, n * 2 + 2);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", r + i);
    ae(s, i + n, r[i], 0);
    ae(i, t, r[i], 0);
  }
  int P, M, F, N, S;
  scanf("%d%d%d%d%d", &P, &M, &F, &N, &S);
  for (int i = 1; i <= n - M; ++i) {
    ae(i + n, i + M, kInfL, F);
  }
  for (int i = 1; i <= n - N; ++i) {
    ae(i + n, i + N, kInfL, S);
  }
  for (int i = 1; i <= n - 1; ++i) {
    ae(i + n, i + n + 1, kInfL, 0);
  }
  for (int i = 1; i <= n; ++i) {
    ae(s, i, kInfL, P);
  }
  printf("%lld\n", mcmf().first);
  return 0;
}
