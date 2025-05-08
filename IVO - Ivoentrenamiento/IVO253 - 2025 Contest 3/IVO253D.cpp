#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll x1, x2, y1, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  ll dx = x2 - x1, dy = y2 - y1;

  int n;
  string s;
  cin >> n >> s;

  vl pfxX(n + 1), pfxY(n + 1);
  rep(i, 0, n) pfxX[i + 1] = pfxX[i] - (s[i] == 'R') + (s[i] == 'L');
  rep(i, 0, n) pfxY[i + 1] = pfxY[i] - (s[i] == 'U') + (s[i] == 'D');

  const auto check = [&](ll i) {
    ll moveX = (i / n) * pfxX.back() + pfxX[i % n];
    ll moveY = (i / n) * pfxY.back() + pfxY[i % n];
    ll missing = abs(dx + moveX) + abs(dy + moveY);

    return missing <= i;
  };

  ll lo = 0, hi = 1e18;
  while (hi - lo > 1) {
    ll mid = (lo + hi) / 2;

    if (check(mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  if (check(hi)) {
    cout << hi << '\n';
  } else {
    cout << -1 << '\n';
  }
}
