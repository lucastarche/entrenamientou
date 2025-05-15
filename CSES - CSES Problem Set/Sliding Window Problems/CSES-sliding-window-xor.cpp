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

  int n, k;
  ll x0, a, b, c;
  cin >> n >> k >> x0 >> a >> b >> c;

  ll ans = x0;
  rep(i, 1, n) {
    x0 = (a * x0 + b) % c;
    if (min({i + 1, n - i, k}) % 2 == 1) ans ^= x0;
  }
  cout << ans << '\n';
}
