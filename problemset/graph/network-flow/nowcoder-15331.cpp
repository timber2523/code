#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace FastInput {
static const int kBufSiz = 1 << 20; // 1M
char buf[kBufSiz], *S = buf, *T = buf, ch;
bool neg;
inline bool fetch() { return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T; }
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

const int kMaxN = 105, kMaxM = 1005;

namespace SSP {
static const int kMaxV = kMaxN * 2 + kMaxM;
static const int kMaxE = kMaxV * 2;
int s, t, vc, ec, g[kMaxV], v[kMaxV];
ll d[kMaxV], pre[kMaxV], mnf[kMaxV];
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
ll aug() {
  for (int i = 0; i <= vc; ++i) {
    mnf[i] = kInfL;
    v[i] = 0;
    d[i] = -kInfL;
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
pair<ll, ll> mcmf(int k) {
  ll co = 0, flo = 0;
  int cnt = 0;
  while (++cnt <= k && aug()) {
    flo += mnf[t];
    for (int cur = t; cur != s; cur = e[pre[cur] ^ 1].to) {
      e[pre[cur]].f -= mnf[t], e[pre[cur] ^ 1].f += mnf[t];
      co += mnf[t] * e[pre[cur]].c;
    }
  }
  return make_pair(co, flo);
}
} // namespace SSP

int T, n, m, k;
int a[kMaxN];

int main() {
  ri(T);
  for (int _ = 1; _ <= T; ++_) {
    ri(n), ri(m), ri(k);
    int sz = n * 2 + 2, s, t;
    SSP::init(sz, s = sz - 1, t = sz);
    for (int i = 1; i <= n; ++i) {
      ri(a[i]);
      SSP::ae(s, i, 1, 0);
      SSP::ae(i, i + n, 1, a[i]);
      SSP::ae(i, i + n, kInfL, 0);
      SSP::ae(i + n, t, 1, 0);
    }
    for (int i = 1, u, v, c; i <= m; ++i) {
      ri(u), ri(v), ri(c);
      SSP::ae(u + n, v, kInfL, -c);
    }
    printf("Case #%d: %lld\n", _, SSP::mcmf(k).first);
  }
  return 0;
}
