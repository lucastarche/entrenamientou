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

const int BITS = 20;
const ll MOD = 1e9 + 7;

void FST(vi& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j, i, i + step) {
        int &u = a[j], &v = a[j + step];
        tie(u, v) = inv ? pii(v, u - v) : pii(u + v, u);  // OR
      }
  }
  // if (inv) for (int& x : a) x /= sz(a); // XOR only /// include-line
}

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e > 0; b = b * b % MOD, e /= 2)
    if (e & 1) ans = ans * b % MOD;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  int allOnes = (1 << BITS) - 1;
  vi freq(1 << BITS, 0);
  rep(i, 0, n) {
    int x;
    cin >> x;
    freq[allOnes ^ x]++;
  }

  FST(freq, false);
  ll ans = 0;
  rep(i, 0, 1 << BITS) {
    ll sign = (__builtin_popcount(i) % 2 == 0 ? +1 : -1);
    ans = (ans + 2 * MOD + sign * (modpow(2, freq[i]) - 1)) % MOD;
  }
  cout << ans << '\n';
}
