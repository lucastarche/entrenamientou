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

const int BITS = 30;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k, x0;
  ll a, b, c;
  cin >> n >> k >> x0 >> a >> b >> c;

  int curr = 0;
  vi freq(BITS);
  queue<int> q;
  q.push(x0);

  const auto apply = [&](int x, int delta) {
    while (x > 0) {
      int b = __builtin_ctz(x);
      x ^= 1 << b;

      if (min(freq[b], freq[b] + delta) == 0) curr ^= (1 << b);
      freq[b] += delta;
    }
  };

  apply(x0, +1);
  rep(i, 1, k) q.push((a * q.back() + b) % c), apply(q.back(), +1);

  int ans = curr;
  rep(i, k, n) {
    int x = (a * q.back() + b) % c;
    apply(q.front() & (~x), -1), apply(x & (~q.front()), +1);
    q.pop(), q.push(x);
    ans ^= curr;
  }
  cout << ans << '\n';
}
