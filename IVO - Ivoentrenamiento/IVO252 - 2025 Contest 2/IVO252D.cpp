#include <bits/stdc++.h>
#pragma GCC optimize("O3")
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

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vi a;
    a.reserve(n);
    rep(i, 0, n) {
      int x;
      cin >> x;
      if (x % 2 == 0) a.push_back(x / 2);
    }

    int target = (n + 1) / 2;
    n = sz(a);

    if (n < target) {
      cout << "NO\n";
      continue;
    }

    int g = 0;
    rep(i, 0, n) g = __gcd(g, a[i]);

    if (g != 1) {
      cout << "NO\n";
      continue;
    } else if (target > 8) {
      cout << "YES\n";
      continue;
    }

    bool can = false;
    map<int, int> best;
    best[0] = 0;
    rep(i, 0, n) {
      vii update;
      for (auto [x, y] : best) update.emplace_back(__gcd(a[i], x), y + 1);
      for (auto [x, y] : update) {
        if (best.count(x) == 0 || best[x] > y) best[x] = y;
      }

      if (best.count(1) && best[1] <= target) {
        can = true;
        break;
      }
    }

    cout << (can ? "YES" : "NO") << '\n';
  }
}
