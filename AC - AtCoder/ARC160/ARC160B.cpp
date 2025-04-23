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

const ll MOD = 998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;

    int s = 1;
    while ((s + 1) * (s + 1) <= N) s++;

    ll ans = (ll)(s)*s * s % MOD;

    rep(maxi, 1, s + 1) {
      ans = (ans + 3LL * (N / maxi - s)) % MOD;
      ans = (ans + 6LL * (maxi - 1) * (N / maxi - s)) % MOD;
    }

    cout << ans << '\n';
  }
}
