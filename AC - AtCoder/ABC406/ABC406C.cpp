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

  int n;
  cin >> n;

  vi p(n);
  rep(i, 0, n) cin >> p[i];

  vii events;
  events.emplace_back(0, 0);
  rep(i, 1, n - 1) {
    if (p[i] > p[i - 1] && p[i] > p[i + 1]) events.emplace_back(i, 1);
    if (p[i] < p[i - 1] && p[i] < p[i + 1]) events.emplace_back(i, -1);
  }
  events.emplace_back(n - 1, 0);

  ll ans = 0;
  rep(i, 1, sz(events) - 1) {
    if (events[i].second != 1) continue;
    if (events[i + 1].second != -1) continue;

    int lhs = events[i].first - events[i - 1].first;
    int rhs = events[i + 2].first - events[i + 1].first;
    ans += (ll)(lhs)*rhs;
  }
  cout << ans << '\n';
}
