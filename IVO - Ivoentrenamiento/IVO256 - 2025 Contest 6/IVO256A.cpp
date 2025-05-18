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

  string s;
  cin >> s;

  int f1 = 0, f2 = 0, f3 = 0;
  for (auto c : s) {
    f1 += (c == '1');
    f2 += (c == '2');
    f3 += (c == '3');
  }

  string ans = "";
  while (f1 > 0) ans += "1+", f1--;
  while (f2 > 0) ans += "2+", f2--;
  while (f3 > 0) ans += "3+", f3--;
  ans.pop_back();

  cout << ans << '\n';
}
