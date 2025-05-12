#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const int MOD = 1e9 + 7;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;

  vector<string> a(n);
  rep(i, 0, n) cin >> a[i];

  int ans = 1;
  rep(i, 0, n) rep(j, 0, m) {
    bool valid = true;
    rep(k, 0, 4) {
      int x = i + dx[k], y = j + dy[k];
      if (x < 0 || y < 0 || x >= n || y >= m) continue;
      valid &= a[i][j] == a[x][y];
    }

    if (valid) ans = (2 * ans) % MOD;
  }
  cout << ans << '\n';
}