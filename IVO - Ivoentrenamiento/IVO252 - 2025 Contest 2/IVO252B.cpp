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

const int INF = 1e9;
const vector<string> OPTIONS = {"BGR", "BRG", "GBR", "GRB", "RBG", "RGB"};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;

    int ans = INF;
    for (auto t : OPTIONS) {
      int curr = 0;
      rep(i, 0, n) curr += t[i % 3] != s[i];
      ans = min(ans, curr);
    }
    cout << ans << '\n';
  }
}
