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
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % MOD, e /= 2)
    if (e & 1) ans = ans * b % MOD;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vb prime(n + 1, true);
  vi mu(n + 1, 1);
  prime[0] = prime[1] = false;
  rep(p, 2, n + 1) {
    if (not prime[p]) continue;
    mu[p] = -1;
    for (int k = 2 * p; k <= n; k += p) mu[k] *= -1, prime[k] = false;
    for (ll k = (ll)(p)*p; k <= n; k += (ll)(p)*p) mu[k] = 0;
  }

  vi freq(n + 1);
  rep(i, 0, n) {
    int x;
    cin >> x;
    freq[x]++;
  }

  vl g(n + 1);
  rep(i, 1, n + 1) for (int j = i; j <= n; j += i) g[i] += freq[j];
  rep(i, 1, n + 1) g[i] = (modpow(2, g[i]) + MOD - 1) % MOD;

  vl f(n + 1);
  rep(d, 1, n + 1) {
    for (int k = d; k <= n; k += d) f[d] = (f[d] + MOD + mu[k / d] * g[k]) % MOD;
  }

  rep(i, 1, n + 1) cout << f[i] << " \n"[i == n];
}
