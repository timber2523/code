#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 305;

namespace ZKW {
static const int kMaxV = 3 * kMaxN;
static const int kMaxE = 9 * kMaxN;
int s, t, vc, ec, g[kMaxV], v[kMaxV], gg[kMaxV];
ll d[kMaxV], pre[kMaxV], mnf[kMaxV], co, flo;
struct Edge {
  int to, nxt;
  ll f, c;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
  s = _s, t = _t, vc = _vc;
  ec = 0;
  for (int i = 0; i <= vc; ++i) {
    g[i] = -1;
  }
}
inline void ae(int u, int v, ll f, ll c) {
  e[ec] = (Edge){v, g[u], f, c}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0, -c}, g[v] = ec++;
}
ll lb() {
  for (int i = 0; i <= vc; ++i) {
    d[i] = mnf[i] = kInfL;
    v[i] = 0;
    gg[i] = g[i];
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
ll aug(int u, ll m) {
  if (u == t) {
    v[u] = 1;
    return m;
  }
  v[u] = 1;
  ll su = 0, f;
  for (int i = gg[u]; ~i; gg[u] = i = e[i].nxt) {
    if ((!v[e[i].to] || e[i].to == t) && e[i].f && d[u] + e[i].c == d[e[i].to]) {
      f = aug(e[i].to, min(m, e[i].f));
      e[i].f -= f, e[i ^ 1].f += f;
      m -= f, su += f;
      co += f * e[i].c;
      if (m == 0)
        break;
    }
  }
  if (!su)
    d[u] = -1;
  return su;
}
pair<ll, ll> mcmf() {
  co = flo = 0;
  while (lb()) {
    v[t] = 1;
    while (v[t]) {
      fill(v, v + vc + 1, 0);
      flo += aug(s, kInfL);
    }
  }
  return make_pair(co, flo);
}
} // namespace ZKW

int T, n, k, a, b;
ll c[kMaxN];

int main() {
  scanf("%d", &T);
  while (T --> 0) {
    scanf("%d%d%d%d", &n, &k, &a, &b);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", c + i);
    }
    int s, t, sz = 2 * n + 10, p = n - k + 1;
    ZKW::init(sz, s = sz - 1, t = sz);
    int _ = 0;
    for (int i = 1; i <= k; ++i)
      ZKW::ae(0, min(i, p), 1, -c[i]), ++_;
    for (int i = 1; i <= n - 2 * k; ++i)
      ZKW::ae(i, min(i + k, p), 1, -c[i + k]), ++_;
    for (int i = max(n - 2 * k + 1, 1); i <= n - k; ++i)
      ZKW::ae(i, p, 1, -c[i + k]), ++_;
    assert(_ == n);
    ZKW::ae(s, 0, b, 0);
    ZKW::ae(p, t, a, 0);
    for (int i = 1; i <= n - k; ++i) {
      ZKW::ae(s, i, b - a, 0);
    }
    for (int i = p + 1; i <= p + p; ++i) {
      ZKW::ae(i - p, i, kInfL, 0);
      ZKW::ae(i - p - 1, i, kInfL, 0);
      ZKW::ae(i, t, b - a, 0);
    }
    printf("%lld\n", -ZKW::mcmf().first);
  }
  return 0;
}

