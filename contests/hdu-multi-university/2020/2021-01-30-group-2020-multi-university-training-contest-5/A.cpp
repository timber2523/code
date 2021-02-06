#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kMod = 998244353;
const int kMaxN = 6e6 + 5;
ll T, n, ans[kMaxN], inv[kMaxN];

int main() {
  ios::sync_with_stdio(false);
  cin >> T;
  inv[1] = 1;
  for (int i = 2; i < kMaxN; ++i)
    inv[i] = (kMod - kMod / i * inv[kMod % i]) % kMod;
  for (int i = 1; i < kMaxN; ++i)
    ans[i] = (ans[i - 1] + inv[i] * inv[i] % kMod) % kMod;
  while (T--) {
    cin >> n;
    cout << ((3 * inv[n] * ans[n]) % kMod + kMod) % kMod << endl;
  }
  return 0;
}
