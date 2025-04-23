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

void solve(const vector<vi> &adj, const vi &target, vi &ans, bool &valid, int u = 0, int p = -1) {
  int delta = 0;
  for (auto v : adj[u]) {
    if (v == p) continue;
    solve(adj, target, ans, valid, v, u);

    if (ans[v] == -1) ans[v] = target[u];
    delta += (ans[v] == target[u] ? +1 : -1);
  }

  if (delta == 0 && p != -1) {
    if (ans[p] == -1) ans[p] = target[u];
    delta += (ans[p] == target[u] ? +1 : -1);
  }
  valid &= (delta >= 0);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<vi> adj(n);
    rep(i, 0, n - 1) {
      int u, v;
      cin >> u >> v, u--, v--;
      adj[u].push_back(v), adj[v].push_back(u);
    }

    string s;
    cin >> s;
    vi target(n);
    rep(i, 0, n) target[i] = (s[i] == 'B');

    bool valid = true;
    vi ans(n, -1);
    solve(adj, target, ans, valid);

    if (valid) {
      rep(i, 0, n) cout << (ans[i] == 1 ? 'B' : 'W');
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }
}
