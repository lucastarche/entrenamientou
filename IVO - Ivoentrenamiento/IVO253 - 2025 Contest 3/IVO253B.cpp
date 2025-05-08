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

  int a, b, c;
  cin >> a >> b >> c;

  int pos = 0;
  vi seen(b);
  while (not seen[a]) {
    pos++;
    seen[a] = true;

    a *= 10;
    int d = a / b;
    a %= b;

    if (c == d) {
      cout << pos << '\n';
      return 0;
    }
  }

  cout << -1 << '\n';
}
