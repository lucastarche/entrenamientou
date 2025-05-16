#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;

vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &adj) {
  const int n = (int)(adj.size());

  vector<bool> seen(n, false);
  vector<ll> dist(n, INF);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

  pq.emplace(dist[0] = 0, 0);
  while (not pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (seen[u]) continue;
    seen[u] = true;

    for (const auto &[v, w] : adj[u]) {
      if (dist[v] > d + w) {
        pq.emplace(dist[v] = d + w, v);
      }
    }
  }

  return dist;
}

// Compute the shortest path from the capital to every other node
vector<ll> getDist(const vector<tuple<int, int, ll>> &routes, const vector<ll> &shortestTrainRoute) {
  const int n = (int)shortestTrainRoute.size();

  vector<vector<pair<int, ll>>> adj(n);
  for (const auto &[u, v, w] : routes) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  for (int v = 1; v < n; v++) {
    if (shortestTrainRoute[v] != -1) {
      adj[0].emplace_back(v, shortestTrainRoute[v]);
      adj[v].emplace_back(0, shortestTrainRoute[v]);
    }
  }

  return dijkstra(adj);
}

// Determine whether or not there is a single shortest path from the capital to each city
vector<int> getPathAmount(const vector<vector<int>> &adj) {
  const int n = (int)adj.size();
  vector<int> deg(n);

  for (int u = 0; u < n; u++) {
    for (auto v : adj[u]) deg[v]++;
  }

  stack<int> s;
  s.push(0);

  vector<int> pathAmount(n, 0);
  pathAmount[0] = 1;

  // Visit nodes in a toposort order, to run a Dynamic Programming algorithm
  while (not s.empty()) {
    int u = s.top();
    s.pop();

    for (auto v : adj[u]) {
      pathAmount[v] = min(2, pathAmount[u] + pathAmount[v]);
      deg[v]--;
      if (deg[v] == 0) s.push(v);
    }
  }

  return pathAmount;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m, k;
  cin >> n >> m >> k;

  vector<tuple<int, int, ll>> routes(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w, u--, v--;
    routes[i] = {u, v, w};
  }

  int ans = 0;
  vector<ll> shortestTrainRoute(n, -1);
  for (int i = 0; i < k; i++) {
    int v;
    ll w;
    cin >> v >> w, v--;

    // Keep only a single copy of the shortest train route
    if (shortestTrainRoute[v] == -1) {
      shortestTrainRoute[v] = w;
    } else {
      ans++;
      shortestTrainRoute[v] = min(shortestTrainRoute[v], w);
    }
  }

  const auto dist = getDist(routes, shortestTrainRoute);

  // Construct the shortest paths DAG
  vector<vector<int>> dag(n);
  for (const auto &[u, v, w] : routes) {
    if (dist[u] + w == dist[v]) dag[u].push_back(v);
    if (dist[v] + w == dist[u]) dag[v].push_back(u);
  }

  for (int v = 1; v < n; v++) {
    if (shortestTrainRoute[v] == -1) continue;

    // Discard train routes which are not a shortest path
    if (dist[v] == shortestTrainRoute[v]) {
      dag[0].push_back(v);
    } else {
      ans++;
      shortestTrainRoute[v] = -1;
    }
  }

  const auto pathAmount = getPathAmount(dag);

  // Discard train routes where there is an alternative shortest path
  for (int v = 1; v < n; v++) {
    if (shortestTrainRoute[v] == -1) continue;
    if (pathAmount[v] == 1) continue;
    ans++;
  }

  cout << ans << '\n';
}