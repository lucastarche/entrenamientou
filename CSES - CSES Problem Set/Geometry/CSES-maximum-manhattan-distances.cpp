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

  int n;
  cin >> n;

  ll maxX = -INF, minX = INF, maxY = -INF, minY = INF;
  rep(i, 0, n) {
    ll x, y;
    cin >> x >> y;
    tie(x, y) = pair<ll, ll>(x + y, x - y);

    maxX = max(maxX, x);
    minX = min(minX, x);
    maxY = max(maxY, y);
    minY = min(minY, y);

    cout << max(maxX - minX, maxY - minY) << '\n';
  }
}
