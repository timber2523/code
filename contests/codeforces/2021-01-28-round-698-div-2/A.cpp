#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 105;
int t, n, cnt[kMaxN];

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    memset(cnt, 0x00, sizeof cnt);
    for (int i = 1, x; i <= n; ++i) {
      scanf("%d", &x);
      ++cnt[x];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans = max(ans, cnt[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
