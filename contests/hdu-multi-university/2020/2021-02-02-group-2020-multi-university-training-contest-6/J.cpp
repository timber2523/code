#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kMaxN = 105, kMaxM = 1e4 + 5, kMod = 998244353;
ll a[kMaxN][kMaxN];
int t, n, m;
struct Edge { int u, v, w; } e[kMaxM];
ll det(int n, int p);
ll inv(ll i) { return i == 1 ? 1 : (kMod - kMod / i) * inv(kMod % i) % kMod; }

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    memset(a, 0x00, sizeof a);
    for (int i = 1, u, v, w; i <= m; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      e[i].u = u, e[i].v = v, e[i].w = w;
      ++a[u][u], ++a[v][v];
      --a[u][v], --a[v][u];
    }
    ll tot = abs(det(n - 1, kMod)), ans = 0;
    for (int i = 0; i <= 30; ++i) {
      memset(a, 0x00, sizeof a);
      for (int j = 1; j <= m; ++j) {
        if ((e[j].w >> i) & 1) {
          --a[e[j].u][e[j].v], --a[e[j].v][e[j].u];
          ++a[e[j].u][e[j].u], ++a[e[j].v][e[j].v];
        }
      }
      ans += (1LL << i) * abs(det(n - 1, kMod)) % kMod;
      ans %= kMod;
    }
    printf("%lld\n", (ans * inv(tot) % kMod + kMod) % kMod);
  }
  return 0;
}

ll det(int n, int p) {
  ll ans = 1;
  bool flag = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      a[i][j] = (a[i][j] + p) % p;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j)
      while (a[j][i]) {
        ll t = a[i][i] / a[j][i];
        for (int k = i; k <= n; ++k)
          a[i][k] = (a[i][k] + p - t * a[j][k] % p) % p;
        for (int k = i; k <= n; ++k)
          swap(a[i][k], a[j][k]);
        flag ^= 1;
      }
    ans = ans * a[i][i] % p;
    if (!ans) return 0;
  }
  if (!flag) ans = (p - ans);
  return ans;
}
