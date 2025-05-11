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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n);
  map<int, vector<int>> byValue;
  rep(i, 0, n) cin >> a[i], byValue[a[i]].push_back(i);

  vi next(n, n);
  for (const auto &[_, v] : byValue) rep(i, 0, sz(v) - 1) next[v[i]] = v[i + 1];
  per(i, 0, n - 1) next[i] = min(next[i], next[i + 1]);

  ll ans = 0;
  rep(i, 0, n) ans = ans + next[i] - i;
  cout << ans << '\n';
}
