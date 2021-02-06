#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll t, b, x;

int main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld", &b, &x);
    puts((b - 1) % x == 0 ? "T" : "F");
  }
  return 0;
}
