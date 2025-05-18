// Lei mal el enunciado, hay que recorrerlos del 1 al n ...
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

const int MAX_X = 1e5 + 1;

pair<ll, int> getCost(const vi &a, ll C, ll D) {
  pair<ll, int> ans = {C * MAX_X, MAX_X};

  int cnt = 0, pos = sz(a) - 1;
  ll moves = 0;
  per(i, 0, MAX_X) {
    moves += cnt;
    ans = min(ans, pair<ll, int>(C * i + D * moves, i));
    while (pos >= 0 && a[pos] == i) cnt++, pos--;
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll C, D;
  cin >> n >> C >> D;

  vi left, right;
  vi a(n);
  rep(i, 0, n) {
    cin >> a[i];
    if (a[i] > 0) right.push_back(a[i]);
    if (a[i] < 0) left.push_back(-a[i]);
  }
  sort(all(left)), sort(all(right));

  const auto [cl1, l1] = getCost(left, C, D);
  const auto [cl2, l2] = getCost(left, 2 * C, D);
  const auto [cr1, r1] = getCost(right, C, D);
  const auto [cr2, r2] = getCost(right, 2 * C, D);

  int l, r;
  ll ans = 0;
  if (cl1 + cr2 <= cl2 + cr1) {
    l = l1, r = r2, ans = cl1 + cr2;
  } else {
    l = l2, r = r1, ans = cl2 + cr1;
  }

  cout << ans << '\n';
  rep(i, 0, n) cout << clamp(a[i], l, r) << " \n"[i + 1 == n];
}
