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
using pll = pair<ll, ll>;
using vll = vector<pll>;

const ll INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<vl> p(n, vl(n)), r(n, vl(n - 1)), d(n - 1, vl(n));
  rep(i, 0, n) rep(j, 0, n) cin >> p[i][j];
  rep(i, 0, n) rep(j, 0, n - 1) cin >> r[i][j];
  rep(i, 0, n - 1) rep(j, 0, n) cin >> d[i][j];

  vector<vll> dp(n, vll(n, {INF, INF}));
  dp[0][0] = {0, 0};

  rep(x, 0, n) rep(y, 0, n) {
    vector<vl> dist(n, vl(n, INF));
    dist[x][y] = 0;

    rep(i, x, n) rep(j, y, n) {
      if (i + 1 < n) dist[i + 1][j] = min(dist[i + 1][j], dist[i][j] + d[i][j]);
      if (j + 1 < n) dist[i][j + 1] = min(dist[i][j + 1], dist[i][j] + r[i][j]);
    }

    rep(i, x, n) rep(j, y, n) {
      // La plata está negativa, sumar es restar
      ll work = max((dist[i][j] + dp[x][y].second + p[x][y] - 1) / p[x][y], 0LL);
      dp[i][j] = min(dp[i][j], {dp[x][y].first + work, dp[x][y].second + dist[i][j] - work * p[x][y]});
    }
  }

  cout << dp[n - 1][n - 1].first + (2 * n - 2) << '\n';
}
