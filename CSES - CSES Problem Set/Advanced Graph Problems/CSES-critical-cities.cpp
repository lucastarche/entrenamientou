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

vector<int> DomTree(vector<vector<int>>& graph, int src) {
  int n = graph.size();
  vector<vector<int>> tree(n), trans(n), buck(n);
  vector<int> semi(n), par(n), dom(n), label(n), atob(n, -1), btoa(n, -1), link(n, -1);

  function<int(int, int)> find = [&](int u, int d) {
    if (link[u] == -1) return d ? -1 : u;
    int v = find(link[u], d + 1);
    if (v < 0) return u;
    if (semi[label[link[u]]] < semi[label[u]]) label[u] = label[link[u]];
    link[u] = v;
    return d ? v : label[u];
  };
  int t = 0;
  function<void(int)> dfs = [&](int u) {
    atob[u] = t;
    btoa[t] = u;
    label[t] = semi[t] = t;
    t++;
    for (auto v : graph[u]) {
      if (atob[v] == -1) dfs(v), par[atob[v]] = atob[u];
      trans[atob[v]].push_back(atob[u]);
    }
  };
  dfs(src);
  for (int u = t - 1; u >= 0; --u) {
    for (auto v : trans[u]) semi[u] = min(semi[u], semi[find(v, 0)]);
    if (u) buck[semi[u]].push_back(u);
    for (auto w : buck[u]) {
      int v = find(w, 0);
      dom[w] = semi[v] == semi[w] ? semi[w] : v;
    }
    if (u) link[u] = par[u];
  }
  vector<int> ret(n, -1);
  for (int u = 1; u < t; ++u) {
    if (dom[u] != semi[u]) dom[u] = dom[dom[u]];
    ret[btoa[u]] = btoa[dom[u]];
  }
  return ret;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<vi> adj(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v);
  }

  auto dom = DomTree(adj, 0);

  vi ans = {n - 1};
  while (dom[ans.back()] != -1) ans.push_back(dom[ans.back()]);

  cout << sz(ans) << '\n';
  sort(all(ans));
  rep(i, 0, sz(ans)) cout << ans[i] + 1 << " \n"[i + 1 == sz(ans)];
}
