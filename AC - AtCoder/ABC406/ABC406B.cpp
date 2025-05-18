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
  cin >> n >> k;

  ll val = 1, lim = 1;
  rep(i, 0, k) lim *= 10LL;

  rep(i, 0, n) {
    ll x;
    cin >> x;

    if (x < (lim + val - 1) / val) {
      val *= x;
    } else {
      val = 1;
    }
  }
  cout << val << '\n';
}
