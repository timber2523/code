#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 2e5 + 5, kMaxM = 4e5 + 5;

namespace SubTask1 { // 无向图欧拉回路
int n, m, g[kMaxN], vis[kMaxM << 1], ec, d[kMaxN];
int ans[kMaxM];
struct Edge { int to, nxt, id; } e[kMaxM << 1];
inline void ae(int u, int v, int id) {
  e[ec] = (Edge) { v, g[u], id }, g[u] = ec++;
  e[ec] = (Edge) { u, g[v], -id }, g[v] = ec++;
}
inline void init(int n) {
  ec = 0;
  fill(g + 1, g + n + 1, -1);
  fill(vis + 1, vis + n + 1, 0);
  fill(d + 1, d + n + 1, 0);
}
void dfs(int u) {
  for (int &i = g[u]; ~i; ) {
    if (vis[i]) {
      i = e[i].nxt; // 因为后续 i 会改变，所以不能写在最后
      continue;
    }
    vis[i] = vis[i ^ 1] = 1;
    int j = e[i].id;
    dfs(e[i].to);
    ans[++*ans] = j;
  }
}
int solve() {
  scanf("%d%d", &n, &m);
  init(n);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    ae(u, v, i);
    ++d[u], ++d[v];
  }
  for (int i = 1; i <= n; ++i) {
    if (d[i] & 1)
      return puts("NO");
  }
  for (int i = 1; i <= n; ++i) {
    if (~g[i]) {
      dfs(i);
      break;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (~g[i]) {
      return puts("NO");
    }
  }
  assert(*ans == m);
  puts("YES");
  for (int i = m; i >= 1; --i) {
    printf("%d%c", ans[i], " \n"[i == 1]);
  }
  return 0;
}
} // namespace SubTask1

namespace SubTask2 { // 有向图欧拉回路
int n, m, g[kMaxN], vis[kMaxM], ec, d[kMaxN];
int ans[kMaxM];
struct Edge { int to, nxt, id; } e[kMaxM];
inline void ae(int u, int v, int id) {
  e[ec] = (Edge) { v, g[u], id }, g[u] = ec++;
}
inline void init(int n) {
  ec = 0;
  fill(g + 1, g + n + 1, -1);
  fill(vis + 1, vis + n + 1, 0);
  fill(d + 1, d + n + 1, 0);
}
void dfs(int u) {
  for (int &i = g[u]; ~i; ) {
    if (vis[i]) {
      i = e[i].nxt;
      continue;
    }
    vis[i] = 1;
    int j = e[i].id;
    dfs(e[i].to);
    ans[++*ans] = j;
  }
}
int solve() {
  scanf("%d%d", &n, &m);
  init(n);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    ae(u, v, i);
    ++d[u], --d[v];
  }
  for (int i = 1; i <= n; ++i) {
    if (d[i]) {
      return puts("NO");
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (~g[i]) {
      dfs(i);
      break;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (~g[i]) {
      return puts("NO");
    }
  }
  assert(*ans == m);
  puts("YES");
  for (int i = m; i >= 1; --i) {
    printf("%d%c", ans[i], " \n"[i == 1]);
  }
  return 0;
}
} // namespace SubTask2

int main() {
  int t;
  scanf("%d", &t);
  if (t == 1)
    return SubTask1::solve(), 0;
  if (t == 2)
    return SubTask2::solve(), 0;
  return 0;
}
