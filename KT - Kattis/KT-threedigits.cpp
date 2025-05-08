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

void solveSmall(ll n) {
  ll ans = 1;
  rep(i, 1, n + 1) ans *= i;
  while (ans % 10 == 0) ans /= 10;

  string s = to_string(ans);
  if (sz(s) <= 3) {
    cout << s << '\n';
  } else {
    cout << s.substr(sz(s) - 3) << '\n';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  ll n;
  cin >> n;

  if (n <= 20) return solveSmall(n), 0;

  ll fives = 0;
  for (ll x = 5; x <= n; x *= 5) fives += n / x;

  ll ans = 1;
  rep(i, 1, n + 1) {
    ll x = i;
    while (x % 5 == 0) x /= 5;
    while (x % 2 == 0 && fives > 0) x /= 2, fives--;
    ans = (ans * x) % 1000;
  }

  string s = to_string(ans);
  cout << string(3 - sz(s), '0') << s << '\n';
}