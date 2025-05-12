#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}

  void update(int pos, ll dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }

  ll query(int pos) {
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vi a(n);
    vector<vi> where(n);
    rep(i, 0, n) {
      cin >> a[i], a[i]--;
      where[a[i]].push_back(i);
    }

    FT ft(n);
    rep(i, 0, n) ft.update(i, +1);

    ll ans = 0;
    rep(i, 0, n) {
      if (where[a[i]].empty()) continue;
      int j = where[a[i]].back();
      where[a[i]].pop_back();

      if (i >= j) continue;

      ans += ft.query(j) - ft.query(i);
      ft.update(i, -1);
      ft.update(j, -1);
    }
    cout << ans << '\n';
  }
}