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

using ld = long double;
ld solve(const vector<vi> &adj, int u = 0, int p = -1) {
  int d = sz(adj[u]) - (u != 0);
  if (d == 0) return 0.0;

  ld ans = 0.0;
  for (auto v : adj[u]) {
    if (v == p) continue;
    ans += solve(adj, v, u);
  }
  return 1.0l + ans / d;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ld ans = solve(adj);
  cout << fixed << setprecision(8) << ans << '\n';
}
