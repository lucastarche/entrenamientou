#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const ll MOD = 998244353;

ll mult(ll x, ll y) { return ((x % MOD) * (y % MOD)) % MOD; }

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    vl a;
    rep(i, 0, n) {
      ll x;
      cin >> x;
      if (x > 0) a.push_back(x);
    }
    sort(all(a));

    while (sz(a) >= k) {
      ll next = 1;
      rep(i, 0, k) {
        next = mult(next, a.back());
        a.pop_back();
      }
      a.push_back(next);
    }

    if (a.empty()) a.push_back(0);
    cout << a.back() % MOD << '\n';
  }
}