#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kMod = 998244353;
const int kMaxN = 5e6 + 5;
ll fac[kMaxN], rfac[kMaxN], ans[kMaxN];
int T, n;

ll quickpow(ll x, ll y) {
  ll res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1)
      res = (res * x) % kMod;
    x = (x * x) % kMod;
  }
  return res;
}

void init() {
  int n = 5e6;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = 1LL * fac[i - 1] * i % kMod;
  }
  rfac[n] = quickpow(fac[n], kMod - 2);
  for (int i = n - 1; i >= 0; --i) {
    rfac[i] = 1LL * rfac[i + 1] * (i + 1) % kMod;
  }
}

ll combin(int n, int m) {
  return fac[n] * rfac[n - m] % kMod * rfac[m] % kMod;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> T;
  init();
  while (T--) {
    cin >> n;
    int m = (n - 1) >> 1;
    for (int i = 1; i <= m; ++i) {
      cout << "0 ";
    }
    ll su = 0;
    for (int i = m + 1; i <= n; ++i) {
      ans[i] = combin(i - 1, n - i) * fac[n - i] % kMod * fac[(2 * i - n - 1)] % kMod * quickpow(rfac[2], (i * 2 - n - 1) >> 1) % kMod * rfac[(2 * i - n - 1) / 2] % kMod;
      su = (su + ans[i]) % kMod;
    }
    ll rsu = quickpow(su, kMod - 2);
    for (int i = m + 1; i <= n; ++i) {
      cout << (rsu * ans[i] % kMod + kMod) % kMod << " \n"[i == n];
    }
  }
  return 0;
}
