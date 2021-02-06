#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 105, kMaxM = 5005;
const double eps = 1e-8;

inline double quickpow(double x, ll y) {
  double res = 1.0;
  for (; y > 0; y >>= 1) {
    if (y & 1)
      res = res * x;
    x = x * x;
  }
  return res;
}

namespace SSP {
static const int kMaxV = kMaxN * 4;
static const int kMaxE = kMaxM * 3;
int s, t, vc, ec, g[kMaxV], v[kMaxV];
double d[kMaxV];
ll pre[kMaxV], mnf[kMaxV];
struct Edge {
  int to, nxt;
  ll f;
  double c;
} e[kMaxE << 1];
void init(int _vc, int _s, int _t) {
  s = _s, t = _t, vc = _vc;
  ec = 0;
  for (int i = 1; i <= vc; ++i) {
    g[i] = -1;
  }
}
inline void ae(int u, int v, ll f, double c) {
  e[ec] = (Edge){v, g[u], f, c}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0, -c}, g[v] = ec++;
}
ll aug() {
  for (int i = 1; i <= vc; ++i) {
    d[i] = mnf[i] = kInf;
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
      if (!e[i].f || d[u] + e[i].c >= d[e[i].to] - eps)
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
pair<double, ll> mcmf() {
  double co = 0;
  ll flo = 0;
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

int T, n, m;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    SSP::init(n + 2, n + 1, n + 2);
    for (int i = 1, s, b; i <= n; ++i) {
      scanf("%d%d", &s, &b);
      if (s)
        SSP::ae(n + 1, i, s, 0);
      if (b)
        SSP::ae(i, n + 2, b, 0);
    }
    for (int i = 1, u, v, c; i <= m; ++i) {
      double p;
      scanf("%d%d%d%lf", &u, &v, &c, &p);
      if (c > 0) SSP::ae(u, v, 1, 0);
      if (c - 1 > 0) SSP::ae(u, v, c - 1, -log2(1 - p));
    }
    auto res = SSP::mcmf();
    printf("%.2lf\n", 1.0 - pow(2, -res.first));
  }
  return 0;
}
