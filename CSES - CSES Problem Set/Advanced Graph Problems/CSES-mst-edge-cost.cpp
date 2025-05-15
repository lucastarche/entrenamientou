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

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

const int SIZE = 20;

void dfs(const vector<vii> &adj, vii &parent, vi &depth, int u = 0, int p = -1) {
  for (auto [v, w] : adj[u]) {
    if (v == p) continue;
    parent[v] = {u, w};
    depth[v] = depth[u] + 1;
    dfs(adj, parent, depth, v, u);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int>> edges(m);
  rep(i, 0, m) {
    int u, v, w;
    cin >> u >> v >> w, u--, v--;
    edges[i] = {u, v, w};
  }

  vi p(m);
  iota(all(p), 0);
  sort(all(p), [&](int i, int j) { return get<2>(edges[i]) < get<2>(edges[j]); });

  ll ans = 0;
  UF uf(n);
  vector<vii> adj(n);
  for (auto i : p) {
    auto [u, v, w] = edges[i];
    if (uf.join(u, v)) {
      adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
      ans += w;
    }
  }

  vi depth(n);
  vector<vii> jump(SIZE, vii(n));
  dfs(adj, jump[0], depth);
  rep(step, 0, SIZE - 1) rep(i, 0, n) {
    int p = jump[step][i].first;
    jump[step + 1][i].first = jump[step][p].first;
    jump[step + 1][i].second = max(jump[step][i].second, jump[step][p].second);
  }

  const auto query = [&](int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int delta = depth[u] - depth[v], ans = 0;
    rep(b, 0, SIZE) if (delta & (1 << b)) {
      ans = max(ans, jump[b][u].second);
      u = jump[b][u].first;
    }
    if (u == v) return ans;

    per(b, 0, SIZE) {
      if (jump[b][u].first == jump[b][v].first) continue;
      ans = max({ans, jump[b][u].second, jump[b][v].second});
      u = jump[b][u].first, v = jump[b][v].first;
    }

    return max({ans, jump[0][u].second, jump[0][v].second});
  };

  rep(i, 0, m) {
    auto [u, v, w] = edges[i];
    cout << ans + w - query(u, v) << '\n';
  }
}
