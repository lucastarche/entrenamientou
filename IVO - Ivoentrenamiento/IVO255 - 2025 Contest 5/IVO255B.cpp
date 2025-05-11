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

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi p(n), q(n);
  rep(i, 0, n) cin >> p[i], p[i]--;
  rep(i, 0, n) cin >> q[i], q[i]--;

  vi pInv(n);
  rep(i, 0, n) pInv[p[i]] = i;
  rep(i, 0, n) p[i] = pInv[q[i]];

  ll ans = 0;
  FT ft(n);
  rep(i, 0, n) {
    if (ft.query(p[i]) < p[i]) ans++;
    ft.update(p[i], +1);
  }

  cout << ans << '\n';
}
