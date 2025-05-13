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

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] = (s[pos] + dif) % MOD;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res = (res + s[pos - 1]) % MOD;
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  FT dp(n + 1);
  dp.update(0, +1);
  map<int, int> last;

  int right = 0;
  rep(i, 0, n) {
    int x;
    cin >> x;

    if (last.count(x)) right = max(right, last[x] + 1);
    ll curr = (dp.query(i + 1) + MOD - dp.query(right)) % MOD;
    last[x] = i;
    dp.update(i + 1, +curr);
  }

  cout << (dp.query(n + 1) + MOD - dp.query(n)) % MOD << '\n';
}
