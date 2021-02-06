#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const ll kMaxN = 2e5 + 5;
ll t, n, k, x[kMaxN], y[kMaxN];

ll gcd(ll a, ll b) {
  return b == 0 ? a : gcd(b, a % b);
}

int main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", x + i);
    }
    for (int i = 1; i < n; ++i) {
      y[i] = x[i] - x[n];
    }
    ll p = y[1];
    for (int i = 2; i < n; ++i) {
      p = gcd(p, y[i]);
    }
    if ((k - x[n]) % p == 0)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}
