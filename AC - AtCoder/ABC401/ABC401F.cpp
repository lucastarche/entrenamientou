#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rall(x) rbegin(x), rend(x)

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);  // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
        auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];   /// exclude-line
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}
vd conv(const vd& a, const vd& b) {
  if (a.empty() || b.empty()) return {};
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
  vector<C> in(n), out(n);
  copy(all(a), begin(in));
  rep(i, 0, sz(b)) in[i].imag(b[i]);
  fft(in);
  for (C& x : in) x *= x;
  rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
  return res;
}

vl conv(const vi& a, const vi& b) {
  vd lhs(sz(a)), rhs(sz(b));
  rep(i, 0, sz(a)) lhs[i] = a[i];
  rep(i, 0, sz(b)) rhs[i] = b[i];
  auto prod = conv(lhs, rhs);

  vl ans(sz(prod));
  rep(i, 0, sz(prod)) ans[i] = (ll)(round(prod[i]));
  return ans;
}

int dfsDown(const vector<vi>& adj, vi& down, int u = 0, int p = -1) {
  for (auto v : adj[u]) {
    if (v == p) continue;
    down[u] = max(down[u], dfsDown(adj, down, v, u) + 1);
  }
  return down[u];
}

void dfsUp(const vector<vi>& adj, const vi& down, vi& freq, int u = 0, int p = -1, int up = -1) {
  up++, freq[max(up, down[u])]++;

  vi next = {up};
  for (auto v : adj[u]) {
    if (v != p) next.push_back(down[v] + 1);
  }
  sort(rall(next));

  for (auto v : adj[u]) {
    if (v == p) continue;
    dfsUp(adj, down, freq, v, u, (next[0] == down[v] + 1 ? next[1] : next[0]));
  }
}

vi getDists() {
  int n;
  cin >> n;

  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vi down(n), freq(n);
  dfsDown(adj, down);
  dfsUp(adj, down, freq);
  return freq;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  auto lhs = getDists(), rhs = getDists();
  int dl = sz(lhs) - 1, dr = sz(rhs) - 1;
  while (lhs[dl] == 0) dl--;
  while (rhs[dr] == 0) dr--;

  ll ans = 0;
  auto prod = conv(lhs, rhs);
  rep(i, 0, sz(prod)) ans += (ll)max({i + 1, dl, dr}) * prod[i];
  cout << ans << '\n';
}
