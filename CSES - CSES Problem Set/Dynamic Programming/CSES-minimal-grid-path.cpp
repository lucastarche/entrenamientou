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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<string> a(n);
  rep(i, 0, n) cin >> a[i];

  string ans;
  ans += a[0][0];

  vb can(1, true);
  rep(d, 0, 2 * n - 2) {  // x + y == d
    char best = 'Z';
    rep(i, 0, d + 1) {
      if (!can[i]) continue;
      int x = i, y = d - i;
      if (x >= n || y < 0) continue;

      if (x + 1 < n) best = min(best, a[x + 1][y]);
      if (y + 1 < n) best = min(best, a[x][y + 1]);
    }

    ans += best;
    vb next(d + 2);
    rep(i, 0, sz(can)) {
      if (!can[i]) continue;
      int x = i, y = d - i;
      if (x >= n || y < 0) continue;

      if (x + 1 < n && a[x + 1][y] == best) next[i + 1] = true;
      if (y + 1 < n && a[x][y + 1] == best) next[i] = true;
    }

    swap(can, next);
  }

  cout << ans << '\n';
}
