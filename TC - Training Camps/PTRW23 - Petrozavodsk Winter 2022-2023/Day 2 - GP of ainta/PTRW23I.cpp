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

struct BCC {
  int timer = 0, n;
  vb artic;
  vi num, low, st;
  vector<vi> comps;

  BCC(const vector<vi>& adj) : n(sz(adj)), artic(n), num(n), low(n) { rep(i, 0, n) if (!num[i]) dfs(adj, i); }

  void dfs(const vector<vi>& adj, int u, int p = -1) {
    num[u] = low[u] = ++timer;
    st.push_back(u);

    for (auto v : adj[u]) {
      if (v == p) continue;
      if (num[v]) {  // Back edge
        low[u] = min(low[u], num[v]);
        continue;
      }

      dfs(adj, v, u);  // Tree edge
      low[u] = min(low[u], low[v]);
      if (low[v] >= num[u]) {
        artic[u] = (num[u] > 1 || num[v] > 2);
        comps.push_back({u});
        while (comps.back().back() != v) {
          comps.back().push_back(st.back());
          st.pop_back();
        }
      }
    }
  }
};

const int SIZE = 20;

void dfs(const vector<vi>& adj, vi& dp, vi& depth, vi& parent, int n, int u = 0, int p = -1) {
  if (u < n) dp[u]++;
  if (p != -1) depth[u] = depth[p] + 1, parent[u] = p;

  for (auto v : adj[u]) {
    if (v == p) continue;
    dfs(adj, dp, depth, parent, n, v, u);
    dp[u] += dp[v];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vi> adj(n);
    rep(i, 0, m) {
      int u, v;
      cin >> u >> v, u--, v--;
      adj[u].push_back(v), adj[v].push_back(u);
    }

    BCC bcc(adj);

    int k = sz(bcc.comps);
    vector<vi> bct(n + k);
    rep(i, 0, k) for (auto u : bcc.comps[i]) bct[i + n].push_back(u), bct[u].push_back(i + n);

    vi dp(n + k), depth(n + k);
    vector<vi> parent(SIZE, vi(n + k, 0));
    dfs(bct, dp, depth, parent[0], n);
    rep(i, 0, SIZE - 1) rep(u, 0, n + k) parent[i + 1][u] = parent[i][parent[i][u]];

    const auto up = [&](int u, int delta) {
      rep(b, 0, SIZE) if (delta & (1 << b)) u = parent[b][u];
      return u;
    };

    const auto lca = [&](int u, int v) {
      if (depth[u] < depth[v]) swap(u, v);
      u = up(u, depth[u] - depth[v]);
      if (u == v) return u;

      per(b, 0, SIZE) if (parent[b][u] != parent[b][v]) u = parent[b][u], v = parent[b][v];
      return parent[0][u];
    };

    int q;
    cin >> q;
    while (q--) {
      int a, b;
      cin >> a >> b, a--, b--;

      int c = lca(a, b);
      if (c == b) swap(a, b);

      int cantReach = 0;
      if (c == a) {
        int child = up(b, depth[b] - depth[a] - 1);
        cantReach = (n - dp[child] - 1) + (dp[b] - 1);
      } else {
        cantReach = (dp[a] - 1) + (dp[b] - 1);
      }
      cout << n - cantReach << '\n';
    }
  }
}
