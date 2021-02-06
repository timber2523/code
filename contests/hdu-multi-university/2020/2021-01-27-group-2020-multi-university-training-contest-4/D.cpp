#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll kInfL = 5e17;
const int kMaxN = 2e5 + 5, kMaxM = 8e5 + 5;
int T, n, m, s, t, x;
char str[kMaxN];

namespace Dijkstra {
static const int kMaxV = kMaxN;
static const int kMaxE = kMaxM;
int g[kMaxV], ec = 0, vc = 0, vis[kMaxV];
ll d[kMaxV];
typedef pair<ll, int> Node;
struct Edge {
  int to, nxt;
  ll w;
} e[kMaxE << 1];
void init(int _vc) {
  vc = _vc, ec = 0;
  for (int i = 1; i <= vc; ++i)
    g[i] = -1;
}
inline void ae(int u, int v, ll w) {
  e[ec] = (Edge){v, g[u], w}, g[u] = ec++;
  e[ec] = (Edge){u, g[v], w}, g[v] = ec++;
}
ll sssp(int s, int t) {
  priority_queue<Node, vector<Node>, greater<Node>> Q;
  for (int i = 1; i <= vc; ++i)
    d[i] = kInfL, vis[i] = 0;
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
        if (!vis[e[i].to])
          Q.push({d[e[i].to], e[i].to});
      }
    }
  }
  return d[t];
}
} // namespace Dijkstra

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &x);
    scanf("%s", str + 1);
    Dijkstra::init(n * 2);
    for (int i = 1, u, v, w; i <= m; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      if (str[u] == 'M') {
        if (str[v] == 'L' || str[v] == 'M') {
          Dijkstra::ae(u, v, w); // L -> L
          Dijkstra::ae(u + n, v, w + x); // R -> L
        }
        if (str[v] == 'R' || str[v] == 'M') {
          Dijkstra::ae(u, v + n, w + x); // L -> R
          Dijkstra::ae(u + n, v + n, w); // R -> R
        }
      } else if (str[u] == 'L') {
        if (str[v] == 'L' || str[v] == 'M') {
          Dijkstra::ae(u, v, w);
        }
        if (str[v] == 'R' || str[v] == 'M') {
          Dijkstra::ae(u, v + n, w + x);
        }
      } else if (str[u] == 'R') {
        if (str[v] == 'L' || str[v] == 'M') {
          Dijkstra::ae(u + n, v, w + x);
        }
        if (str[v] == 'R' || str[v] == 'M') {
          Dijkstra::ae(u + n, v + n, w);
        }
      }
    }
    ll ans = kInfL;
    if (str[s] == 'L' || str[s] == 'M') {
      Dijkstra::sssp(s, t);
      ans = min(ans, min(Dijkstra::d[t], Dijkstra::d[t + n]));
    }
    if (str[s] == 'R' || str[s] == 'M') {
      Dijkstra::sssp(s + n, t);
      ans = min(ans, min(Dijkstra::d[t], Dijkstra::d[t + n]));
    }
    printf("%lld\n", ans);
  }
  return 0;
}
