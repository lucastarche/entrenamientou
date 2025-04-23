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

const ll MOD = 998244353;

ll modpow(ll x, ll y) {
  ll ans = 1;
  while (y > 0) {
    if (y % 2 == 1) ans = (ans * x) % MOD;
    x = (x * x) % MOD, y /= 2;
  }
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n;
  cin >> n;
  vi d(n);
  rep(i, 0, n) cin >> d[i];

  vl fact(n + 1, 1), facti(n + 1, 1);
  rep(i, 0, n) fact[i + 1] = (fact[i] * (i + 1)) % MOD;
  facti.back() = modinv(fact.back());
  per(i, 0, n) facti[i] = (facti[i + 1] * (i + 1)) % MOD;

  int leaves = count(all(d), 0);
  ll denom = facti[d[0] - 1], ans = fact[n - 2] * (leaves + 1) % MOD;
  rep(i, 1, n) denom = (denom * facti[d[i]]) % MOD;

  vector<vl> ways(n, vl(n, 0));
  ways[0][0] = 1;
  per(i, 1, n) {
    rep(k, 2, n) {
      if (k - d[i] - 1 < 0) continue;
      ll weight = (fact[n - k - 1] * fact[k - 2]) % MOD;
      weight = (weight * d[i]) % MOD;
      ans = (ans + ways[k - 1][k - d[i] - 1] * weight % MOD) % MOD;
    }

    per(k, 0, n - 1) rep(sum, 0, n - d[i]) ways[k + 1][sum + d[i]] = (ways[k + 1][sum + d[i]] + ways[k][sum]) % MOD;
  }

  ans = (ans * denom) % MOD;

  cout << ans << '\n';
}
