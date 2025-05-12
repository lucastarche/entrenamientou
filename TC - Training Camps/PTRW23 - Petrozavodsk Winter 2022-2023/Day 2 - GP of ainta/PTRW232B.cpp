#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

struct UF {
  vi e, edges;
  UF(int n) : e(n, -1), edges(n, 0) {}
  int cnt(int x) { return edges[find(x)]; }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  void join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) {
      edges[a]++;
      return;
    }
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a;
    edges[a] += edges[b] + 1;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;

  vii edges(m);
  for (auto &[u, v] : edges) cin >> u >> v, u--, v--;
  sort(all(edges));

  vb seen(n);
  vector<vi> adj(n);
  for (auto [u, v] : edges) {
    auto iter = lower_bound(all(edges), pii{v, u});
    if (iter != edges.end() && *iter == pii{v, u}) {
      adj[u].push_back(v);
      continue;
    }
    seen[v] = true;
  }

  stack<int> s;
  rep(u, 0, n) if (seen[u]) s.push(u);

  while (not s.empty()) {
    int u = s.top();
    s.pop();

    for (auto v : adj[u]) {
      if (seen[v]) continue;
      seen[v] = true;
      s.push(v);
    }
  }

  UF uf(n);
  for (auto [u, v] : edges) {
    if (seen[u] || seen[v]) continue;
    if (u < v) uf.join(u, v);
  }

  bool valid = true;
  rep(u, 0, n) valid &= (seen[u] || uf.cnt(u) >= uf.size(u));
  cout << (valid ? "YES" : "NO") << '\n';
}