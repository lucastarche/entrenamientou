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
ll modpow(ll x, ll y) {
  ll ans = 1;
  while (y > 0) {
    if (y % 2 == 1) ans = (ans * x) % MOD;
    x = (x * x) % MOD, y /= 2;
  }
  return ans;
}
const ll HALF = modpow(2, MOD - 2);

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    ll a, b;
    cin >> a >> b;

    ll turns = 0;
    while (a != b) {
      ll g = gcd(a, b);
      a /= g, b /= g;

      if (a % 2 != b % 2) {
        turns = -1;
        break;
      }

      if (a > b) swap(a, b);
      b -= a, a *= 2;
      turns++;
    }

    if (turns == -1) {
      cout << 2 << '\n';
    } else {
      cout << (2 + MOD - modpow(HALF, turns)) % MOD << '\n';
    }
  }
}
