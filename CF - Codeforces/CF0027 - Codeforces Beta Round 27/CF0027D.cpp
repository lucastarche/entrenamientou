/*
Pensarlo como grafo planar, hago 2-SAT para elegir quien va adentro/afuera.
Puedo zafar de codear 2-SAT porque cada componente es fuertemente conexa, solo hace falta un DSU, añado una arista cuando dos cuerdas se intersecan.
*/
#include <bits/stdc++.h>

using namespace std;

// Check if chords lhs and rhs intersect inside the polygon
bool inside(pair<int, int> range, int point) { return range.first < point && point < range.second; }
bool intersect(pair<int, int> lhs, pair<int, int> rhs) {
  if (lhs.first == rhs.first || lhs.first == rhs.second || lhs.second == rhs.first || lhs.second == rhs.second) {
    return false;
  }
  return inside(lhs, rhs.first) != inside(lhs, rhs.second);
}

// Disjoint-Set Union
struct DSU {
  vector<int> e;
  DSU(int n) : e(n, -1) {}

  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(e[a], e[b]);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> roads(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    // There was a bug here, the input does not guarantee u <= v
    roads[i] = minmax(u, v);
  }

  const auto inside = [](int x) { return 2 * x; };
  const auto outside = [](int x) { return 2 * x + 1; };
  DSU dsu(2 * m);

  // If two chords intersect, they must lie in opposite sides of the ring
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      if (intersect(roads[i], roads[j])) {
        dsu.join(inside(i), outside(j));
        dsu.join(outside(i), inside(j));
      }
    }
  }

  bool valid = true;
  string ans(m, 'o');
  for (int i = 0; i < m; i++) {
    // Ensure there are no contradictions
    valid &= dsu.find(inside(i)) != dsu.find(outside(i));

    // Assign i the choice with smaller component number
    if (dsu.find(inside(i)) < dsu.find(outside(i))) {
      ans[i] = 'i';
    }
  }

  if (not valid) ans = "Impossible";
  cout << ans << '\n';
}
