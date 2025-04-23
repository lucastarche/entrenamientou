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
  vector<vi> adj(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  UF uf(n);
  int ans = 0;
  vb remove(n, false);
  rep(u, 0, n) {
    if (remove[u]) remove[u] = false, ans--;
    for (auto v : adj[u]) {
      if (u > v) {
        uf.join(u, v);
      } else if (not remove[v]) {
        remove[v] = true;
        ans++;
      }
    }

    cout << (uf.size(0) == u + 1 ? ans : -1) << '\n';
  }
}
