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

using ld = long double;
using vd = vector<ld>;

vd getDist(int n, int l, int d) {
  vd p(n + 1);
  p[0] = 1.0l;

  ld curr = 0.0l;
  queue<ld> events;
  rep(i, 0, n + 1) {
    if (sz(events) > d) {
      curr -= events.front();
      events.pop();
    }

    if (i > 0) p[i] = curr;
    if (i < l) {
      ld next = p[i] / (ld)(d);
      events.push(next), curr += next;
      p[i] = 0;
    } else {
      events.push(0);
    }
  }

  return p;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, l, d;
  cin >> n >> l >> d;

  vd distRival = getDist(n, l, d);
  vd pWin(n + 1, 0.0);
  pWin[0] = 1.0L - accumulate(all(distRival), 0.0L);
  rep(i, 1, n + 1) pWin[i] = pWin[i - 1] + distRival[i - 1];

  ld curr = 0.0l;
  queue<ld> events;
  per(i, 0, n + 1) {
    if (sz(events) > d) {
      curr -= events.front();
      events.pop();
    }

    pWin[i] = max(pWin[i], curr);

    ld next = pWin[i] / (ld)(d);
    curr += next, events.push(next);
  }

  cout << fixed << setprecision(10) << pWin[0] << '\n';
}
