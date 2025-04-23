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

  int n, m;
  cin >> n >> m;

  vi freq(n);
  rep(i, 0, m) {
    int x, y;
    cin >> x >> y;
    freq[(x + y) % n]++;
  }

  ll ans = (ll)m * (m - 1) / 2LL;
  rep(i, 0, n) ans -= (ll)freq[i] * (freq[i] - 1) / 2LL;
  cout << ans << '\n';
}
