#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const int dx[8] = {1, 0, -1, -1, -1, 0, 1, 1};
const int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

const ll INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by, ax--, ay--, bx--, by--;

    vector<vi> a(n, vi(n));
    rep(i, 0, n) rep(j, 0, n) cin >> a[i][j];

    if (ax > bx) {
      reverse(all(a)), ax = n - ax - 1, bx = n - bx - 1;
    }

    if (ay > by) {
      rep(i, 0, n) reverse(all(a[i]));
      ay = n - ay - 1, by = n - by - 1;
    }

    vector<vector<vl>> dp(n + 1, vector<vl>(n, vl(n, -INF)));
    dp[0][ax][ay] = 0;
    rep(i, 0, n + 1) {
      per(x, 0, n) per(y, 0, n) {
        if (dp[i][x][y] == -INF) continue;
        if (max(abs(bx - x), abs(by - y)) <= i) continue;

        rep(k, 0, 8) {
          int nx = x + dx[k], ny = y + dy[k];
          if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
          dp[i + 1][nx][ny] = max(dp[i + 1][nx][ny], dp[i][x][y] + a[nx][ny]);
        }
      }
    }

    ll ans = 0;
    rep(i, 0, n + 1) rep(x, 0, n) rep(y, 0, n) ans = max(ans, dp[i][x][y]);
    cout << ans << '\n';
  }
}
