#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int BITS = 30;
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

ll solve(const vector<int> &s, int b = BITS - 1) {
  // We should not proceed further on an empty list, or the complexity would be 2^30
  if (s.empty()) return 0;

  // We need an additional turn to say the numbers are equal
  if (b == -1) return (ll)(s.size()) * (ll)(s.size());

  vector<int> bitUnset, bitSet;
  // Partition s with respect to whether or not the bit b is set
  partition_copy(s.begin(), s.end(), back_inserter(bitUnset), back_inserter(bitSet),
                 [b](int v) { return ((v >> b) & 1) == 0; });

  ll k1 = (ll)bitUnset.size(), k2 = (ll)bitSet.size();

  ll ans = 3LL * k1 * k2;         // Turns between pairs where exactly one is set
  ans += k2 * k2;                 // Extra turns where both are set
  ans += solve(bitUnset, b - 1);  // We remove the bits, and solve recursively for both lists
  ans += solve(bitSet, b - 1);    // starting from the next bit
  ans %= MOD;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    ll ans = solve(s);
    // Divide the sum of turns by the total number of pairs
    ans = (ans * modinv((ll)n * n % MOD /* There was an overflow without (ll) */)) % MOD;
    cout << ans << '\n';
  }
}