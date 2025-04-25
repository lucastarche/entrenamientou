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

const ll MAX_K = 200;
const ll MAX_X = 1e18;

vl z;
vector<vl> dp;

void init() {
  z.push_back(1);
  while (z.back() <= MAX_X) z.push_back(4LL * z.back() + 1LL);

  dp.resize(sz(z), vl(MAX_K, 0));
  rep(i, 0, sz(z) - 1) {
    dp[i][1]++;
    rep(delta, 0, 4) rep(k, 0, MAX_K - delta) dp[i + 1][k + delta] += dp[i][k];
  }
}

ll cnt(ll lim, ll k) {
  if (k >= MAX_K || lim == 0) return 0;
  int zi = sz(z) - 1;
  ll ans = 0;
  while (zi >= 0 && k >= 0) {
    if (z[zi] <= lim) {
      ans += dp[zi][k];
      lim -= z[zi];
      k--;
    } else {
      zi--;
    }
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  init();

  int t;
  cin >> t;
  while (t--) {
    ll l, r, k;
    cin >> l >> r >> k;
    cout << cnt(r, k) - cnt(l - 1, k) << '\n';
  }
}
