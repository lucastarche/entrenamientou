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
using vd = vector<ld>;
const ld EPS = 1e-4;
const ld INF = 1e18;

bool check(const vl &a, const vl &b, int k, ld lambda) {
  const int n = sz(a);
  vd w(n);
  rep(i, 0, n) w[i] = (ld)(a[i]) - lambda * (ld)(b[i]);
  sort(all(w));

  ld tot = 0;
  rep(i, k, n) tot += w[i];
  return tot >= 0.0l;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, k; cin >> n >> k, n != 0 || k != 0;) {
    vl a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];

    ld lo = 0.0, hi = 1.0;
    while (hi - lo > EPS) {
      ld mid = (lo + hi) / 2.0l;
      if (check(a, b, k, mid)) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    cout << (int)round(100.0l * lo) << '\n';
  }
}
