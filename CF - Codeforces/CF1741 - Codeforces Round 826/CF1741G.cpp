#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

// Compute the distance from source to every other node
vector<int> BFS(const vector<vector<int>> &adj, int source) {
  const int n = (int)(adj.size());
  vector<int> dist(n, INF);
  queue<int> q;

  q.push(source);
  dist[source] = 0;
  while (not q.empty()) {
    int u = q.front();
    q.pop();

    for (auto v : adj[u]) {
      if (dist[v] > dist[u] + 1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }

  return dist;
}

int solve(const vector<vector<int>> &adj, const vector<int> &withCar, const vector<int> &withoutCar) {
  const int k = (int)(withoutCar.size());

  vector<int> distSource = BFS(adj, 0);
  vector<vector<int>> distWithout(k);
  for (int i = 0; i < k; i++) distWithout[i] = BFS(adj, withoutCar[i]);

  // Check if someone with a car going to node u can take friends in mask along the way
  const auto checkMask = [&](int u, int mask) -> bool {
    vector<int> perm;
    for (int b = 0; b < k; b++) {
      if ((mask >> b) & 1) perm.push_back(b);
    }

    // Try to take the friends in each possible order
    const int m = (int)(perm.size());
    const int target = distSource[u];
    do {
      int curr = distSource[withoutCar[perm[0]]] + distWithout[perm.back()][u];
      for (int i = 0; i + 1 < m; i++) {
        curr += distWithout[perm[i]][withoutCar[perm[i + 1]]];
      }

      if (curr == target) return true;
    } while (next_permutation(perm.begin(), perm.end()));

    // There was no valid permutation, we cannot take our friends
    return false;
  };

  // In each step, try to extend the subset by considering every subset of friends we could add
  vector<bool> can(1 << k, false);
  can[0] = true;
  for (auto u : withCar) {
    vector<bool> next = can;

    for (int mask = 1; mask < (1 << k); mask++) {
      if (not checkMask(u, mask)) continue;

      for (int prev = 0; prev < (1 << k); prev++) {
        if (can[prev]) next[prev | mask] = true;
      }
    }

    swap(next, can);
  }

  // If we can take some subset of friends by car, the complement is those who have to walk
  int best = k;
  for (int mask = 0; mask < (1 << k); mask++) {
    if (can[mask]) best = min(best, k - __builtin_popcount(mask));
  }
  return best;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v, u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    int f;
    cin >> f;

    vector<int> friends(f);
    for (int i = 0; i < f; i++) cin >> friends[i], friends[i]--;

    vector<bool> hasCar(f, true);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
      int x;
      cin >> x, x--;
      hasCar[x] = false;
    }

    vector<int> withCar, withoutCar;
    for (int i = 0; i < f; i++) {
      (hasCar[i] ? withCar : withoutCar).push_back(friends[i]);
    }

    cout << solve(adj, withCar, withoutCar) << '\n';
  }
}