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

const ll mod = (119 << 23) + 1, root = 62;  // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}

void ntt(vl &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vl rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = {1, modpow(root, mod >> s)};
    rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
}
vl conv(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = modpow(n, mod - 2);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, 0, n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}

vl add(const vl &p, const vl &q) {
  vl res(max(sz(p), sz(q)));
  rep(i, 0, sz(p)) res[i] += p[i];
  rep(i, 0, sz(q)) res[i] += q[i];
  for (ll &x : res) x %= mod;
  while (!res.empty() && !res.back()) res.pop_back();
  return res;
}

pair<vl, vl> solve(const vi &a) {
  if (sz(a) == 1) {
    vl p = {1}, q(a[0] + 1, 0);
    q.back() = 1;
    return {p, q};
  }

  vi left, right;
  rep(i, 0, sz(a) / 2) left.push_back(a[i]);
  rep(i, sz(a) / 2, sz(a)) right.push_back(a[i]);

  auto [pl, ql] = solve(left);
  auto [pr, qr] = solve(right);
  return {add(conv(pl, pr), conv(ql, qr)), add(conv(pl, qr), conv(pr, ql))};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vi a(n);
  rep(i, 0, n) cin >> a[i];
  auto [_, q] = solve(a);

  if (sz(q) <= m) {
    cout << 0 << '\n';
  } else {
    cout << q[m] << '\n';
  }
}
