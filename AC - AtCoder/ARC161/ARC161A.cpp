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
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n);
  rep(i, 0, n) cin >> a[i];
  sort(all(a));

  int k = (n + 1) / 2;

  vi b(n, -1);
  rep(i, 0, k) b[2 * i] = a[i];
  rep(i, 0, k - 1) b[2 * i + 1] = a[i + k];

  bool valid = true;
  rep(i, 0, k - 1) valid &= b[2 * i + 1] > max(b[2 * i], b[2 * i + 2]);
  cout << (valid ? "Yes" : "No") << '\n';
}
