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

const int ITERS = 20;

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
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
  for (auto &[u, v] : edges) cin >> u >> v, u--, v--;

  int q;
  cin >> q;
  vi x(q), y(q), z(q);
  rep(i, 0, q) cin >> x[i] >> y[i] >> z[i], x[i]--, y[i]--;

  vi lo(q, 0), hi(q, m);
  rep(_, 0, ITERS) {
    vector<vi> byMid(m);
    rep(i, 0, q) byMid[(lo[i] + hi[i]) / 2].push_back(i);

    UF uf(n);
    rep(i, 0, m) {
      uf.join(edges[i].first, edges[i].second);
      for (auto qi : byMid[i]) {
        int curr = uf.size(x[qi]);
        if (uf.find(x[qi]) != uf.find(y[qi])) curr += uf.size(y[qi]);
        if (curr >= z[qi]) {
          hi[qi] = i;
        } else {
          lo[qi] = i;
        }
      }
    }
  }

  rep(i, 0, q) cout << hi[i] + 1 << '\n';
}
