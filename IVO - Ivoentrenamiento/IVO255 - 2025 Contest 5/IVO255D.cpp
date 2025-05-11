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

  set<int> s;
  rep(i, 0, n) {
    int x;
    cin >> x;
    s.insert(x);
  }

  while (true) {
    int x = *s.rbegin(), y = x;
    s.erase(x), x /= 2;
    while (x > 0 && s.count(x)) x /= 2;

    if (x > 0) {
      s.insert(x);
    } else {
      s.insert(y);
      break;
    }
  }

  for (auto x : s) cout << x << " ";
  cout << '\n';
}
