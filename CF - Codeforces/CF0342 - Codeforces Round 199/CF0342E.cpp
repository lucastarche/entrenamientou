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

const int INF = 1e9;

template <class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      rep(j, 0, sz(jmp[k])) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b);  // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  int T = 0;
  vi time, path, ret, depth;
  RMQ<int> rmq;

  LCA(vector<vi>& C) : time(sz(C)), depth(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
  void dfs(vector<vi>& C, int v, int par) {
    if (par != -1) depth[v] = depth[par] + 1;
    time[v] = T++;
    for (int y : C[v])
      if (y != par) {
        path.push_back(v), ret.push_back(time[v]);
        dfs(C, y, v);
      }
  }

  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  int dist(int a, int b) { return depth[a] + depth[b] - 2 * depth[lca(a, b)]; }
};

struct Centroid {
  int n;
  vb sn;
  vi par, siz;
  Centroid(vector<vi>& g) : n(sz(g)), sn(n), par(n), siz(n) { dfs(g); }
  void dfs(vector<vi>& g, int u = 0, int p = -1, int s = -1) {
    if (s < 0) s = calcsz(g, u, -1);
    for (int v : g[u])
      if (!sn[v] && siz[v] * 2 >= s) {
        siz[u] = 0;
        dfs(g, v, p, s);
        return;
      }
    sn[u] = true, par[u] = p;
    for (int v : g[u])
      if (!sn[v]) dfs(g, v, u);
  }
  int calcsz(vector<vi>& g, int u, int p) {
    siz[u] = 1;
    for (int v : g[u])
      if (v != p && !sn[v]) siz[u] += calcsz(g, v, u);
    return siz[u];
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  LCA lca(adj);
  Centroid cnt(adj);
  vi minVal(n, INF);

  const auto color = [&](int u) {
    int p = u;
    while (p != -1) {
      minVal[p] = min(minVal[p], lca.dist(u, p));
      p = cnt.par[p];
    }
  };

  const auto query = [&](int u) {
    int p = u, ans = INF;
    while (p != -1) {
      ans = min(ans, lca.dist(u, p) + minVal[p]);
      p = cnt.par[p];
    }
    return ans;
  };

  color(0);
  while (q--) {
    int type, u;
    cin >> type >> u, u--;

    if (type == 1) {
      color(u);
    } else {
      cout << query(u) << '\n';
    }
  }
}
