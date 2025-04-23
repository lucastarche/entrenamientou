#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
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
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vi p(n);
    rep(i, 0, n) cin >> p[i], p[i]--;

    vb can(n, true);
    rep(i, 0, n) rep(j, i + 1, n) if (p[i] > p[j]) can[i] = false;
    cout << count(all(can), true) << '\n';
  }
}
