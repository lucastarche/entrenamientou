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

  vi cmp;
  vii segments(n);
  rep(i, 0, n) {
    int l, r;
    cin >> l >> r;
    segments[i] = {l, r};
    cmp.push_back(2 * l), cmp.push_back(2 * r), cmp.push_back(l + r);
  }

  sort(all(cmp));
  cmp.erase(unique(all(cmp)), cmp.end());

  const auto compress = [&](int x) { return (int)(lower_bound(all(cmp), x) - cmp.begin()); };

  // Orden decreciente de longitud
  sort(all(segments), [&](pii lhs, pii rhs) { return (lhs.second - lhs.first) > (rhs.second - rhs.first); });

  ll ans = 0;
  FT ft(sz(cmp));
  for (auto [l, r] : segments) {
    int m = compress(l + r);
    l = compress(2 * l), r = compress(2 * r);
    ans += ft.query(r + 1) - ft.query(l);
    ft.update(m, +1);
  }
  cout << ans << '\n';
}
