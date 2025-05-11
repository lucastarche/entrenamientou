#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;
using pll = pair<ll, ll>;

const ll INF = 4e18;

int solve(const vector<pll> &v, const vl &x, ll X) {
  const int n = sz(v);
  if (n == 0) return 0;
  vi freq(n);

  for (auto [m, b] : v) {
    if (m * x.back() + b < X) continue;
    int lo = -1, hi = n - 1;
    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;
      if (m * x[mid] + b < X) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    freq[hi]++;
  }

  int cnt = 0;
  rep(i, 0, n) {
    cnt += freq[i] > 0;
    if (freq[i] > 0 && i + 1 < n) freq[i + 1] += freq[i] - 1;
  }
  return cnt;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<pll> neg, pos;
    vl zero;

    vector<pll> v(n);
    rep(i, 0, n) cin >> v[i].first;
    rep(i, 0, n) cin >> v[i].second;
    for (auto p : v) {
      if (p.first < 0) {
        p.first *= -1;
        neg.push_back(p);
      } else if (p.first == 0) {
        zero.push_back(p.second);
      } else {
        pos.push_back(p);
      }
    }

    vl c(n);
    rep(i, 0, n) cin >> c[i];
    sort(all(c));

    vl xN(sz(neg)), xP(sz(pos));
    rep(i, 0, sz(neg)) xN[i] = -c[i];
    rep(i, 0, sz(pos)) xP[i] = c[i + sz(neg) + sz(zero)];
    reverse(all(xN));

    ll lo = -INF, hi = INF;
    while (hi - lo > 1) {
      ll mid = (lo + hi) / 2LL;

      int cnt = 0;
      for (auto b : zero) cnt += b >= mid;
      cnt += solve(neg, xN, mid);
      cnt += solve(pos, xP, mid);

      if (2 * cnt >= n) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    cout << lo << '\n';
  }
}