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

  int n, k;
  cin >> n >> k;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  vi cmp = a;
  sort(all(cmp));
  cmp.erase(unique(all(cmp)), cmp.end());
  rep(i, 0, n) a[i] = lower_bound(all(cmp), a[i]) - cmp.begin();

  const int N = sz(cmp);
  ll ans = 0;
  FT ft(N);

  const auto add = [&](int x) { ans += ft.query(N) - ft.query(x + 1), ft.update(x, +1); };
  const auto remove = [&](int x) { ans -= ft.query(x), ft.update(x, -1); };

  rep(i, 0, k) add(a[i]);
  cout << ans << ' ';

  rep(i, k, n) {
    remove(a[i - k]), add(a[i]);
    cout << ans << ' ';
  }
  cout << '\n';
}
