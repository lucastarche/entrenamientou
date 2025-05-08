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

const ll MOD = 1e9 + 7;
using Mat = array<array<ll, 3>, 3>;

const Mat A = {0, 1, 0, 1, 1, 1, 0, 0, 1};

Mat operator*(const Mat &lhs, const Mat &rhs) {
  Mat ans;
  ans.fill({0, 0, 0});
  rep(i, 0, 3) rep(k, 0, 3) rep(j, 0, 3) ans[i][j] = (ans[i][j] + lhs[i][k] * rhs[k][j]) % MOD;
  return ans;
}

Mat operator^(Mat lhs, ll x) {
  Mat ans;
  rep(i, 0, 3) rep(j, 0, 3) ans[i][j] = i == j;

  while (x > 0) {
    if (x & 1) ans = ans * lhs;
    lhs = lhs * lhs, x /= 2;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  ll n;
  cin >> n;

  Mat B = A ^ (n - 1);
  ll ans = (B[0][0] + 2 * B[0][1] + B[0][2]) % MOD;
  cout << ans << '\n';
}