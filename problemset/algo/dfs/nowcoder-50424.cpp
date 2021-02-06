#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 5005;
bool vis[kMaxN];
int k, n, ans;
char s[kMaxN];

bool dfs(int x, int d) {
  if (vis[x]) return 0;
  s[d] = (x & 1) + '0';
  if (d == n + k - 1)
    return 1;
  vis[x] = 1;
  if (dfs((x << 1) & (n - 1), d + 1)) {
    return 1;
  }
  if (dfs((x << 1 | 1) & (n - 1), d + 1)) {
    return 1;
  }
  vis[x] = 0;
  return 0;
}

int main() {
  scanf("%d", &k), n = (1 << k);
  for (int i = 1; i <= k; ++i) {
    s[i] = '0';
  }
  dfs(0, k);
  s[n + 1] = 0;
  printf("%d %s\n", n, s + 1);
  return 0;
}
