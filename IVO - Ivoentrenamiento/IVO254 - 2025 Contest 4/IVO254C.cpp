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

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vii v(n);
  rep(i, 0, n) cin >> v[i].first >> v[i].second;
  sort(all(v));

  vi next(n, -1);
  rep(i, 0, n) {
    int pos = v[i].first - v[i].second;
    auto j = lower_bound(all(v), pii{pos, -INF}) - v.begin();
    next[i] = j - 1;
  }

  vi len(n, 1);
  rep(i, 0, n) if (next[i] >= 0) len[i] = len[next[i]] + 1;
  cout << n - *max_element(all(len)) << '\n';
}
