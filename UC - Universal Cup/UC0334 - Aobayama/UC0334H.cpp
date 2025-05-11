#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)a; i < (int)b; ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

struct TwoSat {
  int N;
  vector<vi> gr;
  vi values;

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

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;

  TwoSat ts(n * n);
  rep(_, 0, m) {
    int t, i, j, d;
    cin >> t >> i >> j >> d, i--, j--;

    int me = i * n + j;
    int other = me + 1;
    if (t == 0) other += n - 1;

    if (d == 1) {
      ts.either(me, other);
      ts.either(~me, ~other);
    } else {
      ts.either(me, ~other);
      ts.either(~me, other);
    }
  }

  bool can = ts.solve();
  if (!can) {
    cout << "No\n";
    return 0;
  }

  cout << "Yes\n";
  rep(i, 0, n) rep(j, 0, n) {
    if ((i + 1) % 2 == (j + 1) % 2) {
      cout << (ts.values[i * n + j] ? 3 : 0);
    } else {
      cout << (ts.values[i * n + j] ? 1 : 2);
    }

    cout << " \n"[j == n - 1];
  }
}