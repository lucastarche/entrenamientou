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
using pll = pair<ll, ll>;

const int BITS = 18;
const int SIZE = 1 << BITS;
const int ONES = SIZE - 1;
const ll MOD = 1e9 + 7;

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % MOD, e /= 2)
    if (e & 1) ans = ans * b % MOD;
  return ans;
}

void FST(vl& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j, i, i + step) {
        ll &u = a[j], &v = a[j + step];
        tie(u, v) = inv ? pll(v, (MOD + u - v) % MOD) : pll((u + v) % MOD, u);  // OR
      }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vl freq(SIZE);
  rep(i, 0, n) {
    int x;
    cin >> x;
    freq[~x & ONES]++;
  }

  FST(freq, false);
  rep(i, 0, SIZE) freq[i] = modpow(2, freq[i]);
  FST(freq, true);

  rep(i, 0, n + 1) cout << freq[~i & ONES] << " \n"[i == n];
}
