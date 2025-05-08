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

const int MAX_X = 1e3;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vi freq(2 * MAX_X + 1);
    rep(i, 0, n) {
      int x;
      cin >> x;
      freq[x + MAX_X]++;
    }

    ll ans = 0;
    rep(x, -MAX_X, MAX_X + 1) {
      int fx = freq[x + MAX_X];
      ans += (ll)(fx) * (fx - 1) / 2LL;
      rep(y, x + 1, MAX_X + 1) {
        int fy = freq[y + MAX_X], d = (x + y) / 2;
        if (fy == 0 || 2 * d != x + y) continue;
        if (freq[d + MAX_X] > 0) ans += (ll)(fx)*fy;
      }
    }

    cout << ans << '\n';
  }
}
