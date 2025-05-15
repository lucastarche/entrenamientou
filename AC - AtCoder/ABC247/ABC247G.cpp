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

#include <bits/extc++.h>

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
  struct edge {
    int from, to, rev;
    ll cap, cost, flow;
  };
  int N;
  vector<vector<edge>> ed;
  vi seen;
  vector<ll> dist, pi;
  vector<edge*> par;

  MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

  void addEdge(int from, int to, ll cap, ll cost) {
    if (from == to) return;
    ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
    ed[to].push_back(edge{to, from, sz(ed[from]) - 1, 0, -cost, 0});
  }

  void path(int s) {
    fill(all(seen), 0);
    fill(all(dist), INF);
    dist[s] = 0;
    ll di;

    __gnu_pbds::priority_queue<pair<ll, int>> q;
    vector<decltype(q)::point_iterator> its(N);
    q.push({0, s});

    while (!q.empty()) {
      s = q.top().second;
      q.pop();
      seen[s] = 1;
      di = dist[s] + pi[s];
      for (edge& e : ed[s])
        if (!seen[e.to]) {
          ll val = di - pi[e.to] + e.cost;
          if (e.cap - e.flow > 0 && val < dist[e.to]) {
            dist[e.to] = val;
            par[e.to] = &e;
            if (its[e.to] == q.end())
              its[e.to] = q.push({-dist[e.to], e.to});
            else
              q.modify(its[e.to], {-dist[e.to], e.to});
          }
        }
    }
    rep(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
  }

  vl maxflow(int s, int t) {
    vl ans;
    while (path(s), seen[t]) {
      ll fl = 1;
      for (edge* x = par[t]; x; x = par[x->from]) fl = min(fl, x->cap - x->flow);

      for (edge* x = par[t]; x; x = par[x->from]) {
        x->flow += fl;
        ed[x->to][x->rev].flow -= fl;
      }

      ll cost = 0;
      rep(i, 0, N) for (edge& e : ed[i]) cost += e.cost * e.flow;
      ans.push_back(-cost / 2);
    }

    return ans;
  }

  // If some costs can be negative, call this before maxflow:
  void setpi(int s) {  // (otherwise, leave this out)
    fill(all(pi), INF);
    pi[s] = 0;
    int it = N, ch = 1;
    ll v;
    while (ch-- && it--) rep(i, 0, N) if (pi[i] != INF) for (edge& e : ed[i]) if (e.cap) if ((v = pi[i] + e.cost) < pi[e.to]) pi[e.to] = v, ch = 1;
    assert(it >= 0);  // negative cost cycle
  }
};

const int MAX_X = 150;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  MCMF mf(2 * MAX_X + 2);
  const auto left = [&](int x) { return x; };
  const auto right = [&](int x) { return x + MAX_X; };
  int s = 2 * MAX_X, t = s + 1;

  rep(i, 0, MAX_X) mf.addEdge(s, left(i), 1, 0), mf.addEdge(right(i), t, 1, 0);

  rep(i, 0, n) {
    int a, b, c;
    cin >> a >> b >> c, a--, b--;
    mf.addEdge(left(a), right(b), 1, -c);
  }

  mf.setpi(s);

  auto ans = mf.maxflow(s, t);
  cout << sz(ans) << '\n';
  for (auto x : ans) cout << x << '\n';
}
