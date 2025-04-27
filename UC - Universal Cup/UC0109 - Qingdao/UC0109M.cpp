#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

int f(int x) {
  if (x == 0) return 1;

  int ans = 0;
  while (x > 0) {
    int d = x % 10;
    x /= 10;
    ans += (d == 0) + (d == 4) + (d == 6) + 2 * (d == 8) + (d == 9);
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int x, k;
    cin >> x >> k;

    while (x > 0 && k > 0) x = f(x), k--;

    if (k == 0) {
      cout << x << '\n';
    } else {
      cout << k % 2 << '\n';
    }
  }
}
