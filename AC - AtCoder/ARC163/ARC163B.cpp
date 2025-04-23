#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, l, r;
  cin >> n >> m >> l >> r;
  n -= 2;

  vi a(n);
  rep(i, 0, n) cin >> a[i];
  sort(all(a));

  ll ans = INF;
  rep(i, 0, n - m + 1) {
    int x = a[i], y = a[i + m - 1];
    ans = min(ans, (ll)max(l - x, 0) + max(y - r, 0));
  }

  cout << ans << '\n';
}
