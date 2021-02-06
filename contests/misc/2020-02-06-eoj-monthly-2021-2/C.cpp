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

int n, q;

namespace SubTask1 {
const int kMaxN = 15;
int a[kMaxN];
struct Limit {
  int l, r, v;
} b[kMaxN];
int resolve() {
  for (int i = 0; i < n; ++i) {
    a[i] = i;
  }
  for (int i = 1; i <= q; ++i) {
    ri(b[i].l), ri(b[i].r), ri(b[i].v);
  }
  do {
    bool flag = true;
    for (int i = 1; i <= q; ++i) {
      int m = kInf;
      for (int j = b[i].l; j <= b[i].r; ++j) {
        m = min(m, a[j]);
      }
      if (m != b[i].v) {
        flag = false;
        break;
      }
    }
    if (flag) {
      for (int i = 0; i < n; ++i) {
        printf("%d%c", a[i], " \n"[i == n]);
      }
      return 0;
    }
  } while (next_permutation(a, a + n));
  for (int i = 1; i <= n; ++i) {
    printf("-1%c", " \n"[i == n]);
  }
  return 0;
}
} // namespace SubTask1

int main() {
  ri(n), ri(q);
  if (n <= 10 && q <= 10) {
    return SubTask1::resolve(); // 23pts
  }
  return 0;
}
