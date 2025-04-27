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
    cin >> n;

    string a, b;
    cin >> a >> b;

    if (a == b) {
      cout << (ll)(n) * (n + 1) / 2LL << '\n';
      continue;
    }

    int l = 0, r = 0;
    while (a[l] == b[l]) l++;
    while (a[n - r - 1] == b[n - r - 1]) r++;

    int curr = 0;
    vi seg;
    rep(i, 0, n) {
      if (a[i] == b[i]) {
        if (curr > 0) seg.push_back(curr), curr = 0;
      } else {
        curr++;
      }
    }

    if (curr > 0) seg.push_back(curr);

    if (sz(seg) > 2) {
      cout << 0 << '\n';
    } else if (sz(seg) == 2) {
      cout << 6 << '\n';
    } else {
      cout << 2LL * (l + r + seg[0] - 1) << '\n';
    }
  }
}
