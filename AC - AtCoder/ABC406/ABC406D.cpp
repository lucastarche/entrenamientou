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

  int h, w, n;
  cin >> h >> w >> n;

  set<pii> byX, byY;
  rep(i, 0, n) {
    int x, y;
    cin >> x >> y;
    byX.emplace(x, y);
    byY.emplace(y, x);
  }

  int q;
  cin >> q;
  while (q--) {
    int type, k;
    cin >> type >> k;

    int ans = 0;

    auto &curr = (type == 1 ? byX : byY);
    auto &other = (type == 1 ? byY : byX);

    auto iter = curr.lower_bound(pii(k, -1));
    while (iter != curr.end() && iter->first == k) {
      auto [x, y] = *iter;
      other.erase(pii(y, x));
      iter = curr.erase(iter);
      ans++;
    }
    cout << ans << '\n';
  }
}
