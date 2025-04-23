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

  ll n, d;
  cin >> n >> d;

  if (n * (n - 1) / 2 < d * n) {
    cout << "No\n";
    return 0;
  }

  cout << "Yes\n";
  rep(i, 0, n) rep(j, 1, d + 1) cout << i + 1 << " " << (i + j) % n + 1 << '\n';
}
