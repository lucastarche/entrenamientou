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

void solve(const vi &a, vi &ans, int k, int b) {
  if (b == -1) return;

  vi off, on;
  rep(i, 0, 1 << b) off.push_back(a[i]), on.push_back(a[i + (1 << b)]);
  solve(off, ans, k, b - 1);
  rep(i, 0, 1 << b) {
    ans[k + (1 << b) + i] = max(ans[k + (1 << b) + i], off[i] + on[i]);
    on[i] = max(off[i], on[i]);
  }
  solve(on, ans, k + (1 << b), b - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(1 << n);
  rep(i, 0, 1 << n) cin >> a[i];

  vi ans(1 << n);
  solve(a, ans, 0, n - 1);
  rep(i, 1, 1 << n) ans[i] = max(ans[i], ans[i - 1]);
  rep(i, 1, 1 << n) cout << ans[i] << '\n';
}
