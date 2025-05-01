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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll a, b;
  cin >> a >> b;

  if (a % 2 == 1) {
    cout << 0 << '\n';
    return 0;
  }

  ll x = a / 2LL;
  ll ans = 1;
  while (b--) ans = (ans * x) % a;
  cout << ans << '\n';
}
