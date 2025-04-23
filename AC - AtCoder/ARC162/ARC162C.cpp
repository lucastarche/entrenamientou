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

pair<vb, int> solve(const vector<vi> &adj, const vi &a, bool &ans, int u, int k) {
  int moves = (a[u] == -1);
  vb seen(k + 1, false);
  if (a[u] != -1 && a[u] <= k) seen[a[u]] = true;

  for (auto v : adj[u]) {
    auto [cSeen, cMoves] = solve(adj, a, ans, v, k);
    rep(i, 0, k + 1) seen[i] = seen[i] || cSeen[i];
    moves += cMoves;
  }

  int missing = 0;
  rep(i, 0, k) missing += not seen[i];
  if (not seen[k]) ans |= (missing <= moves && moves <= 1);

  return {seen, moves};
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<vi> adj(n);
    rep(i, 1, n) {
      int p;
      cin >> p, p--;
      adj[p].push_back(i);
    }

    vi a(n);
    rep(i, 0, n) cin >> a[i];

    bool ans = false;
    solve(adj, a, ans, 0, k);
    cout << (ans ? "Alice" : "Bob") << '\n';
  }
}
