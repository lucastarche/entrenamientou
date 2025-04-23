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

const int MAX_N = 1e3;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, L, R;
  cin >> n >> L >> R;

  int ans = 0;
  rep(i, 0, n) {
    int x;
    cin >> x;
    ans ^= (x % (L + R)) / L;
  }

  cout << (ans == 0 ? "Second" : "First") << '\n';
}
