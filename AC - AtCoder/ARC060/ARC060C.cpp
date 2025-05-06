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

const int SIZE = 20;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi x(n);
  rep(i, 0, n) cin >> x[i];

  int L, q;
  cin >> L >> q;

  vector<vi> prev(SIZE, vi(n)), next(SIZE, vi(n));

  rep(i, 0, n) {
    int l = lower_bound(all(x), x[i] - L) - x.begin();
    int r = upper_bound(all(x), x[i] + L) - x.begin();
    prev[0][i] = l, next[0][i] = r - 1;
  }

  rep(i, 0, SIZE - 1) rep(j, 0, n) {
    prev[i + 1][j] = prev[i][prev[i][j]];
    next[i + 1][j] = next[i][next[i][j]];
  }

  while (q--) {
    int a, b;
    cin >> a >> b, a--, b--;

    int ans = 0;
    if (a < b) {
      per(i, 0, SIZE) {
        if (next[i][a] < b) {
          a = next[i][a];
          ans += 1 << i;
        }
      }
    } else {
      per(i, 0, SIZE) {
        if (prev[i][a] > b) {
          a = prev[i][a];
          ans += 1 << i;
        }
      }
    }
    cout << ans + 1 << '\n';
  }
}
