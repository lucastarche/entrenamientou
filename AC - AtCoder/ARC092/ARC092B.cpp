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

const int MAX_X = 1 << 28;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n), b(n);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, n) cin >> b[i];

  int ans = 0;
  for (int pow2 = 1; pow2 < 2 * MAX_X; pow2 *= 2) {
    bool parity = false;

    vi bOff, bOn;
    for (auto x : b) (x & pow2 ? bOn : bOff).push_back(x % pow2);
    sort(all(bOff)), sort(all(bOn));

    for (auto x : a) {
      int i = lower_bound(all(bOff), pow2 - (x % pow2)) - bOff.begin();
      int j = lower_bound(all(bOn), pow2 - (x % pow2)) - bOn.begin();

      if (x & pow2) {
        j = sz(bOn) - j;
      } else {
        i = sz(bOff) - i;
      }

      parity ^= (i % 2 == 1);
      parity ^= (j % 2 == 1);
    }

    if (parity) ans += pow2;
  }

  cout << ans << '\n';
}
