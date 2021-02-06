#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 1e5 + 5;
ll d[kMaxN << 1], t, n, a[kMaxN << 1];

int main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld", &n);
    map<ll, int> mp;
    bool valid = true;
    for (int i = 1; i <= n * 2; ++i) {
      scanf("%lld", d + i);
      mp[d[i]]++;
      if (d[i] & 1)
        valid = false;
    }
    int cnt = 0;
    for (pair<ll, int> i : mp) {
      if (i.second & 1) {
        valid = false;
        break;
      }
      for (int j = 1; j * 2 <= i.second; ++j) {
        a[++cnt] = i.first >> 1;
      }
    }
    mp.clear();
    ll res = 0;
    for (int i = n; i >= 1; --i) {
      if ((a[i] - res) % i != 0) {
        valid = false;
        break;
      }
      ++mp[(a[i] - res) / i];
      res += (a[i] - res) / i;
    }
    for (pair<ll, int> i : mp) {
      if (i.second > 1) {
        valid = false;
        break;
      }
      if (i.first <= 0 && i.second > 0) {
        valid = false;
        break;
      }
    }
    if (valid)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}
