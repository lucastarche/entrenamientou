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

const int MAX_X = 2000 * 2000 + 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  bitset<MAX_X> can;
  can.set(0);
  for (auto x : a) can |= (can << x);

  const int sum = accumulate(all(a), 0);
  int ans = sum / 2;
  while (!can.test(ans)) ans--;
  cout << sum - ans << '\n';
}
