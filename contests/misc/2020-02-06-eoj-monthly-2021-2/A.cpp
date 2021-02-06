#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

namespace FastInput {
static const int kBufSiz = 1 << 20; // 1M
char buf[kBufSiz], *S = buf, *T = buf, ch;
bool neg;
inline bool fetch() { return T = (S = buf) + fread(buf, 1, kBufSiz, stdin), S != T; }
inline char nc() { return S == T ? (fetch() ? *S++ : EOF) : *S++; }
template <typename Int> inline void ri(Int &x) {
  x = neg = 0;
  for (ch = nc(); isspace(ch); ch = nc())
    ;
  if (ch == '-')
    ch = nc(), neg = 1;
  for (; isdigit(ch); ch = nc())
    x = x * 10 + ch - '0';
  if (neg)
    x = -x;
}
} // namespace FastInput
using FastInput::ri;

const int kMaxN = 5e4 + 5;
int n, q, ec, dep[kMaxN], ind[kMaxN], oud[kMaxN], dfn;
int f[kMaxN][21], dp[kMaxN][21];
vector<pii> G[kMaxN];

void dfs(int u, int fa) {
  dep[u] = dep[fa] + 1;
  ind[u] = ++dfn;
  for (int i = 1; (1 << i) <= dep[u]; ++i) {
    f[u][i] = f[f[u][i - 1]][i - 1];
    dp[u][i] = dp[f[u][i - 1]][i - 1] + dp[u][i - 1];
  }
  for (int i = 0; i < (int)G[u].size(); ++i) {
    int v = G[u][i].first;
    if (v == fa)
      continue;
    f[v][0] = u;
    dp[v][0] = G[u][i].second;
    dfs(v, u);
  }
  oud[u] = dfn;
}

int getlca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (int i = 20; i >= 0; --i) {
    if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
  }
  for (int i = 20; i >= 0; --i) {
    if (f[x][i] != f[y][i])
      x = f[x][i], y = f[y][i];
  }
  return f[x][0];
}

int getfa(int x, int lca) {
  for (int i = 20; i >= 0; --i) {
    if (dep[f[x][i]] > dep[lca]) x = f[x][i];
  }
  return x;
}

int ans = 0;

int getcost(int x, int lca) {
  int res = 0;
  for (int i = 20; i >= 0; --i) {
    if (dep[f[x][i]] >= dep[lca]) {
      res += dp[x][i];
      x = f[x][i];
    }
  }
  return res;
}

void resolve(const vector<int> &vec, int last) {
  if (vec.size() == 1) {
    ans += getcost(vec[0], last);
    return;
  }
  int lca = getlca(vec[0], vec[1]);
  for (int i = 2; i < (int)vec.size(); ++i) {
    lca = getlca(lca, vec[i]);
  }
  if (last != -1) {
    ans += getcost(lca, last);
  }
  bool vis[5];
  memset(vis, 0x00, sizeof vis);
  for (int i = 0; i < (int)vec.size(); ++i) {
    if (vec[i] == lca)
      continue;
    if (vis[i])
      continue;
    int trt = getfa(vec[i], lca);
    vis[i] = true;
    vector<int> p;
    p.push_back(vec[i]);
    for (int j = 0; j < (int)vec.size(); ++j) {
      if (!vis[j])
        if (ind[trt] <= ind[vec[j]] && ind[vec[j]] <= oud[trt])
          vis[j] = true, p.push_back(vec[j]);
    }
    resolve(p, lca);
  }
}

int main() {
  ri(n);
  for (int i = 1, u, v, w; i < n; ++i) {
    ri(u), ri(v), ri(w);
    ++u, ++v;
    G[u].push_back(make_pair(v, w));
    G[v].push_back(make_pair(u, w));
  }
  for (int i = 1; i <= n; ++i) {
    sort(G[i].begin(), G[i].end());
  }
  dfs(1, 0);
  ri(q);
  for (int i = 1; i <= q; ++i) {
    ans = 0;
    vector<int> vec;
    for (int j = 0, x; j < 5; ++j)
      ri(x), vec.push_back(x + 1);
    resolve(vec, -1);
    printf("%d\n", ans);
  }
  return 0;
}
