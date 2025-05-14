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

ll modinv(ll x) { return modpow(x, MOD - 2); }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll n;
  cin >> n;
  ll x = n * n, y = (n * n + 1) / 2, z = (n * n + 3) / 4;

  ll o4 = (modpow(2, x) + MOD - modpow(2, y)) % MOD;
  ll o2 = (modpow(2, y) + MOD - modpow(2, z)) % MOD;
  ll o1 = modpow(2, z);

  cout << (o4 * modinv(4) + o2 * modinv(2) + o1) % MOD << '\n';
}
