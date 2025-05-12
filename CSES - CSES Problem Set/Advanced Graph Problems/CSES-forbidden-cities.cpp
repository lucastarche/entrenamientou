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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, q;
  cin >> n >> m >> q;

  vector<vi> adj(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  BCC bcc(adj);
  vector<vi> bct(n + sz(bcc.comps));
  rep(i, 0, sz(bcc.comps)) {
    for (auto u : bcc.comps[i]) {
      bct[u].push_back(n + i), bct[n + i].push_back(u);
    }
  }

  LCA lca(bct);
  while (q--) {
    int a, b, c;
    cin >> a >> b >> c, a--, b--, c--;

    if (lca.dist(a, b) == lca.dist(a, c) + lca.dist(b, c)) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
}
