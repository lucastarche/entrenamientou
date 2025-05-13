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

  int n, m;
  cin >> n >> m;

  vector<string> a(n), b(n, string(m, ' '));
  rep(i, 0, n) cin >> a[i];

  rep(i, 0, n) rep(j, 0, m) {
    int seen = 0;
    seen |= 1 << (a[i][j] - 'A');
    if (i > 0) seen |= 1 << (b[i - 1][j] - 'A');
    if (j > 0) seen |= 1 << (b[i][j - 1] - 'A');

    int k = 0;
    while (seen & (1 << k)) k++;
    b[i][j] = (char)('A' + k);
  }

  rep(i, 0, n) cout << b[i] << '\n';
}
