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

const int MAX_N = 2e5 + 10;
const ll MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vi next(MAX_N, -1);
  rep(i, 2, MAX_N) {
    if (next[i] != -1) continue;
    for (int k = i; k < MAX_N; k += i) next[k] = i;
  }

  int n;
  cin >> n;
  vi p(n);
  rep(i, 0, n) cin >> p[i], p[i]--;

  vb seen(n);
  map<int, int> maxFreq;
  rep(i, 0, n) {
    if (seen[i]) continue;
    int len = 0;
    while (not seen[i]) len++, seen[i] = true, i = p[i];

    map<int, int> currFreq;
    while (len > 1) currFreq[next[len]]++, len /= next[len];
    for (auto [p, f] : currFreq) maxFreq[p] = max(maxFreq[p], f);
  }

  ll ans = 1;
  for (auto [p, f] : maxFreq) rep(_, 0, f) ans = (ans * p) % MOD;
  cout << ans << '\n';
}
