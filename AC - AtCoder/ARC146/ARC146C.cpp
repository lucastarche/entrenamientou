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

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e > 0; b = b * b % MOD, e /= 2)
    if (e & 1) ans = ans * b % MOD;
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  ll curr = modpow(2, n), ans = (curr + 1) % MOD;
  rep(k, 0, n) {
    curr = curr * (modpow(2, n) + MOD - modpow(2, k)) % MOD;
    curr = curr * modinv(k + 2) % MOD;
    ans = (ans + curr) % MOD;
  }
  cout << ans << '\n';
}
