#include <bits/stdc++.h>

using namespace std;

// Get a bicoloring of the tree
void dfs(const vector<vector<int>> &adj, vector<bool> &color, int u, int p = -1) {
  if (p != -1) color[u] = not color[p];
  for (auto v : adj[u]) {
    if (v == p) continue;
    dfs(adj, color, v, u);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v, u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<bool> color(n);
    dfs(adj, color, 0);

    // Assign to each node its degree, where we multiply white nodes by -1
    for (int i = 0; i < n; i++) {
      cout << (color[i] ? 1 : -1) * (int)(adj[i].size()) << ' ';
    }
    cout << '\n';
  }
}