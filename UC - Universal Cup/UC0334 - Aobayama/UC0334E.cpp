#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)a; i < (int)b; ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;

    int zeros = count(all(s), '0'), longest = 0, curr = 0;
    for (auto c : s) {
      if (c == '0') {
        curr++;
      } else {
        curr = 0;
      }

      longest = max(longest, curr);
    }

    int pfx = 0, sfx = 0;
    while (pfx < n && s[pfx] == '0') pfx++;
    while (sfx < n && s[n - sfx - 1] == '0') sfx++;

    if (2 * longest > zeros) {
      cout << n - longest - (longest != pfx) - (longest != sfx) << '\n';
    } else {
      cout << zeros / 2 + (n - zeros - 1) - (pfx == 0 && sfx == 0 && zeros % 2 == 1) << '\n';
    }
  }
}