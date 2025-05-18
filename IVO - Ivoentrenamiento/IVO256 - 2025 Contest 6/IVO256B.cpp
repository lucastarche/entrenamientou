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

  int t;
  cin >> t;
  while (t--) {
    int n;
    ll x;
    cin >> n >> x;

    vl a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));

    int ans = 0;
    ll cnt = 0, mini = 0;
    while (sz(a) > 0) {
      cnt++, mini = a.back();
      a.pop_back();

      if (cnt * mini >= x) {
        ans++, cnt = 0, mini = 0;
      }
    }
    cout << ans << '\n';
  }
}
