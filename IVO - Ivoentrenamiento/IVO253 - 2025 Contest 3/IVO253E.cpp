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

ll solve(ll x, ll y, ll z, ll l) {
  ll ans = 0;
  rep(dx, 0, l + 1) {
    ll w = min(l - dx, x + dx - y - z);
    if (w >= 0) ans += (w + 1) * (w + 2) / 2LL;
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll a, b, c, l;
  cin >> a >> b >> c >> l;

  ll total = (l + 3) * (l + 2) * (l + 1) / 6;
  ll ans = solve(a, b, c, l) + solve(b, a, c, l) + solve(c, a, b, l);
  cout << total - ans << '\n';
}
