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
const ll THRESH = 1e9;
const ll MAX_X = 1e12;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vl a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));

    ll ans = 0, overThresh = 0;
    vl pfx(n + 1);
    rep(i, 0, n) {
      if (a[i] <= THRESH) {
        rep(j, 0, n) {
          ll curr = (a[j] % a[i]) % MOD;
          ans += (curr * curr) % MOD;
          ans %= MOD;
        }
      } else {
        overThresh++;
      }
      pfx[i + 1] = (pfx[i] + a[i]) % MOD;
    }

    rep(i, 0, n) {
      ll aSqrd = (a[i] % MOD) * (a[i] % MOD) % MOD;
      ans = (ans + aSqrd * overThresh) % MOD;
      if (a[i] <= THRESH) continue;

      int prev = lower_bound(all(a), a[i]) - a.begin();
      for (ll x = a[i]; x <= MAX_X; x += a[i]) {
        int j = lower_bound(all(a), x + a[i]) - a.begin();
        ans += (ll)(j - prev) * ((x % MOD) * (x % MOD) % MOD) % MOD, ans %= MOD;
        ans -= 2LL * (pfx[j] - pfx[prev]) * (x % MOD) % MOD, ans = (ans % MOD + MOD) % MOD;
        prev = j;
      }
    }

    cout << ans << '\n';
  }
}
