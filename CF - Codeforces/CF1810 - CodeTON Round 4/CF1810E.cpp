#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

// Merge lhs and rhs into a single set
// Takes O(k log (|lhs| + |rhs|)), where k = min(|lhs|, |rhs|)
void merge(set<pii> &lhs, set<pii> &rhs) {
  if (lhs.size() < rhs.size()) swap(lhs, rhs);
  for (auto p : rhs) lhs.insert(p);
  rhs.clear();
}

// Disjoint-Set Union / Union-Find
struct UF {
  vector<int> e;

  // Keep track of (danger, monster) pairs adjacent to each node
  vector<set<pii>> adjacent;

  UF(int n) : e(n, -1), adjacent(n) {}

  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }

  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);

    // Small-to-Large merging, this will take O(m log^2 m) throughout the whole algorithm
    merge(adjacent[a], adjacent[b]);

    e[a] += e[b];
    e[b] = a;
    return true;
  }

  // Helper functions, to work with the monsters adjacent to u's component easily
  bool hasAdjacent(int u) { return not adjacent[find(u)].empty(); }
  pii nextAdjacent(int u) { return *adjacent[find(u)].begin(); }
  void popAdjacent(int u) {
    const int comp = find(u);
    adjacent[comp].erase(adjacent[comp].begin());
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    UF uf(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v, u--, v--;
      uf.adjacent[u].emplace(a[v], v);
      uf.adjacent[v].emplace(a[u], u);
    }

    for (int u = 0; u < n; u++) {
      if (a[u] != 0) continue;        // We can only start from zero-danger monsters
      if (uf.size(u) != 1) continue;  // We have already seen this node, skip

      // Keep expanding the component while it is possible to do so
      while (uf.hasAdjacent(u)) {
        auto [w, v] = uf.nextAdjacent(u);
        if (uf.size(u) < w) break;
        uf.popAdjacent(u);
        uf.join(u, v);
      }
    }

    cout << (uf.size(0) == n ? "YES" : "NO") << '\n';
  }
}