#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;

// We will never need more than INF leeway, we can discard the remaining amount
void addLeeway(ll &x, ll y) { x = min(x + y, INF); }

vector<ll> solve(const vector<vector<int>> &adj, const vector<ll> &a, ll &ans, int u) {
  const int n = (int)(adj.size());

  ll childSum = 0;
  vector<ll> leewayByDepth(n);
  for (auto v : adj[u]) {
    const auto child = solve(adj, a, ans, v);
    childSum += a[v];

    // Shift depth by one, as we move from child to parent
    for (int d = 0; d < n - 1; d++) {
      addLeeway(leewayByDepth[d + 1], child[d]);
    }
  }

  if (adj[u].empty()) {
    // Current child is a leaf, there is no constraint
    leewayByDepth[0] = INF;
  } else if (a[u] <= childSum) {
    // The constraint already holds, we don't need to do anything
    leewayByDepth[0] = childSum - a[u];
  } else {
    // Greedily perform operation in increasing depth
    ll missing = a[u] - childSum;
    for (int d = 1; d < n; d++) {
      ll delta = min(missing, leewayByDepth[d]);
      leewayByDepth[d] -= delta;
      missing -= delta;
      ans += delta * (ll)d;
    }
  }

  return leewayByDepth;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for (int u = 1; u < n; u++) {
      int p;
      cin >> p, p--;
      adj[p].push_back(u);
    }

    ll ans = 0;
    solve(adj, a, ans, 0);
    cout << ans << '\n';
  }
}