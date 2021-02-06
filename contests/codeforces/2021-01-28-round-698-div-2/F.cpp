#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int kInf = 0x3f3f3f3f;
const ll kInfL = 5e17;

const int kMaxN = 5005;
int n;
struct Node {
  int first, second;
  int id;
} a[kMaxN];

bool isacute(int i, int j, int k) {
  int x1 = a[i].first - a[j].first, y1 = a[i].second - a[j].second;
  int x2 = a[k].first - a[j].first, y2 = a[k].second - a[j].second;
  return 1LL * x1 * x2 + 1LL * y1 * y2 > 0;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
    a[i].id = i;
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = n - 1; j >= i; --j) {
      if (!isacute(j - 1, j, j + 1))
        swap(a[j], a[j + 1]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    printf("%d%c", a[i].id, " \n"[i == n]);
  }
  return 0;
}
