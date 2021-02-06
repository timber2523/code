#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;

const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace FastInput {
static const int kBufSiz = 1 << 20; // 1M
char buf[kBufSiz], *S = buf, *T = buf, ch;
bool neg;
inline bool fetch() {
  return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T;
}
inline char nc() { return S == T ? (fetch() ? *S++ : EOF) : *S++; }
template <typename Int> inline void ri(Int &x) {
  x = neg = 0;
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  if (ch == '-')
    ch = nc(), neg = 1;
  for (; isdigit(ch); ch = nc())
    x = x * 10 + ch - '0';
  if (neg)
    x = -x;
}
} // namespace FastInput
using FastInput::ri;

const int kMaxN = 1005, kMaxM = 15005;

namespace Dinic {
static const int kMaxV = kMaxN;
static const int kMaxE = kMaxM;
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
      if (d[x] + 1 < d[e[i].to]) {
        d[e[i].to] = d[x] + 1;
        pred[e[i].to].clear();
        pred[e[i].to].push_back(make_pair(e[i].w, x));
        if (!vis[e[i].to])
          Q.push({d[e[i].to], e[i].to});
      } else if (d[x] + 1 == d[e[i].to]) {
        pred[e[i].to].push_back(make_pair(e[i].w, x));
      }
    }
  }
  return d[t];
}
} // namespace Dijkstra

int t, n, m;
bool vis[kMaxN];

void resolve(int x) {
  if (vis[x])
    return;
  vis[x] = true;
  for (auto j : Dijkstra::pred[x]) {
    Dinic::ae(j.second, x, j.first);
    // cerr << j.second << " " << x << " " << j.first << endl;
    if (!vis[j.second])
      resolve(j.second);
  }
}

int main() {
  ri(t);
  while (t--) {
    ri(n), ri(m);
    Dijkstra::init(n);
    Dinic::init(1, n, n);
    for (int i = 1, u, v, w; i <= m; ++i) {
      ri(u), ri(v), ri(w);
      Dijkstra::ae(u, v, w);
      Dijkstra::ae(v, u, w);
      // Dinic::ae(u, v, w);
      // Dinic::ae(v, u, w);
    }
    Dijkstra::sssp(1, n);
    memset(vis, 0x00, sizeof vis);
    resolve(n);
    printf("%lld\n", Dinic::maxflow());
  }
  return 0;
}
