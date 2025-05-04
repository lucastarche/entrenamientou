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

  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;

    int ones = count(all(s), '1');
    if (ones == 0) {
      cout << 0 << '\n';
      continue;
    }

    int pfx = 0, sfx = 0;
    while (s[pfx] == '0') pfx++;
    while (s[n - sfx - 1] == '0') sfx++;

    priority_queue<int> pq;
    pq.push(2 * pfx), pq.push(2 * sfx);

    int curr = 0;
    rep(i, pfx, n - sfx) {
      if (s[i] == '1') {
        if (curr > 0) pq.push(curr), pq.push(curr), curr = 0;
      } else {
        curr++;
      }
    }

    int cnt = 0, ans = 2 * n;
    while (not pq.empty() && cnt < pq.top()) {
      ans -= pq.top() - cnt;
      pq.pop();
      cnt += 2;
    }

    cout << ans / 2 << '\n';
  }
}
