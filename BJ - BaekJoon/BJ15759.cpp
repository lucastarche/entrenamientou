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

using ld = double;
using vd = vector<ld>;
const ld EPS = 1e-6;
const ld INF = 1e9;

bool check(const vi &w, const vi &t, const int W, ld lambda) {
  const int n = sz(w);
  vd dp(W + 1, -INF);
  dp[0] = 0;
  rep(i, 0, n) per(j, 0, W + 1) {
    int nj = min(W, j + w[i]);
    dp[nj] = max(dp[nj], dp[j] + (ld)(t[i]) - lambda * (ld)(w[i]));
  }
  return dp[W] > 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  // ifstream cin("talent.in");
  // ofstream cout("talent.out");

  int n, W;
  cin >> n >> W;

  vi w(n), t(n);
  rep(i, 0, n) cin >> w[i] >> t[i];

  ld lo = 0.0, hi = INF;
  while (hi - lo > EPS) {
    ld mid = (lo + hi) / 2.0l;
    if (check(w, t, W, mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << (ll)floor(1000.0l * hi) << '\n';
}
