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

const int SIZE = 20;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  stack<int> s;
  vector<vi> next(SIZE, vi(n + 1, n));
  per(i, 0, n) {
    while (not s.empty() && a[i] >= a[s.top()]) s.pop();
    if (not s.empty()) next[0][i] = s.top();
    s.push(i);
  }

  rep(step, 0, SIZE - 1) rep(i, 0, n) next[step + 1][i] = next[step][next[step][i]];

  while (q--) {
    int x, y;
    cin >> x >> y, x--, y--;

    int ans = 1;
    per(step, 0, SIZE) {
      if (next[step][x] <= y) {
        ans += 1 << step;
        x = next[step][x];
      }
    }
    cout << ans << '\n';
  }
}
