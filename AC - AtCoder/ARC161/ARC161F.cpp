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
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n, d;
    cin >> n >> d;

    vi deg(n);
    vector<vi> adj(n);
    rep(i, 0, n * d) {
      int u, v;
      cin >> u >> v, u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
      deg[u]++, deg[v]++;
    }

    int edges = n * d, nodes = n;
    priority_queue<pii, vii, greater<pii>> pq;
    rep(u, 0, n) pq.emplace(deg[u], u);

    vb removed(n, false);
    const auto remove = [&](int u) {
      if (removed[u]) return;
      removed[u] = true;
      nodes--;

      for (auto v : adj[u]) {
        if (not removed[v]) pq.emplace(--deg[v], v), edges--;
      }
    };

    bool ans = false;
    while (not pq.empty()) {
      remove(pq.top().second);
      pq.pop();

      if (nodes > 0 && nodes * d <= edges) {
        ans = true;
        break;
      }
    }

    cout << (ans ? "No" : "Yes") << '\n';
  }
}
