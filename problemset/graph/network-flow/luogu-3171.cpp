#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;
const int kMaxN = 505, kMaxM = 1e5 + 5;

namespace Dinic {
static const int kMaxV = kMaxN * 2;
static const int kMaxE = kMaxV * 6;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
void init(int _s, int _t, int _vc) {
  s = _s, t = _t, vc = _vc, ec = 0;
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

namespace Dijkstra {
static const int kMaxV = kMaxN;
static const int kMaxE = kMaxM;
int g[kMaxV], ec = 0, vc = 0, vis[kMaxV];
ll d[kMaxV];
typedef pair<ll, int> Node;
vector<Node> pred[kMaxV];
struct Edge {
  int to, nxt;
  ll w;
} e[kMaxE << 1];
void init(int _vc) {
  vc = _vc, ec = 0;
  for (int i = 1; i <= vc; ++i)
    g[i] = -1;
}
inline void ae(int u, int v, ll w) { e[ec] = (Edge){v, g[u], w}, g[u] = ec++; }
ll sssp(int s, int t) {
  priority_queue<Node, vector<Node>, greater<Node>> Q;
  for (int i = 1; i <= vc; ++i)
    d[i] = kInfL, vis[i] = 0, pred[i].clear();
  d[s] = 0;
  Q.push({d[s], s});
  while (!Q.empty()) {
    auto now = Q.top();
    int x = now.second;
    Q.pop();
    if (vis[x])
      continue;
    vis[x] = 1;
    for (int i = g[x]; ~i; i = e[i].nxt) {
      if (d[x] + e[i].w < d[e[i].to]) {
        d[e[i].to] = d[x] + e[i].w;
        pred[e[i].to].clear();
        pred[e[i].to].push_back(make_pair(e[i].w, x));
        if (!vis[e[i].to])
          Q.push({d[e[i].to], e[i].to});
      } else if (d[x] + e[i].w == d[e[i].to]) {
        pred[e[i].to].push_back(make_pair(e[i].w, x));
      }
    }
  }
  return d[t];
}
} // namespace Dijkstra
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  Dijkstra::init(n);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    Dijkstra::ae(u, v, w);
    Dijkstra::ae(v, u, w);
  }
  Dijkstra::sssp(1, n);
  Dinic::init(n * 2 + 2, n * 2 + 1, n * 2 + 2);
  for (int i = 1; i <= n; ++i) {
    ll x;
    scanf("%lld", &x);
    if (i == 1 || i == n) x = kInfL;
    Dinic::ae(i, i + n, x);
  }
  Dinic::ae(Dinic::s, 1, kInfL);
  Dinic::ae(n * 2, Dinic::t, kInfL);
  for (int i = 1; i <= n; ++i) {
    for (const auto &j : Dijkstra::pred[i]) {
      Dinic::ae(j.second + n, i, kInfL);
    }
  }
  printf("%lld\n", Dinic::maxflow());
  return 0;
}
