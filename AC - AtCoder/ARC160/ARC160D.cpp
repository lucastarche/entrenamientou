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
using vl = vector<ll>;

const ll mod = (119 << 23) + 1, root = 62;  // = 998244353
const ll MOD = mod;
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}

ll modinv(ll b) { return modpow(b, mod - 2); }

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

vl binpow(vl b, ll e) {
  vl ans(1, 1);
  while (e > 0) {
    if (e % 2 == 1) ans = conv(ans, b);
    b = conv(b, b), e /= 2;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll n, m, k;
  cin >> n >> m >> k;

  if (m % k != 0) {
    cout << 0 << '\n';
    return 0;
  }

  ll ops = m / k;
  vl f(k, 1);
  f = binpow(f, n - k + 1);

  ll choose = 1, freq = 0;

  const auto mult = [&](ll x) {
    while (x % MOD == 0 && x > 0) x /= MOD, freq++;
    choose = (choose * (x % MOD)) % MOD;
  };

  const auto div = [&](ll x) {
    while (x % MOD == 0 && x > 0) x /= MOD, freq--;
    choose = (choose * modinv(x % MOD)) % MOD;
  };

  rep(i, 1, n) mult(ops + i), div(i);

  ll ans = 0;
  rep(i, 0, min(ops + 1, (ll)sz(f))) {
    if (freq == 0) ans = (ans + f[i] * choose) % MOD;
    mult(ops - i), div(n - 1 + ops - i);
  }

  cout << (ans + MOD) % MOD << '\n';
}
