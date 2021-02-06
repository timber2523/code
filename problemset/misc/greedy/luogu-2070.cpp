#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kMaxN = 1e5 + 5;
int n, x;
char ch;
vector<pii> v;

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, d; i <= n; ++i) {
    cin >> d >> ch;
    if (ch == 'R') {
      v.push_back(make_pair(x, x + d));
      x += d;
    } else {
      v.push_back(make_pair(x - d, x));
      x -= d;
    }
  }
  sort(v.begin(), v.end(), [](const pii &lhs, const pii &rhs) {
      return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second);
      });
  int l = v[0].first, r = v[0].second, ans = 0;
  for (int i = 1; i < (int)v.size(); ++i) {
    if (v[i].second > l) {
      l = max(l, v[i].first);
      if (v[i].second > r) {
        ans += r - l;
        l = r;
        r = v[i].second;
      } else {
        ans += v[i].second - l;
        l = v[i].second;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
