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
    int n, a, b;
    cin >> n >> a >> b;

    if (a == 0 && b == 0) {
      cout << "YES\n";
      rep(i, 0, n) cout << i + 1 << " \n"[i + 1 == n];
      rep(i, 0, n) cout << i + 1 << " \n"[i + 1 == n];
      continue;
    } else if (a == 0 || b == 0 || a + b > n) {
      cout << "NO\n";
      continue;
    }

    vi p(n), q(n);
    rep(i, 0, a + b) p[i] = i, q[i] = (i + a) % (a + b);
    rep(i, a + b, n) p[i] = q[i] = i;

    cout << "YES\n";
    rep(i, 0, n) cout << p[i] + 1 << " \n"[i + 1 == n];
    rep(i, 0, n) cout << q[i] + 1 << " \n"[i + 1 == n];
  }
}
