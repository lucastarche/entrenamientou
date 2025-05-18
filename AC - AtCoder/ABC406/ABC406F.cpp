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

void dfs(const vector<vi> &adj, vi &time, vi &size, vi &depth, int &timer, int u = 0, int p = -1) {
  time[u] = timer++, size[u] = 1;
  for (auto v : adj[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(adj, time, size, depth, timer, v, u);
    size[u] += size[v];
  }
}

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vii edges(n - 1);
  vector<vi> adj(n);
  for (auto &[u, v] : edges) {
    cin >> u >> v, u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int timer = 0;
  vi time(n), size(n), depth(n);
  dfs(adj, time, size, depth, timer);

  ll total = n;
  FT ft(n);
  rep(i, 0, n) ft.update(i, +1);

  int q;
  cin >> q;
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int x, k;
      cin >> x >> k, x--;
      total += k;
      ft.update(time[x], +k);
    } else {
      int e;
      cin >> e, e--;
      auto [u, v] = edges[e];
      if (depth[u] < depth[v]) swap(u, v);

      ll lhs = ft.query(time[u] + size[u]) - ft.query(time[u]);
      ll rhs = total - lhs;
      cout << abs(lhs - rhs) << '\n';
    }
  }
}
