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

constexpr ll K = 30;
ll inv(ll a) {
  ll r = 1;
#pragma GCC unroll(K)
  rep(l, 0, K) {
    if ((mod - 2) >> l & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
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
  int nInv = inv(n);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, 0, n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * nInv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}

vl integrate(const vl &p) {  // O(n)
  vl ans(sz(p) + 1);
  rep(i, 0, sz(p)) ans[i + 1] = (p[i] * inv(i + 1)) % mod;
  return ans;
}

vl naive(const vl &lhs, const vl &rhs) {
  vl ans(sz(lhs) + sz(rhs) - 1);
  rep(i, 0, sz(lhs)) rep(j, 0, sz(rhs)) ans[i + j] = (ans[i + j] + lhs[i] * rhs[j]) % mod;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  ll l;
  cin >> n >> k >> l;

  vl fact(3 * n + 1, 1), facti(3 * n + 1, 1);
  rep(i, 0, 3 * n) fact[i + 1] = fact[i] * (i + 1) % mod;
  facti.back() = inv(fact.back());
  per(i, 0, 3 * n) facti[i] = facti[i + 1] * (i + 1) % mod;

  ll linv = inv(l), l2 = (l * l) % mod, l2inv = inv(l2);
  vector<vl> ps(n + 1);
  ps[0] = {1}, ps[1] = {0, 2 * linv % mod, (-2 * l2inv % mod + mod) % mod};
  rep(i, 1, n) ps[i + 1] = naive(ps[i], ps[1]);

  vl val(n + 1);
  rep(i, 0, n + 1) {
    ll curr = 0;
    per(j, 0, sz(ps[i])) curr = ((curr * l) % mod + ps[i][j] * (fact[j] * facti[j + 1] % mod) % mod) % mod;
    curr = (curr * l) % mod;

    val[i] = curr;
  }

  ll ans = 0;
  rep(i, k, n + 1) {
    rep(j, 0, n - i + 1) {
      ll choose = fact[n] * ((facti[i] * facti[j] % mod) * facti[n - i - j] % mod) % mod;
      if ((n - i - j) % 2 == 1) choose = (mod - choose) % mod;
      ans = (ans + choose * val[n - j]) % mod;
    }
  }
  cout << ans << '\n';
}
