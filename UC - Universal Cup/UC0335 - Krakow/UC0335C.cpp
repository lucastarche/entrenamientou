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

const ll INF = 1e18;

template <typename T>
bool chmax(T &lhs, T rhs) {
  if (lhs < rhs) return lhs = rhs, true;
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vl> a(n, vl(m));
    rep(i, 0, n) rep(j, 0, m) cin >> a[i][j];

    vector<vector<vl>> dp(n, vector<vl>(m, vl(2, -INF)));
    dp[0][0][0] = a[0][0];

    rep(i, 0, n) rep(j, 0, m) {
      rep(k, 0, 2) {
        if (i + 1 < n) chmax(dp[i + 1][j][k], dp[i][j][k] + a[i + 1][j]);
        if (j + 1 < m) chmax(dp[i][j + 1][k], dp[i][j][k] + a[i][j + 1]);
      }

      if (i + 2 < n && j > 0) chmax(dp[i + 2][j - 1][1], dp[i][j][0] + a[i + 1][j] + a[i + 1][j - 1] + a[i + 2][j - 1]);
      if (i + 1 < n && j > 0) chmax(dp[i + 1][j][1], dp[i][j][0] + a[i + 1][j - 1] + a[i + 1][j]);
    }

    cout << *max_element(all(dp[n - 1][m - 1])) << '\n';
  }
}
