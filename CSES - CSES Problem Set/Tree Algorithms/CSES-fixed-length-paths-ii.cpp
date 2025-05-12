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

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    pos = min(pos, sz(s));

    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

struct Centroid {
  int n, k1, k2;
  vb seen;
  vi par, siz;

  ll ans = 0;
  Centroid(const vector<vi> &g, int _k1, int _k2) : n(sz(g)), k1(_k1), k2(_k2), seen(n), par(n), siz(n) { dfs(g); }
  void dfs(const vector<vi> &g, int u = 0, int p = -1, int s = -1) {
    if (s < 0) s = calcsz(g, u, -1);
    for (int v : g[u])
      if (!seen[v] && siz[v] * 2 >= s) {
        siz[u] = 0;
        dfs(g, v, p, s);
        return;
      }

    process(g, u);

    seen[u] = true, par[u] = p;
    for (int v : g[u])
      if (!seen[v]) dfs(g, v, u);
  }

  int calcsz(const vector<vi> &g, int u, int p) {
    siz[u] = 1;
    for (int v : g[u])
      if (v != p && !seen[v]) siz[u] += calcsz(g, v, u);
    return siz[u];
  }

  void process(const vector<vi> &g, int root) {
    FT ft(siz[root] + 1);
    ft.update(0, +1);

    for (auto v : g[root]) {
      if (seen[v]) continue;

      vi depths;
      dfs2(g, depths, v, root, 1);
      for (auto d : depths) ans += ft.query(k2 - d + 1) - ft.query(k1 - d);
      for (auto d : depths) ft.update(d, +1);
    }
  }

  void dfs2(const vector<vi> &g, vi &depths, int u, int p, int d) {
    depths.push_back(d);
    for (auto v : g[u]) {
      if (v == p || seen[v]) continue;
      dfs2(g, depths, v, u, d + 1);
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k1, k2;
  cin >> n >> k1 >> k2;

  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  Centroid centroid(adj, k1, k2);
  cout << centroid.ans << '\n';
}
