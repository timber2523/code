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

const int kMaxN = 5005;
int n, m, k;
vector<int> G[kMaxN];
vector<pii> h;
int d[kMaxN][kMaxN];
bool vis[kMaxN];

void bfs(int s) {
  for (int i = 1; i <= n; ++i)
    vis[i] = 0;
  queue<int> Q;
  Q.push(s);
  vis[s] = 1;
  while (!Q.empty()) {
    int u = Q.front();
    for (int to : G[u]) {
      if (vis[to]) continue;

    }
  }
}

int main() {
  ri(n), ri(m);
  for (int i = 1, u, v; i <= m; ++i) {
    ri(u), ri(v);
    ++u, ++v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    bfs(i);
  }
  ri(k);
  for (int i = 1, a, b; i <= k; ++i) {
    ri(a), ri(b);
    ++a, ++b;
    h.push_back(make_pair(a, b));
  }
  return 0;
}
