#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;

const ll INF = 1e10;

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

struct Edge {
  int u, v;
  ll w;

  Edge(int x, int y, ll z) : u(x), v(y), w(z) {}
  bool operator<(const Edge &o) const { return tie(w, u, v) < tie(o.w, o.u, o.v); }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, m, k;
  cin >> n >> m >> k;

  vector<Edge> normal, special;

  rep(i, 0, m) {
    int u, v;
    ll w;
    cin >> u >> v >> w, u--, v--;
    if (u > v) swap(u, v);
    (u == 0 ? special : normal).emplace_back(u, v, w);
  }

  sort(all(normal)), sort(all(special));

  const auto check = [&](ll lambda) -> pair<ll, int> {
    int cnt = 0;
    ll cost = 0;
    UF uf(n);

    for (int i = 0, j = 0; i < sz(normal) || j < sz(special);) {
      if (j == sz(special)) {
        cost += uf.join(normal[i].u, normal[i].v) * normal[i].w;
        i++;
        continue;
      }

      if (i == sz(normal) or (special[j].w + lambda < normal[i].w)) {
        if (uf.join(special[j].u, special[j].v)) {
          cost += special[j].w + lambda;
          cnt++;
        }
        j++;
        continue;
      }

      cost += uf.join(normal[i].u, normal[i].v) * normal[i].w;
      i++;
    }

    return {cost, cnt};
  };

  ll lo = -INF, hi = INF;
  while (hi - lo > 1) {
    ll mid = (lo + hi) / 2;
    if (check(mid).second >= k) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  auto [ans, cnt] = check(hi);
  ans -= hi * k;

  if (cnt > k) ans = -1;
  cout << ans << '\n';
}