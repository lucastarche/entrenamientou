#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
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
const int MAX_X = 1e5;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vi mu(MAX_X + 1, 1);
  vl mult(MAX_X + 1, 0);
  vector<vi> divi(MAX_X + 1);
  rep(d, 1, MAX_X + 1) {
    bool prime = sz(divi[d]) == 1;
    for (int n = d; n <= MAX_X; n += d) {
      divi[n].push_back(d);
      if (prime) mu[n] *= -1;
      mult[n] = (mult[n] + MOD + (n / d) * mu[d]) % MOD;
    }

    if (prime) {
      for (ll n = (ll)d * d; n <= MAX_X; n += (ll)d * d) mu[n] = 0;
    }
  }

  int n;
  cin >> n; 
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  ll ans = 0, pow2 = 1LL;
  vl F(MAX_X + 1, 0);
  rep(i, 0, n) {
    ans = (2LL * ans) % MOD;

    for (auto d : divi[a[i]]) {
      ans = (ans + F[d] * mult[d]) % MOD;
      F[d] = (F[d] + pow2) % MOD;
    }

    cout << ans << '\n';
    pow2 = (2LL * pow2) % MOD;
  }
}
