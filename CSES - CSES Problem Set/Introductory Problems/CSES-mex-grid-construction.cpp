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

  int n;
  cin >> n;
  vector<vi> a(n, vi(n));

  rep(i, 0, n) rep(j, 0, n) {
    vb seen(2 * n + 2);
    rep(x, 0, i) seen[a[x][j]] = true;
    rep(y, 0, j) seen[a[i][y]] = true;

    int mex = 0;
    while (seen[mex]) mex++;
    a[i][j] = mex;
  }

  rep(i, 0, n) rep(j, 0, n) cout << a[i][j] << " \n"[j + 1 == n];
}
