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

const int MAX_N = 800;
const ll MOD = 998244353;
vl fact(MAX_N + 1, 1), facti(MAX_N + 1, 1);

ll modpow(ll x, ll y) {
  ll ans = 1;
  for (; y > 0; x = x * x % MOD, y /= 2)
    if (y & 1) ans = ans * x % MOD;
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

void init() {
  rep(i, 0, MAX_N) fact[i + 1] = fact[i] * (i + 1) % MOD;
  facti.back() = modinv(fact.back());
  per(i, 0, MAX_N) facti[i] = facti[i + 1] * (i + 1) % MOD;
}

ll choose(ll n, ll k) { return fact[n] * (facti[k] * facti[n - k] % MOD) % MOD; }

ll countPaths(const vii &pos, int n) {
  const int k = sz(pos);
  if (k <= n) {
    ll ans = 0;
    rep(i, 0, k) rep(j, 0, k) {
      int dx = pos[i].first - pos[j].first;
      int dy = pos[i].second - pos[j].second;
      if (dx < 0 || dy < 0) continue;
      ans = (ans + choose(dx + dy, dx)) % MOD;
    }
    return ans;
  }

  vector<vl> dp(n, vl(n, 0));
  for (auto [x, y] : pos) dp[x][y]++;

  rep(i, 0, n) rep(j, 0, n) {
    if (i + 1 < n) dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
    if (j + 1 < n) dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD;
  }

  ll ans = 0;
  for (auto [x, y] : pos) ans = (ans + dp[x][y]) % MOD;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  init();

  int n;
  cin >> n;

  vector<vii> byPos(n * n);
  rep(i, 0, n) rep(j, 0, n) {
    int x;
    cin >> x, x--;
    byPos[x].emplace_back(i, j);
  }

  ll ans = 0;
  rep(i, 0, n * n) ans = (ans + countPaths(byPos[i], n)) % MOD;
  cout << ans << '\n';
}
