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

const int MAX_D = 8;
using Grid = array<array<int, MAX_D>, MAX_D>;
const int MAX_OPS = 20;

int h, w;

Grid op(Grid a, int x, int y) {
  rep(i, 0, h - 1) rep(j, 0, w - 1) {
    int ni = h - i - 2, nj = w - j - 2;
    if (tie(i, j) < tie(ni, nj)) {
      swap(a[i + x][j + y], a[ni + x][nj + y]);
    }
  }
  return a;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> h >> w;

  Grid source, target;
  rep(i, 0, MAX_D) rep(j, 0, MAX_D) source[i][j] = target[i][j] = 0;
  rep(i, 0, h) rep(j, 0, w) cin >> source[i][j], target[i][j] = i * w + j + 1;

  if (source == target) {
    cout << "0\n";
    return 0;
  }

  set<Grid> lhs, rhs;
  lhs.insert(source), rhs.insert(target);

  rep(ans, 1, MAX_OPS + 1) {
    set<Grid> next;
    for (auto a : lhs) {
      rep(x, 0, 2) rep(y, 0, 2) {
        auto grid = op(a, x, y);

        if (rhs.count(grid)) {
          cout << ans << '\n';
          return 0;
        }
        next.insert(grid);
      }
    }

    swap(lhs, next);
    swap(lhs, rhs);
  }

  cout << "-1\n";
}
