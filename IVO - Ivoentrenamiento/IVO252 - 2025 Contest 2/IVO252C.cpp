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

ll gauss(ll x) { return x * (x + 1) / 2LL; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, k, x;
    cin >> n >> k >> x;

    vi p(k);
    rep(i, 0, k) cin >> p[i];
    sort(all(p));

    ll r = p[0] + x, l = r - (n - k) + 1;
    while (not p.empty() && l <= p.back() && p.back() <= r) l--, p.pop_back();

    ll ans = gauss(r) - gauss(l - 1);
    for (auto y : p) ans += y;
    cout << ans << '\n';
  }
}
