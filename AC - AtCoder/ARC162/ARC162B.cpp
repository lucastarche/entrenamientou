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

void applyOp(vi &p, int i, int j) {
  int x = p[i], y = p[i + 1];
  p.erase(p.begin() + i, p.begin() + i + 2);
  p.insert(p.begin() + j, {x, y});
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi p(n);
  rep(i, 0, n) cin >> p[i], p[i]--;

  bool even = true;
  rep(i, 0, n) rep(j, i + 1, n) even ^= p[i] > p[j];

  if (not even) {
    cout << "No\n";
    return 0;
  }

  cout << "Yes\n";

  vii ans;
  const auto op = [&](int i, int j) {
    ans.emplace_back(i + 1, j);
    applyOp(p, i, j);
  };

  rep(i, 0, n - 1) {
    int pos = -1;
    rep(j, i, n) if (p[j] == i) pos = j;

    if (pos + 1 == n) op(pos - 1, i), pos = i + 1;
    if (pos != i) op(pos, i);
  }

  cout << sz(ans) << '\n';
  for (auto [i, j] : ans) cout << i << ' ' << j << '\n';
}
