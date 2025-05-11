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

const int SIGMA = 26;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;
  const int n = sz(s);

  vector<int> freq(SIGMA);
  rep(i, 0, n) freq[s[i] - 'A']++;

  bool valid = true;
  rep(i, 0, SIGMA) valid &= freq[i] <= (n + 1) / 2;

  if (not valid) {
    cout << -1 << '\n';
    return 0;
  }

  int last = -1;
  string ans = "";
  rep(i, 0, n) {
    rep(c, 0, SIGMA) {
      if (freq[c] == (n - i + 1) / 2 && (n - i) % 2 == 1) {
        ans += (char)(c + 'A');
        freq[c]--;
        last = c;
        break;
      }
    }

    if (sz(ans) > i) continue;

    rep(c, 0, SIGMA) if (freq[c] && c != last) {
      ans += (char)(c + 'A');
      freq[c]--;
      last = c;
      break;
    }
  }
  cout << ans << '\n';
}
