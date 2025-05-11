#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (a); --i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
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

void normalize(vi &basis) {
  sort(all(basis));
  rep(i, 0, sz(basis)) rep(j, i + 1, sz(basis)) if ((basis[j] ^ basis[i]) < basis[j]) basis[j] ^= basis[i];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  vi basis;
  rep(i, 0, n) {
    int x;
    cin >> x;
    insert(basis, x);
  }
  normalize(basis);

  int outside = n - sz(basis), step = 1;
  rep(i, 0, outside) step = min(2 * step, k);

  rep(i, 0, k) {
    int mask = i / step, x = 0;
    rep(b, 0, sz(basis)) if (mask & (1 << b)) x ^= basis[b];
    cout << x << " ";
  }
  cout << '\n';
}
