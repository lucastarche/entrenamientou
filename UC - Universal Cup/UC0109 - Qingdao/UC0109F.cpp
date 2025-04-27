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

vector<vi> step(const vector<vi> &a) {
  const int n = sz(a);
  vector<vi> ans(2 * n, vi(2 * n));
  rep(i, 0, n) rep(j, 0, n) {
    ans[i][j] = ans[i + n][j + n] = a[i][j];
    ans[i + n][j] = ans[i][j + n] = n + a[i][j];
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    int d = 1;
    vector<vi> a(1, vi(1, 0));
    while (n % (2 * d) == 0) a = step(a), d *= 2;

    if (sz(a) - 1 >= k) {
      rep(i, 1, k + 1) {
        for (int x = 0; x < n; x += d) {
          rep(j, 0, d) cout << a[i][j] + x + 1 << " \n"[x + j + 1 == n];
        }
      }
    } else {
      cout << "Impossible" << '\n';
    }
  }
}
