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
  vector<pii> st;
  UF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return sz(st); }
  void rollback(int t) {
    for (int i = time(); i-- > t;) e[st[i].first] = st[i].second;
    st.resize(t);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a]});
    st.push_back({b, e[b]});
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, q;
  cin >> n >> m >> q;

  vector<tuple<int, int, int>> edges(m);
  map<int, vi> edgesByWeight;
  rep(i, 0, m) {
    int u, v, w;
    cin >> u >> v >> w, u--, v--;
    edges[i] = {u, v, w};
    edgesByWeight[w].push_back(i);
  }

  map<int, vii> checksByWeight;
  rep(i, 0, q) {
    int k;
    cin >> k;
    rep(j, 0, k) {
      int x;
      cin >> x, x--;

      int w = get<2>(edges[x]);
      checksByWeight[w].emplace_back(i, x);
    }
  }

  UF uf(n);
  vb ans(q, true);

  for (const auto &[w, vec] : edgesByWeight) {
    int t = uf.time(), last = -1;
    for (auto [qi, e] : checksByWeight[w]) {
      if (qi != last) uf.rollback(t), last = qi;
      auto [u, v, _] = edges[e];
      ans[qi] = ans[qi] && uf.join(u, v);
    }
    uf.rollback(t);

    for (auto e : vec) {
      auto [u, v, _] = edges[e];
      uf.join(u, v);
    }
  }

  rep(i, 0, q) cout << (ans[i] ? "YES" : "NO") << '\n';
}
