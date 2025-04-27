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

void dfs(const vector<vii> &adj, vi &depth, vi &parent, vl &dist, int u = 0, int p = -1) {
  if (p >= 0) depth[u] = depth[p] + 1;
  for (auto [v, w] : adj[u]) {
    if (v == p) continue;
    parent[v] = u, dist[v] = w;
    dfs(adj, depth, parent, dist, v, u);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, q, c;
    cin >> n >> q >> c;

    vector<vii> adj(n);
    rep(i, 0, n - 1) {
      int u, v, w;
      cin >> u >> v >> w, u--, v--;
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
    }

    vi depth(n);
    vector<vi> parent(SIZE, vi(n, 0));
    vector<vl> dist(SIZE, vl(n, 0));
    dfs(adj, depth, parent[0], dist[0]);

    rep(i, 0, SIZE - 1) rep(u, 0, n) {
      parent[i + 1][u] = parent[i][parent[i][u]];
      dist[i + 1][u] = dist[i][u] + dist[i][parent[i][u]];
    }

    vector<vi> next(SIZE, vi(n, 0));
    rep(u, 0, n) {
      int curr = u;
      ll sum = 0;
      per(i, 0, SIZE) {
        if (sum + dist[i][curr] <= c) {
          sum += dist[i][curr];
          curr = parent[i][curr];
        }
      }
      next[0][u] = curr;
    }

    rep(i, 0, SIZE - 1) rep(u, 0, n) next[i + 1][u] = next[i][next[i][u]];

    const auto getLCA = [&](int u, int v) {
      if (depth[u] < depth[v]) swap(u, v);
      int delta = depth[u] - depth[v];
      rep(i, 0, SIZE) if ((delta >> i) & 1) u = parent[i][u];

      if (u == v) return u;
      per(i, 0, SIZE) if (parent[i][u] != parent[i][v]) u = parent[i][u], v = parent[i][v];
      return parent[0][u];
    };

    const auto up = [&](int u, int lca) -> pair<int, ll> {
      int ans = 0;
      ll sumDist = 0;

      per(i, 0, SIZE) {
        if (depth[next[i][u]] > depth[lca]) {
          ans += 1 << i;
          u = next[i][u];
        }
      }

      rep(i, 0, SIZE) {
        if (((depth[u] - depth[lca]) >> i) & 1) {
          sumDist += dist[i][u];
          u = parent[i][u];
        }
      }

      return {ans, sumDist};
    };

    while (q--) {
      int u, v;
      cin >> u >> v, u--, v--;

      int lca = getLCA(u, v);
      auto [ansU, distU] = up(u, lca);
      auto [ansV, distV] = up(v, lca);

      int ans = ansU + ansV + (distU + distV > c);
      cout << ans << '\n';
    }
  }
}
