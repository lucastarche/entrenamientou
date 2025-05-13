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

ll gauss(ll x) { return x * (x + 1) / 2; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  map<int, vi> where;
  rep(i, 0, n) {
    int x;
    cin >> x;
    where[x].push_back(i);
  }

  ll ans = 0;
  for (const auto &[_, v] : where) {
    ans += gauss(n);
    ans -= gauss(v[0]);
    ans -= gauss(n - v.back() - 1);
    rep(i, 1, sz(v)) ans -= gauss(v[i] - v[i - 1] - 1);
  }
  cout << ans << '\n';
}
