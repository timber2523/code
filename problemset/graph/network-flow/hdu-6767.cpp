#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;

const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace FastInput {
static const int kBufSiz = 1 << 20;
char buf[kBufSiz], *S = buf, *T = buf, ch;
bool neg;
inline bool fetch() {
  return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T;
}
inline char nc() { return S == T ? (fetch() ? *S++ : EOF) : *S++; }
template <typename Int> void ri(Int &x) {
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
const int kMaxN = 55;

namespace SSP {
static const int kMaxV = kMaxN * kMaxN * 4;
static const int kMaxE = kMaxV;
int s, t, vc, ec, g[kMaxV], vis[kMaxV];
ll dis[kMaxV], pre[kMaxV], mnf[kMaxV];
struct Edge {
  int to, nxt;
  ll f, c;
} e[kMaxE << 1];
void init(int _s, int _t, int _vc) {
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
    dis[i] = mnf[i] = kInfL;
    vis[i] = 0;
  }
  queue<int> Q;
  Q.push(s);
  mnf[t] = 0;
  dis[s] = 0;
  vis[s] = 1;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    vis[u] = 0;
    for (int i = g[u]; ~i; i = e[i].nxt) {
      if (!e[i].f || dis[u] + e[i].c >= dis[e[i].to])
        continue;
      dis[e[i].to] = dis[u] + e[i].c;
      pre[e[i].to] = i;
      mnf[e[i].to] = min(mnf[u], e[i].f);
      if (!vis[e[i].to]) {
        vis[e[i].to] = 1;
        Q.push(e[i].to);
      }
    }
  }
  return mnf[t];
}
vector<ll> mcmf(int n) {
  vector<ll> res;
  ll psu = 0;
  for (int i = 1; i <= n; ++i) {
    aug();
    ll su = 0;
    for (int cur = t; cur != s; cur = e[pre[cur] ^ 1].to) {
      e[pre[cur]].f -= mnf[t], e[pre[cur] ^ 1].f += mnf[t];
      su += mnf[t] * e[pre[cur]].c;
    }
    psu += su;
    res.push_back(psu);
  }
  return res;
}
} // namespace SSP

int T, n, m;
ll a[kMaxN], b[kMaxN], c[kMaxN];

unordered_map<ll, int> pool;
int memcnt;
inline int alloc(ll v) {
  if (pool.count(v))
    return pool[v];
  return pool[v] = ++memcnt;
}

int main() {
  // freopen("1005.in", "r", stdin);
  // freopen("1005.out", "w", stdout);
  ri(T);
  while (T--) {
    ri(n), ri(m);
    for (int i = 1; i <= n; ++i) {
      ri(a[i]), ri(b[i]), ri(c[i]);
    }
    vector<tuple<int, int, ll, ll>> d;
    memcnt = n + 2;
    pool.clear();
    for (int i = 1; i <= n; ++i) {
      ll mid = -b[i] / (a[i] * 2);
      for (ll j = max(1LL, min(mid, 1LL * m) - n + 1); j <= min(1LL * m, max(mid, 1LL) + n - 1); ++j) {
        d.push_back(make_tuple(i, alloc(j), 1, a[i] * j * j + b[i] * j + c[i]));
        // cout << j << endl;
      }
    }
    SSP::init(n + 1, n + 2, memcnt);
    for (const auto &i : d) {
      SSP::ae(get<0>(i), get<1>(i), get<2>(i), get<3>(i));
    }
    for (int i = 1; i <= n; ++i) {
      SSP::ae(SSP::s, i, 1, 0);
    }
    for (int i = n + 3; i <= memcnt; ++i) {
      SSP::ae(i, SSP::t, 1, 0);
    }
    auto res = SSP::mcmf(n);
    for (int i = 1; i <= (int)res.size(); ++i) {
      printf("%lld%c", res[i - 1], " \n"[i == (int)res.size()]);
    }
  }
  return 0;
}

// 1
// 3 5
// 2 3 10
// 2 -3 10
// 1 -1 4