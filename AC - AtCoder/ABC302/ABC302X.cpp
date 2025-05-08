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

struct RollbackUF {
  int ans = 0;
  vi e, edges;
  vector<pair<int *, int>> st;
  RollbackUF(int n) : e(n, -1), edges(n, 0) {}

  void store(int &x) { st.emplace_back(&x, x); }

  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return sz(st); }

  void rollback(int t) {
    for (int i = time(); i-- > t;) *st[i].first = st[i].second;
    st.resize(t);
  }

  void join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) {
      store(edges[a]);
      edges[a]++;
      if (edges[a] == size(a)) {
        store(ans);
        ans++;
      }
      return;
    }

    if (e[a] > e[b]) swap(a, b);
    store(e[a]), store(e[b]);
    store(edges[a]), store(ans);

    ans -= size(a) - (edges[a] == size(a) - 1);
    ans -= size(b) - (edges[b] == size(b) - 1);

    edges[a] += edges[b] + 1;
    e[a] += e[b];
    e[b] = a;

    ans += size(a) - (edges[a] == size(a) - 1);
  }
};

void dfs(const vector<vi> &adj, const vii &balls, RollbackUF &uf, vi &ans, int u = 0, int p = -1) {
  int t = uf.time();
  uf.join(balls[u].first, balls[u].second);
  ans[u] = uf.ans;

  for (auto v : adj[u]) {
    if (v == p) continue;
    dfs(adj, balls, uf, ans, v, u);
  }

  uf.rollback(t);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vii balls(n);
  vector<vi> adj(n);
  for (auto &[x, y] : balls) cin >> x >> y, x--, y--;
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vi ans(n);
  RollbackUF uf(n);
  dfs(adj, balls, uf, ans);
  rep(i, 1, n) cout << ans[i] << " \n"[i + 1 == n];
}
