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

void FST(vl& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j, i, i + step) {
        ll &u = a[j], &v = a[j + step];
        tie(u, v) = pair<ll, ll>(u + v, u - v);  // XOR
      }
  }
  if (inv)
    for (ll& x : a) x /= sz(a);  // XOR only
}

vl conv(vl a, vl b) {
  FST(a, 0);
  FST(b, 0);
  rep(i, 0, sz(a)) a[i] *= b[i];
  FST(a, 1);
  return a;
}

const int SIZE = 20;  // 2^20 > 1e6

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  int curr = 0;
  vl freq(1 << SIZE, 0);
  freq[0]++;
  for (auto x : a) curr ^= x, freq[curr]++;

  auto prod = conv(freq, freq);
  prod[0] -= n + 1;  // Saco subarrays vacíos

  vi ans;
  rep(i, 0, 1 << SIZE) if (prod[i] > 0) ans.push_back(i);

  cout << sz(ans) << '\n';
  rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i + 1 == sz(ans)];
}
