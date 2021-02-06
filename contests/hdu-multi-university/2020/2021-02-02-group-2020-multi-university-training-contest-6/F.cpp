#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kMod = 1e9 + 7;
const int kMaxN = 1e5 + 5, kMaxM = 2e5 + 5;
int t, n, m, a[kMaxN], fa[kMaxN], cnt0, cnt1;
ll pow2[kMaxM];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
ll quickpow(ll x, ll y) {
  ll res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1)
      res = (res * x) % kMod;
    x = (x * x) % kMod;
  }
  return res;
}
int g[kMaxN], ec;
ll p[kMaxN], q[kMaxN], ans;
struct Edge { int to, nxt; ll w; } e[kMaxN << 1];
inline void ae(int u, int v, ll w) {
  e[ec] = (Edge) { v, g[u], w }, g[u] = ec++;
}
void dfs(int u, int fa = -1) {
  p[u] = q[u] = 0;
  for (int i = g[u]; ~i; i = e[i].nxt) {
    if (e[i].to == fa)
      continue;
    dfs(e[i].to, u);
    ans += e[i].w * (p[e[i].to] * (cnt1 - q[e[i].to]) % kMod + q[e[i].to] * (cnt0 - p[e[i].to]) % kMod) % kMod;
    ans %= kMod;
    p[u] += p[e[i].to];
    q[u] += q[e[i].to];
  }
  p[u] += (a[u] == 0);
  q[u] += (a[u] == 1);
}

int main() {
  scanf("%d", &t);
  pow2[0] = 1;
  for (int i = 1; i < kMaxM; ++i) {
    pow2[i] = pow2[i - 1] * 2LL % kMod;
  }
  while (t--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
    }
    ec = cnt0 = cnt1 = ans = 0;
    for (int i = 1; i <= n; ++i) {
      fa[i] = i;
      g[i] = -1;
      cnt0 += (a[i] == 0);
      cnt1 += (a[i] == 1);
    }
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%d%d", &u, &v);
      int fu = find(u), fv = find(v);
      if (fu != fv) {
        fa[fu] = fv;
        ae(u, v, pow2[i]);
        ae(v, u, pow2[i]);
      }
    }
    dfs(1);
    printf("%lld\n", ans);
  }
  return 0;
}
