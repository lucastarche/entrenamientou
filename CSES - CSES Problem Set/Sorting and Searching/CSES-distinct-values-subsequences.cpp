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

const ll MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n);
  rep(i, 0, n) cin >> a[i];
  sort(all(a));

  int last = -1, freq = 0;
  ll ans = 1;
  for (auto x : a) {
    if (x == last) {
      freq++;
    } else {
      ans = (ans * (freq + 1)) % MOD;
      freq = 1, last = x;
    }
  }

  ans = (ans * (freq + 1)) % MOD;
  ans = (ans + MOD - 1) % MOD;  // La vacia no cuenta
  cout << ans << '\n';
}
