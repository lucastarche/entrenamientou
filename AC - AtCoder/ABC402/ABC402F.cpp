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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll m;
  cin >> n >> m;

  vl pow10(2 * n + 1, 1);
  rep(i, 0, 2 * n) pow10[i + 1] = pow10[i] * 10 % m;

  vector<vl> a(n, vl(n));
  rep(i, 0, n) rep(j, 0, n) {
    int x;
    cin >> x;
    a[i][j] = pow10[2 * n - i - j - 2] * x % m;
  }

  vector<vl> vals(n);
  rep(mask, 0, 1 << (n - 1)) {
    int i = n - 1, j = n - 1;
    ll curr = 0;
    rep(b, 0, n - 1) {
      curr = (curr + a[i][j]) % m;
      ((mask & (1 << b)) ? i : j)--;
    }
    vals[i].push_back(curr);
  }

  rep(i, 0, n) sort(all(vals[i]));

  ll best = 0;
  rep(mask, 0, 1 << (n - 1)) {
    int i = 0, j = 0;
    ll curr = 0;
    rep(b, 0, n - 1) {
      curr = (curr + a[i][j]) % m;
      ((mask & (1 << b)) ? i : j)++;
    }
    curr = (curr + a[i][j]) % m;

    int pos = lower_bound(all(vals[i]), m - curr) - vals[i].begin();
    if (pos > 0) best = max(best, curr + vals[i][pos - 1]);
    best = max(best, (curr + vals[i].back()) % m);
  }
  cout << best << '\n';
}
