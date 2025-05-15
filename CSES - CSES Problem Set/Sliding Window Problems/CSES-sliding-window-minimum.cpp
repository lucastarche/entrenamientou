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

  int n, k;
  ll x0, a, b, c;
  cin >> n >> k >> x0 >> a >> b >> c;

  deque<pair<ll, int>> q;
  q.emplace_back(x0, 0);

  rep(i, 1, k) {
    x0 = (a * x0 + b) % c;
    while (not q.empty() && q.back().first >= x0) q.pop_back();
    q.emplace_back(x0, i);
  }

  ll ans = q.front().first;
  rep(i, k, n) {
    x0 = (a * x0 + b) % c;
    if (q.front().second == i - k) q.pop_front();
    while (not q.empty() && q.back().first >= x0) q.pop_back();
    q.emplace_back(x0, i);
    ans ^= q.front().first;
  }
  cout << ans << '\n';
}
