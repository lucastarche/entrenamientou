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

void dfs(const vector<vi> &adj, vi &dist, int u = 0, int p = -1) {
  for (auto v : adj[u]) {
    if (v == p) continue;
    dist[v] = dist[u] + 1;
    dfs(adj, dist, v, u);
  }
}

int solve(const vector<vi> &adj, int u, int p) {
  set<int> children;
  for (auto v : adj[u]) {
    if (v == p) continue;
    children.insert(solve(adj, v, u));
  }

  if (children.empty()) return 1;
  if (children.count(-1) || sz(children) > 1) return -1;
  return *children.begin() + 1;
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

  vi dist(n);
  dfs(adj, dist);

  int x1 = max_element(all(dist)) - dist.begin();
  dist.assign(n, 0);
  dfs(adj, dist, x1);

  int x2 = max_element(all(dist)) - dist.begin(), diam = dist[x2];
  vi dist2(n);
  dfs(adj, dist2, x2);

  int center = -1;
  rep(u, 0, n) if (dist[u] + dist2[u] == diam && dist[u] == diam / 2) center = u;

  set<int> children;
  for (auto u : adj[center]) children.insert(solve(adj, u, center));

  if (children.count(-1) || sz(children) > 2) {
    cout << "-1\n";
  } else if (sz(children) == 1) {
    int len = *children.begin();
    while (len % 2 == 0) len /= 2;
    cout << len << '\n';
  } else {
    int len = *children.begin() + *children.rbegin();
    while (len % 2 == 0) len /= 2;
    cout << len << '\n';
  }
}
