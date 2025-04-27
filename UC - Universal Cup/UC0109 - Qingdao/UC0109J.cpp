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

const ll INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    int zeros = 0;

    vl a;
    a.reserve(n);
    rep(i, 0, n) {
      ll x;
      cin >> x;

      if (x > 0) a.push_back(x);
      zeros += (x == 0);
    }
    n = sz(a), m -= zeros;

    if (n == m) {
      cout << "Richman" << '\n';
      continue;
    } else if (m < 0) {
      cout << "Impossible" << '\n';
      continue;
    }

    cout << accumulate(a.begin(), a.begin() + m, 0LL) + *min_element(a.begin() + m, a.end()) - 1 << '\n';
  }
}
