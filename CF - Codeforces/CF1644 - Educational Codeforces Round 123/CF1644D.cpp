#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const int NONE = -1;

// Compute the minimum value in the dictionary
int minValue(const map<int, int> &m) {
  int ans = m.begin()->second;
  for (auto &[_, v] : m) ans = min(ans, v);
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    // Compute the last operation which affected each row / column
    map<int, int> r, c;
    for (int i = 0; i < q; i++) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      r[x] = c[y] = i;
    }

    int minR = NONE, minC = NONE;
    // If there is no unaffected row / column, get the minimum key of r / c
    if ((int)r.size() == n) minR = minValue(r);
    if ((int)c.size() == m) minC = minValue(c);

    // Detect "important" operations: those which set the value of some cell at the end of the process
    vector<bool> important(q);
    for (auto [_, op] : r) important[max(op, minC)] = true;
    for (auto [_, op] : c) important[max(op, minR)] = true;

    // The answer is k^x, where x is the number of important operations
    ll ans = 1;
    for (int i = 0; i < q; i++) {
      if (important[i]) ans = (ans * k) % MOD;
    }
    cout << ans << '\n';
  }
}