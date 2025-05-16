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

struct UF {
  vi next;
  vl delta;

  UF(int n) : next(n), delta(n, 0) { iota(all(next), 0); }

  pair<int, ll> find(int x) {
    if (x == next[x]) return {x, 0};
    auto [p, d] = find(next[x]);
    next[x] = p, delta[x] += d;
    return {next[x], delta[x]};
  }

  bool join(int x, int y, ll s) {
    ll dx, dy;
    tie(x, dx) = find(x);
    tie(y, dy) = find(y);

    if (x == y) return dx - dy == s;
    next[x] = y;
    delta[x] = s + dy - dx;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  bool valid = true;
  UF uf(n + 1);
  rep(i, 0, m) {
    int l, r, s;
    cin >> l >> r >> s, l--;
    valid &= uf.join(r, l, s);
  }

  if (valid) {
    cout << "YES\n";
    rep(i, 0, n) cout << uf.find(i + 1).second - uf.find(i).second << " \n"[i == n - 1];
  } else {
    cout << "NO\n";
  }
}
