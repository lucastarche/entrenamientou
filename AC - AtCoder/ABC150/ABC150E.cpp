#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (a); --i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll MOD = 1e9 + 7;
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
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vl w(n);
  rep(i, 0, n) w[i] = (ll)(2 * i + 1) * modpow(4, n - 1) % MOD;

  vi c(n);
  rep(i, 0, n) cin >> c[i];
  sort(rall(c));

  ll ans = 0;
  rep(i, 0, n) ans = (ans + (ll)(c[i]) * w[i]) % MOD;
  cout << ans << '\n';
}
