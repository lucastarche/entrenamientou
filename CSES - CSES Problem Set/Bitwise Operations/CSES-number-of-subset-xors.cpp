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

void insert(vi &basis, int x) {
  for (auto y : basis) {
    if ((x ^ y) < x) x ^= y;
    if (x == 0) break;
  }

  if (x > 0) basis.push_back(x);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi basis;
  rep(i, 0, n) {
    int x;
    cin >> x;
    insert(basis, x);
  }

  int ans = 1 << sz(basis);
  cout << ans << '\n';
}
