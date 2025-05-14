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

struct TwoSat {
  int N;
  vector<vi> gr;
  vi values;  // 0 = false, 1 = true

  TwoSat(int n = 0) : N(n), gr(2 * n) {}

  void either(int f, int j) {
    f = max(2 * f, -1 - 2 * f);
    j = max(2 * j, -1 - 2 * j);
    gr[f].push_back(j ^ 1);
    gr[j].push_back(f ^ 1);
  }

  vi val, comp, z;
  int time = 0;
  int dfs(int i) {
    int low = val[i] = ++time, x;
    z.push_back(i);
    for (int e : gr[i])
      if (!comp[e]) low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
        x = z.back();
        z.pop_back();
        comp[x] = low;
        if (values[x >> 1] == -1) values[x >> 1] = x & 1;
      } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2 * N, 0);
    comp = val;
    rep(i, 0, 2 * N) if (!comp[i]) dfs(i);
    rep(i, 0, N) if (comp[2 * i] == comp[2 * i + 1]) return 0;
    return 1;
  }
};

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const vector<string> OPTIONS = {"BC", "AC", "AB"};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<string> a(n);
  rep(i, 0, n) cin >> a[i];

  TwoSat ts(n * m);
  const auto index = [&](int x, int y) { return x * m + y; };

  rep(x, 0, n) rep(y, 0, m) {
    rep(k, 0, 4) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

      int i = a[x][y] - 'A', j = a[nx][ny] - 'A';
      if (OPTIONS[i][0] == OPTIONS[j][0]) ts.either(index(x, y), index(nx, ny));
      if (OPTIONS[i][0] == OPTIONS[j][1]) ts.either(index(x, y), ~index(nx, ny));
      if (OPTIONS[i][1] == OPTIONS[j][0]) ts.either(~index(x, y), index(nx, ny));
      if (OPTIONS[i][1] == OPTIONS[j][1]) ts.either(~index(x, y), ~index(nx, ny));
    }
  }

  if (ts.solve()) {
    rep(x, 0, n) {
      rep(y, 0, m) {
        int i = a[x][y] - 'A';
        cout << OPTIONS[i][ts.values[index(x, y)]];
      }
      cout << '\n';
    }

  } else {
    cout << "IMPOSSIBLE\n";
  }
}
