#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 1e5 + 5;
int T, n, q, c[kMaxN], v[kMaxN], l[kMaxN], r[kMaxN], ts;
int ans[kMaxN];
struct FenwickTree {
  int a[kMaxN];
  inline int lowbit(int x) { return x & -x; }
  inline int query(int x) {
    int res = 0;
    for (; x > 0; x -= lowbit(x))
      res += a[x];
    return res;
  }
  inline void add(int x, int v) {
    for (; x < kMaxN; x += lowbit(x))
      a[x] += v;
  }
} a[2], b[2];
struct Query {
  int tim, pos, val, typ;
  inline bool operator<(const Query &other) const {
    return tim < other.tim || (tim == other.tim && typ < other.typ);
  }
};
vector<Query> Q[kMaxN];
vector<int> G[kMaxN];
int cv[kMaxN], cc[kMaxN];
void dfs(int x, int fa) {
  l[x] = ++ts;
  for (int u : G[x]) {
    if (u != fa) dfs(u, x);
  }
  r[x] = ts;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> c[i];
      cc[i] = c[i];
    }
    for (int i = 1; i <= n; ++i) {
      cin >> v[i];
      cv[i] = v[i];
      Q[c[i]].push_back((Query){0, i, v[i], 1});
    }
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    dfs(1, 0);
    cin >> q;
    for (int i = 1, opt, x, c, v; i <= q; ++i) {
      cin >> opt;
      if (opt == 1) {
        cin >> x >> v;
        Q[cc[x]].push_back((Query){i, x, cv[x], -1});
        Q[cc[x]].push_back((Query){i, x, cv[x] = v, 1});
      } else {
        cin >> x >> c;
        Q[cc[x]].push_back((Query){i, x, cv[x], -1});
        Q[cc[x] = c].push_back((Query){i, x, cv[x], 1});
      }
    }
    for (int c = 1; c <= n; ++c) {
      sort(Q[c].begin(), Q[c].end());
      for (int j = 0; j < 20; ++j) {
        for (const Query &cur : Q[c]) {
          int p = (cur.val >> j) & 1;
          a[p].add(cur.pos, cur.typ);
          ans[cur.tim] += (a[p].query(n) - a[p].query(r[cur.pos]) + a[p].query(l[cur.pos] - 1)); 
          ans[cur.tim] -= a[p ^ 1].query(r[cur.pos]) - a[p ^ 1].query(l[cur.pos] - 1);
        }
        for (const Query &cur : Q[c]) {
          int p = (cur.val >> j) & 1;
          a[p].add(cur.pos, -cur.typ);
        }
      }
    }
    for (int i = 1; i <= q; ++i) {
      ans[i] += ans[i - 1];
    }
    for (int i = 0; i <= q; ++i) {
      cout << ans[i] << endl;
    }
  }
  return 0;
}
