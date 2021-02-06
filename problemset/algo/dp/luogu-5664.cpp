#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kMod = 998244353;
const int kMaxN = 105, kMaxM = 2005;
int n, m;
ll a[kMaxN][kMaxM], sum[kMaxN][kMaxM];
ll f[kMaxN][kMaxN << 1];

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    a[i][0] = 1;
    sum[i][0] = 1;
  }
  ll ans = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%lld", &a[i][j]);
      sum[i][j] = (sum[i][j - 1] + a[i][j] + kMod) % kMod;
    }
    ans = (ans * sum[i][m]) % kMod;
  }
  ans = (ans - 1 + kMod) % kMod;
  for (int c = 1; c <= m; ++c) {
    memset(f, 0x00, sizeof f);
    f[0][n] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int j = n - i; j <= n + i; ++j) {
        f[i][j] = f[i - 1][j];
        f[i][j] = (f[i][j] + (a[i][c] * f[i - 1][j - 1]) % kMod) % kMod;
        f[i][j] =
            (f[i][j] + (sum[i][m] - 1 - a[i][c]) * f[i - 1][j + 1] % kMod) %
            kMod;
      }
    }
    for (int j = n + 1; j <= n * 2; ++j) {
      ans = (ans - f[n][j]) % kMod;
    }
  }
  printf("%lld\n", (ans + kMod) % kMod);
  return 0;
}
