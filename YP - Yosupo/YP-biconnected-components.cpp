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
    if (sz(adj[u]) == 0) return comps.push_back({u});

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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<vi> adj(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  BCC bcc(adj);
  cout << sz(bcc.comps) << '\n';
  for (auto v : bcc.comps) {
    cout << sz(v) << ' ';
    for (auto x : v) cout << x << ' ';
    cout << '\n';
  }
}
