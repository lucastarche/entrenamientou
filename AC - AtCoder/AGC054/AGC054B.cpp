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

const ll MOD = 998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi w(n);
  rep(i, 0, n) cin >> w[i];

  int total = accumulate(all(w), 0);
  if (total % 2 != 0) {
    cout << 0 << '\n';
    return 0;
  }

  vector<vl> ways(n + 1, vl(total + 1, 0));
  ways[0][0] = 1;
  for (auto x : w) {
    per(i, 0, n) rep(j, 0, total - x) ways[i + 1][j + x] = (ways[i + 1][j + x] + ways[i][j]) % MOD;
  }

  vl fact(n + 1, 1);
  rep(i, 0, n) fact[i + 1] = fact[i] * (i + 1) % MOD;

  ll ans = 0;
  rep(i, 0, n + 1) ans = (ans + ways[i][total / 2] * (fact[i] * fact[n - i] % MOD) % MOD) % MOD;
  cout << ans << '\n';
}
