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

  int n, k;
  cin >> n >> k;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  int x = max(n - k, 0), ans = 0;
  rep(i, 0, x) ans = max(ans, a[i] + a[2 * x - i - 1]);
  rep(i, 2 * x, n) ans = max(ans, a[i]);
  cout << ans << '\n';
}
