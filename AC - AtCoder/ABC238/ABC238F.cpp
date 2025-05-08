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

const int MOD = 998244353;

void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}

vi readPerm(int n) {
  vi p(n), q(n);
  rep(i, 0, n) cin >> p[i], p[i]--;
  rep(i, 0, n) cin >> q[i], q[i]--;

  vi pinv(n);
  rep(i, 0, n) pinv[p[i]] = i;

  vi ans(n);
  rep(i, 0, n) ans[i] = q[pinv[i]];
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;
  auto p = readPerm(n);

  vector<vi> dp(k + 1, vi(n + 1, 0));
  dp[0][n] = 1;

  for (auto x : p) {
    vector<vi> next(k + 1, vi(n + 1, 0));

    rep(i, 0, k + 1) rep(j, 0, n + 1) {
      if (i + 1 <= k && x < j) add(next[i + 1][j], dp[i][j]);
      add(next[i][min(x, j)], dp[i][j]);
    }

    swap(next, dp);
  }

  int ans = 0;
  rep(i, 0, n + 1) add(ans, dp[k][i]);
  cout << ans << '\n';
}
