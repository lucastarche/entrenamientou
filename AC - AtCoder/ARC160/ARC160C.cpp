#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const int MAX_X = 2e5 + 100;
const ll MOD = 998244353;

vl compress(const vl &v) {
  vl ans((sz(v) + 1) / 2);
  rep(i, 0, sz(v)) ans[i / 2] = (ans[i / 2] + v[i]) % MOD;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi freq(MAX_X);
  rep(i, 0, n) {
    int x;
    cin >> x;
    freq[x]++;
  }

  vl prev(1, 1);
  rep(x, 0, MAX_X) {
    prev = compress(prev);

    ll acum = 0;
    vl curr(freq[x] + sz(prev));
    per(i, 0, sz(prev)) {
      acum = (acum + prev[i]) % MOD;
      curr[freq[x] + i] = (curr[freq[x] + i] + acum) % MOD;
    }
    swap(prev, curr);
  }

  ll ans = 0;
  for (auto x : prev) ans = (ans + x) % MOD;
  cout << ans << '\n';
}
