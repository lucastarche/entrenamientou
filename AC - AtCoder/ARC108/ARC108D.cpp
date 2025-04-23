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

const ll MOD = 1e9 + 7;

char opp(char c) { return (c == 'A' ? 'B' : 'A'); }

ll modpow(ll x, ll y) {
  ll ans = 1;
  while (y > 0) {
    if (y % 2 == 1) ans = (ans * x) % MOD;
    x = (x * x) % MOD, y /= 2;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  char caa, cab, cba, cbb;
  cin >> n >> caa >> cab >> cba >> cbb;

  if (n <= 3) {
    cout << 1 << '\n';
    return 0;
  }

  if (cab == 'B') {
    swap(caa, cbb);
    caa = opp(caa), cab = opp(cab), cba = opp(cba), cbb = opp(cbb);
  }

  // cab = 'A'

  if (caa == 'A') {
    cout << 1 << '\n';
    return 0;
  }

  // cab = 'A', caa = 'B'

  if (cba == 'B') {
    cout << modpow(2, n - 3) << '\n';
    return 0;
  }

  // cab = 'A', caa = 'B', cba = 'A'

  vector<vl> dp(n + 1, vl(2, 0));
  dp[1][0] = 1;
  rep(i, 1, n) {
    dp[i + 1][0] = (dp[i][0] + dp[i][1]) % MOD;
    dp[i + 1][1] = dp[i][0];
  }
  cout << dp[n][1] << '\n';
}
