#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 1e4 + 5;
int t, q, d, f[105];

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &q, &d);
    vector<int> ans;
    for (int i = 0; i < d; ++i) {
      ans.push_back(i * 10 + d);
    }
    memset(f, 0x00, sizeof f);
    f[0] = 1;
    for (int i = 0; i < (int)ans.size(); ++i) {
      for (int j = ans[i]; j <= 100; ++j) {
        f[j] |= f[j - ans[i]];
      }
    }
    for (int i = 1, x; i <= q; ++i) {
      scanf("%d", &x);
      if (x >= d * 10) {
        puts("YES");
      } else {
        puts(f[x] ? "YES" : "NO");
      }
    }
  }
  return 0;
}
