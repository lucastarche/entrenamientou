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

  int n, m, k;
  cin >> n >> m >> k;

  if (n + k < m) {
    cout << 0 << '\n';
    return 0;
  }

  if (m <= k) {
    cout << 1 << '\n';
    return 0;
  }

  ld p = 1.0;
  rep(i, 0, n + m) {
    if (i < n) {  // n!
      p = p * (ld)(i + 1);
    } else {  // m!
      p = p * (ld)(i - n + 1);
    }

    if (i < n + k + 1) {  // (n + k + 1)!
      p = p / (ld)(i + 1);
    } else {  // (m - k - 1)!
      p = p / (ld)(i - n - k);
    }
  }

  cout << fixed << setprecision(10) << 1.0l - p << '\n';
}
