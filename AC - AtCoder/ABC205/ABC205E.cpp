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

ll modpow(ll x, ll y) {
  ll ans = 1;
  for (; y > 0; x = x * x % MOD, y /= 2)
    if (y & 1) ans = (ans * x) % MOD;
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  const int SIZE = n + m + 1;
  vl fact(SIZE, 1), facti(SIZE, 1);
  rep(i, 1, SIZE) fact[i] = fact[i - 1] * i % MOD;
  facti.back() = modinv(fact.back());
  per(i, 1, SIZE) facti[i - 1] = facti[i] * i % MOD;

  const auto choose = [&](int n, int k) {
    if (n < k || k < 0) return 0LL;
    return fact[n] * (facti[n - k] * facti[k] % MOD) % MOD;
  };

  if (n > m + k) {
    cout << 0 << '\n';
    return 0;
  }

  cout << (choose(n + m, n) + MOD - choose(n + m, n - k - 1)) % MOD << '\n';
}
