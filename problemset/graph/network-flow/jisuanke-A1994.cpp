#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 2005, kMaxM = 6005;
int n, m, k, L, R;

namespace ULB_Maxflow {
static const int kMaxV = kMaxN * 3;
static const int kMaxE = kMaxM * 10;
int vc, ss, tt, s, t, ec, g[kMaxV], gg[kMaxV], d[kMaxV];
ll psu;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
inline void ae(int u, int v, ll f) {
  e[ec] = (Edge){v, g[u], f}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], 0}, g[v] = ec++;
}
inline void ae(int u, int v, ll lf, ll rf) {
  d[u] -= lf;
  d[v] += lf;
  ae(u, v, rf - lf);
}
inline void init(int _vc, int _s, int _t, int _ss, int _tt) {
  vc = _vc, s = _s, t = _t, ss = _ss, tt = _tt, ec = 0;
  for (int i = 0; i <= vc; ++i) {
    g[i] = -1;
  }
  for (int i = 0; i <= vc; ++i) {
    d[i] = 0;
  }
  ae(t, s, 0, kInfL);
}
inline void rebuild() {
  psu = 0;
  for (int i = 1; i <= vc; ++i) {    
    if (d[i] < 0)
      ae(i, tt, -d[i]);
    if (d[i] > 0)
      ae(ss, i, d[i]), psu += d[i];
  }
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
bool valid() {
  rebuild();
  swap(t, tt), swap(s, ss);
  ll su = 0;
  while (lb())
    su += aug(s, kInfL);
  swap(t, tt), swap(s, ss);
  // fprintf(stderr, ".%d\n", su);
  return su == psu;
}
pair<bool, ll> maxflow() {
  if (!valid())
    return make_pair(false, 0); 
  ll su = 0;
  while (lb()) {
    su += aug(s, kInfL);
  }
  return make_pair(true, su);
}
} // namespace ULB_Maxflow

int main() {
  int ts = 0;
  while (~scanf("%d%d%d", &n, &m, &k)) {
    using namespace ULB_Maxflow;
    scanf("%d%d", &L, &R);
    int p = n + m;
    // fprintf(stderr, ".%d.%d.%d.%d.%d\n", n, m, p, L, R);
    init(p + 4, p + 1, p + 2, p + 3, p + 4);
    for (int i = 1, u, v; i <= k; ++i) {
      scanf("%d%d", &u, &v);
      ae(u, v + n, 0, 1);
    }
    for (int i = 1; i <= n; ++i) {
      ae(p + 1, i, L, R);
    }
    for (int i = 1; i <= m; ++i) {
      ae(i + n, p + 2, L, R);
    }
    bool flag = false;
    auto res = maxflow();
    if (res.first)
      flag = true;
    printf("Case %d: %s\n", ++ts, flag ? "Yes" : "No");
  }
  return 0;
}