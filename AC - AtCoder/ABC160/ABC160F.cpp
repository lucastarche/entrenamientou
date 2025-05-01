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

const ll MOD = 1e9 + 7;
vl fact, facti;

ll modpow(ll x, ll y) {
  ll ans = 1;
  while (y > 0) {
    if (y % 2 == 1) ans = (ans * x) % MOD;
    x = (x * x) % MOD, y /= 2;
  }
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }
ll choose(int n, int k) { return fact[n] * (facti[k] * facti[n - k] % MOD) % MOD; }

void dfsDown(const vector<vi> &adj, vi &size, vl &down, int u = 0, int p = -1) {
  for (auto v : adj[u]) {
    if (v == p) continue;
    dfsDown(adj, size, down, v, u);
    size[u] += size[v];
    down[u] = down[u] * (down[v] * choose(size[u], size[v]) % MOD) % MOD;
  }

  size[u]++;
}

void dfsUp(const vector<vi> &adj, const vi &size, const vl &down, vl &ans, int u = 0, int p = -1, ll waysUp = 1) {
  const int n = sz(adj), sizeUp = n - size[u];
  ans[u] = down[u] * (waysUp * choose(n - 1, sizeUp) % MOD) % MOD;

  for (auto v : adj[u]) {
    if (v == p) continue;
    ll nextUp = ans[u] * modinv(down[v] * choose(n - 1, size[v]) % MOD) % MOD;
    dfsUp(adj, size, down, ans, v, u, nextUp);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  fact.resize(n + 1, 1), facti.resize(n + 1, 1);
  rep(i, 0, n) fact[i + 1] = (fact[i] * (i + 1)) % MOD;
  facti.back() = modinv(fact.back());
  per(i, 0, n) facti[i] = (facti[i + 1] * (i + 1)) % MOD;

  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vi size(n, 0);
  vl down(n, 1);
  dfsDown(adj, size, down);

  vl ans(n);
  dfsUp(adj, size, down, ans);
  rep(i, 0, n) cout << ans[i] << '\n';
}
