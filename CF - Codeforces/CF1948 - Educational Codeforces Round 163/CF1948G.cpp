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

const int INF = 1e9;

bool bitSet(int mask, int b) { return (mask >> b) & 1; }

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, c;
  cin >> n >> c;

  vector<vi> cost(n, vi(n));
  rep(i, 0, n) rep(j, 0, n) cin >> cost[i][j];

  vector<tuple<int, int, int>> edges;
  rep(i, 0, n) rep(j, i + 1, n) if (cost[i][j] > 0) edges.emplace_back(cost[i][j], i, j);
  sort(all(edges));

  int best = INF;
  rep(mask, 0, 1 << n) {
    int curr = __builtin_popcount(mask) * c;
    UF uf(n);
    for (const auto &[w, u, v] : edges) {
      if (bitSet(mask, u) == false && bitSet(mask, v) == false) continue;
      if (uf.join(u, v)) curr += w;
    }

    if (uf.size(0) == n) best = min(best, curr);
  }
  cout << best << '\n';
}
