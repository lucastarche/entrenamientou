#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int l, r, firstOdd;
    cin >> l >> r;
    string even, odd;
    if (l % 2 == 0) {
      even = "Alice";
      odd = "Bob";
      firstOdd = l + 1;
    } else {
      even = "Bob";
      odd = "Alice";
      firstOdd = l;
    }
    if (2 * firstOdd > r) {
      if (r % 2 == 0) cout << even << "\n";
      else cout << odd << "\n";
    } else {
      cout << odd << "\n";
    }
  }
}