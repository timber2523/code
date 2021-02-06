#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
const int kMaxN = 55;
const int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
char mp[kMaxN][kMaxN];
int n;

namespace Dinic {
static const int kMaxV = kMaxN * kMaxN;
static const int kMaxE = (kMaxV << 1) + (kMaxV * 4);
static const ll kInfL = 5e17;
int s, t, g[kMaxV], gg[kMaxV], d[kMaxV], ec = 0, vc = 0;
struct Edge {
  int to, nxt;
  ll f;
} e[kMaxE << 1];
void init(int _s, int _t, int _vc) {
  s = _s, t = _t, vc = _vc, ec = 0;
  for (int i = 1; i <= vc; ++i) g[i] = -1;
}
void ae(int u, int v, ll f) {
  e[ec] = (Edge) { v, g[u], f }, g[u] = ec++;
  e[ec] = (Edge) { u, g[v], 0 }, g[v] = ec++;
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
  if (!su) d[u] = -1;
  return su;
}
ll dinic() {
  ll su = 0;
  while (lb())
    su += aug(s, kInfL);
  return su;
}
}

int main() {
  while (~scanf("%s", mp[++n] + 1))
    ;
  --n;
  for (int i = 1; i <= n; ++i) {
    mp[i][0] = mp[i][n + 1] = mp[0][i] = mp[n + 1][i] = 'X';
  }
  Dinic::init(n * n + 1, n * n + 2, n * n + 2);
  ll ans = 0;
  for (int cx = 1; cx <= n; ++cx) {
    for (int cy = 1; cy <= n; ++cy) {
      if (mp[cx][cy] == '.') {
        Dinic::ae(n * n + 1, (cx - 1) * n + cy, 1);
        // printf("%d -> %d\n", n * n + 1, (cx - 1) * n + cy);
        for (int d = 0; d < 4; ++d) {
          int nx = cx + dx[d], ny = cy + dy[d];
          if (mp[nx][ny] == 'O') {
            Dinic::ae((cx - 1) * n + cy, (nx - 1) * n + ny, Dinic::kInfL);
            // printf("%d -> %d\n", (cx - 1) * n + cy, (nx - 1) * n + ny);
          }
        }
        ++ans;
      } else if (mp[cx][cy] == 'O') {
        Dinic::ae((cx - 1) * n + cy, n * n + 2, 1);
        // printf("%d -> %d\n", (cx - 1) * n + cy, n * n + 2);
        ++ans;
      }
    }
  }
  printf("%lld\n", ans - Dinic::dinic());
  return 0;
}
