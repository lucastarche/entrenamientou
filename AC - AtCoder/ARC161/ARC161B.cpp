#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
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
    ll n;
    cin >> n;

    if (n < 7) {
      cout << "-1\n";
      continue;
    }

    ll b1 = 2, b2 = 1, b3 = 0;
    while ((2LL << b1) + (1LL << b2) + (1LL << b3) <= n) b1++;
    while ((1LL << b1) + (2LL << b2) + (1LL << b3) <= n && b2 + 1 < b1) b2++;
    while ((1LL << b1) + (1LL << b2) + (2LL << b3) <= n && b3 + 1 < b2) b3++;
    cout << (1LL << b1) + (1LL << b2) + (1LL << b3) << '\n';
  }
}
