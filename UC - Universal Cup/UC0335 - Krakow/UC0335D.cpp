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

const int MAX_N = 1e6;
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
const ll HALF = modinv(2);

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vl f(MAX_N + 1);
  for (ll n = 1; n <= MAX_N; n++) {
    ll p = modinv(n * n % MOD), pC = (1LL + MOD - p) % MOD;
    f[n] = (p + pC * (f[n - 1] + 1LL)) % MOD;
  }

  int q;
  cin >> q;
  while (q--) {
    int i;
    cin >> i;
    cout << f[i] << '\n';
  }
}
