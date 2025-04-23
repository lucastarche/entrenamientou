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

const ll MOD = 1e9 + 7;
using Mat = vector<vector<ll>>;

ll modpow(ll x, ll y) {
  ll ans = 1;
  while (y > 0) {
    if (y & 1) ans = (ans * x) % MOD;
    x = (x * x) % MOD, y /= 2;
  }
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

Mat operator*(const Mat &lhs, const Mat &rhs) {
  const int n = sz(lhs);
  Mat ans(n, vector<ll>(n, 0));
  rep(i, 0, n) rep(k, 0, n) rep(j, 0, n) ans[i][j] = (ans[i][j] + lhs[i][k] * rhs[k][j]) % MOD;
  return ans;
}

Mat operator^(Mat lhs, int y) {
  const int n = sz(lhs);
  Mat ans(n, vector<ll>(n, 0));
  rep(i, 0, n) ans[i][i] = 1;

  while (y > 0) {
    if (y & 1) ans = ans * lhs;
    lhs = lhs * lhs, y /= 2;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  int x = count(all(a), 0);
  ll waysInv = modinv(n * (n - 1) / 2);
  Mat A(x + 1, vector<ll>(x + 1, 0));
  rep(y, 0, x + 1) {
    ll minus = y * (n - 2 * x + y) * waysInv % MOD;
    ll plus = (x - y) * (x - y) * waysInv % MOD;

    if (y > 0) A[y][y - 1] = minus;
    if (y + 1 <= x) A[y][y + 1] = plus;
    A[y][y] = ((1 - minus - plus) % MOD + MOD) % MOD;
  }

  A = A ^ k;

  int y0 = count(a.begin(), a.begin() + x, 0);
  cout << A[y0][x] << '\n';
}