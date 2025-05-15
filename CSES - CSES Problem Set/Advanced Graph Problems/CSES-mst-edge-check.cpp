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

  int n, m;
  cin >> n >> m;

  vii edges(m);
  map<int, vi> byWeight;
  rep(i, 0, m) {
    int u, v, w;
    cin >> u >> v >> w, u--, v--;
    edges[i] = {u, v};
    byWeight[w].push_back(i);
  }

  UF uf(n);
  vb ans(m);
  for (const auto &[_, vec] : byWeight) {
    for (auto e : vec) {
      auto [u, v] = edges[e];
      ans[e] = !uf.sameSet(u, v);
    }

    for (auto e : vec) uf.join(edges[e].first, edges[e].second);
  }

  rep(i, 0, m) cout << (ans[i] ? "YES" : "NO") << '\n';
}
