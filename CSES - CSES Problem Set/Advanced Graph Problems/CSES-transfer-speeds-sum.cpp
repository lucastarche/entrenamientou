#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (a); --i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
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

  int n;
  cin >> n;

  vector<tuple<int, int, int>> edges(n - 1);
  rep(i, 0, n - 1) {
    int u, v, w;
    cin >> u >> v >> w, u--, v--;
    edges.emplace_back(w, u, v);
  }
  sort(rall(edges));

  UF uf(n);
  ll ans = 0;
  for (auto [w, u, v] : edges) {
    int lhs = uf.size(u), rhs = uf.size(v);
    ans += (ll)(w)*lhs * rhs;
    uf.join(u, v);
  }
  cout << ans << '\n';
}
