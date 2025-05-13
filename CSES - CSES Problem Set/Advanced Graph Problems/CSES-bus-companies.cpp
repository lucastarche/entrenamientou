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

const ll INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vi cost(m);
  rep(i, 0, m) cin >> cost[i];

  vector<vii> adj(n + m);
  rep(i, 0, m) {
    int k;
    cin >> k;

    rep(j, 0, k) {
      int x;
      cin >> x, x--;
      adj[x].emplace_back(i + n, cost[i]);
      adj[i + n].emplace_back(x, 0);
    }
  }

  using T = pair<ll, int>;
  vb visit(n + m, false);
  vl dist(n + m, INF);
  priority_queue<T, vector<T>, greater<T>> pq;
  pq.emplace(dist[0] = 0, 0);

  while (not pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (visit[u]) continue;
    visit[u] = true;

    for (auto [v, w] : adj[u]) {
      if (dist[v] > d + w) pq.emplace(dist[v] = d + w, v);
    }
  }

  rep(i, 0, n) cout << dist[i] << " \n"[i + 1 == n];
}
