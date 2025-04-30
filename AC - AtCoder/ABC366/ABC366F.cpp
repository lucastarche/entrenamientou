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

  int n, k;
  cin >> n >> k;

  vii f(n);
  rep(i, 0, n) cin >> f[i].first >> f[i].second;

  sort(all(f), [](pii lhs, pii rhs) { return (lhs.first - 1) * rhs.second < (rhs.first - 1) * lhs.second; });

  vl dp(k + 1, 0);
  dp[0] = 1;

  for (const auto &[a, b] : f) {
    per(i, 0, k) dp[i + 1] = max(dp[i + 1], dp[i] * a + b);
  }
  cout << dp[k] << '\n';
}
