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

struct Problem {
  int s, c, p;
};

template <typename T>
bool chmax(T &lhs, T rhs) {
  if (lhs < rhs) return lhs = rhs, true;
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, x;
  cin >> n >> x;

  vector<Problem> a(n);
  rep(i, 0, n) cin >> a[i].s >> a[i].c >> a[i].p;

  vector<vd> dp(1 << n, vd(x + 1, 0.0l));

  per(mask, 0, 1 << n) {
    rep(money, 0, x + 1) {
      rep(i, 0, n) if (mask & (1 << i)) dp[mask][money] += a[i].s;
      rep(i, 0, n) {
        if (mask & (1 << i)) continue;
        if (a[i].c > money) continue;
        chmax(dp[mask][money], dp[mask | (1 << i)][money - a[i].c] * (a[i].p) / 100.0L +
                                   dp[mask][money - a[i].c] * (100 - a[i].p) / 100.0L);
      }
    }
  }

  cout << fixed << setprecision(10) << dp[0][x] << '\n';
}
