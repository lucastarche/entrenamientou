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

const int MAX_N = 1e6;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vi v2(MAX_N + 1, 0);
  rep(i, 1, MAX_N + 1) {
    int x = i;
    v2[i] = v2[i - 1];
    while (x % 2 == 0) v2[i]++, x /= 2;
  }

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    rep(i, 0, n) {
      if (v2[n - 1] == v2[i] + v2[n - i - 1]) {
        cout << k << ' ';
      } else {
        cout << 0 << ' ';
      }
    }
    cout << '\n';
  }
}
