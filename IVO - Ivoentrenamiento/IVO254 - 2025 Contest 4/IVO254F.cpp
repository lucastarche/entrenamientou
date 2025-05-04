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

void dfs(const vector<vi> &adj, vi &dist, int u, int p = -1) {
  if (p != -1) dist[u] = dist[p] + 1;
  for (auto v : adj[u]) {
    if (v == p) continue;
    dfs(adj, dist, v, u);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vi d0(n, 0);
  dfs(adj, d0, 0);

  int x1 = max_element(all(d0)) - d0.begin();
  vi d1(n, 0);
  dfs(adj, d1, x1);

  int x2 = max_element(all(d1)) - d1.begin();
  vi d2(n, 0);
  dfs(adj, d2, x2);

  vi inside, outside;
  rep(i, 0, n) {
    if (d1[i] + d2[i] == d1[x2]) {
      inside.push_back(i);
    } else {
      outside.push_back(i);
    }
  }

  sort(all(inside), [&](int i, int j) { return d1[i] < d1[j]; });
  sort(all(outside), [&](int i, int j) { return max(d1[i], d2[i]) < max(d1[j], d2[j]); });

  ll ans = 0;
  vector<tuple<int, int, int>> ops;
  while (not outside.empty()) {
    int i = outside.back();
    outside.pop_back();

    ops.emplace_back((d1[i] >= d2[i] ? x1 : x2), i, i);
    ans += max(d1[i], d2[i]);
  }

  while (sz(inside) > 1) {
    int i = inside.back();
    inside.pop_back();

    ops.emplace_back(x1, i, i);
    ans += d1[i];
  }

  cout << ans << '\n';
  for (auto [x, y, z] : ops) cout << x + 1 << ' ' << y + 1 << ' ' << z + 1 << '\n';
}
