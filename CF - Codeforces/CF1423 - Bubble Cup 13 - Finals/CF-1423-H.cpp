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

struct RollbackUF {
  vi e;
  vector<pii> st;
  RollbackUF(int n) : e(n, -1) {}
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

struct DynCon {
  int N;
  vi ans;
  vector<vii> edges;
  vector<vii> queries;

  DynCon(int _N) : N(_N), edges(2 * N), queries(2 * N) {}

  void addEdge(int l, int r, pii e, int k = 1, int a = 0, int b = -1) {
    if (k == 1) b = N;
    if (r <= a || b <= l) return;
    if (l <= a && b <= r) return edges[k].push_back(e);
    int mid = (a + b) / 2;
    addEdge(l, r, e, 2 * k, a, mid);
    addEdge(l, r, e, 2 * k + 1, mid, b);
  }

  void addQuery(int t, int u, int id) { queries[t + N].emplace_back(u, id); }

  void solve(RollbackUF &uf, int k = 1) {
    int t = uf.time();
    for (auto [u, v] : edges[k]) uf.join(u, v);
    for (auto [u, id] : queries[k]) ans[id] = uf.size(u);

    if (k < N) {
      solve(uf, 2 * k);
      solve(uf, 2 * k + 1);
    }
    uf.rollback(t);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q, len;
  cin >> n >> q >> len;

  int T = 0, Q = 0;
  vector<vii> edgesByTime(1);
  vector<vii> queriesByTime(1);
  rep(i, 0, q) {
    int t;
    cin >> t;

    if (t == 1) {
      int u, v;
      cin >> u >> v, u--, v--;
      edgesByTime[T].emplace_back(u, v);
    } else if (t == 2) {
      int u;
      cin >> u, u--;
      queriesByTime[T].emplace_back(u, Q++);
    } else {
      T++, edgesByTime.emplace_back(), queriesByTime.emplace_back();
    }
  }
  T++;

  int N = 1;
  while (N < T) N <<= 1;

  DynCon dc(N);
  dc.ans.resize(Q);
  rep(t, 0, T) {
    for (auto [u, id] : queriesByTime[t]) dc.addQuery(t, u, id);
    for (auto e : edgesByTime[t]) dc.addEdge(t, t + len, e);
  }

  RollbackUF uf(n);
  dc.solve(uf);
  rep(i, 0, Q) cout << dc.ans[i] << "\n";
}
