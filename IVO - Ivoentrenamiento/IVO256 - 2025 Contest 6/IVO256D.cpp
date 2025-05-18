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

using ld = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  map<int, vi> byVal;
  rep(i, 0, n) {
    int x;
    cin >> x;
    byVal[x].push_back(i);
  }

  ld ans = 0.0l;
  for (const auto &[_, v] : byVal) {
    ll sumSqrd = (ll)v[0] * v[0] + (ll)(n - v.back() - 1) * (n - v.back() - 1);
    rep(i, 0, sz(v) - 1) sumSqrd += (ll)(v[i + 1] - v[i] - 1) * (v[i + 1] - v[i] - 1);
    ans += 1.0l - (ld)sumSqrd / (ld)((ll)n * n);
  }
  cout << fixed << setprecision(10) << ans << '\n';
}
