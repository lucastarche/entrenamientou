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

  int n, m;
  cin >> n >> m;
  vi a(n), b(m);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, m) cin >> b[i];

  vector<vi> dp(n + 1, vi(m + 1, 0));
  rep(i, 0, n + 1) rep(j, 0, m + 1) {
    if (i + 1 <= n) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
    if (j + 1 <= m) dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
    if (i + 1 <= n && j + 1 <= m && a[i] == b[j]) dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
  }

  vi ans;
  int i = n, j = m;
  while (i > 0 && j > 0) {
    if (dp[i - 1][j - 1] + 1 == dp[i][j] && a[i - 1] == b[j - 1]) {
      ans.push_back(a[i - 1]);
      i--, j--;
    } else if (dp[i - 1][j] == dp[i][j]) {
      i--;
    } else {
      j--;
    }
  }

  reverse(all(ans));
  cout << sz(ans) << '\n';
  rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i + 1 == sz(ans)];
}
