#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;

struct Solution {
  ll ans = -INF;
  const int n, r;
  vector<int> b, p, k;

  Solution(vector<int> _b, vector<int> _p, vector<int> _k, int _r) : n((int)_b.size()), r(_r), b(_b), p(_p), k(_k) {}

  ll computeScore(const vector<int> &a) {
    ll score = 0;
    for (int i = 0; i < n; i++) score += (ll)a[i] * k[i];
    return score;
  }

  vector<int> typeOne(vector<int> a) {
    for (int i = 0; i < n; i++) a[i] ^= b[i];
    return a;
  }

  vector<int> typeTwo(const vector<int> &a) {
    vector<int> ret(n);
    for (int i = 0; i < n; i++) ret[i] = a[p[i]] + r;
    return ret;
  }

  void solve(const vector<int> &a, int u, bool canTypeOne = true) {
    // Perform operations of type 1 until running out
    if (u % 2 == 0) ans = max(ans, computeScore(a));
    if (u == 0) return;

    // Type 1, ban this type for the next state
    if (canTypeOne) solve(typeOne(a), u - 1, false);

    // Type 2, we can now perform type 1 operations again
    solve(typeTwo(a), u - 1, true);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, u, r;
  cin >> n >> u >> r;

  vector<int> a(n), b(n), k(n), p(n);
  for (auto &x : a) cin >> x;
  for (auto &x : b) cin >> x;
  for (auto &x : k) cin >> x;
  for (auto &x : p) cin >> x, x--;

  Solution solution(b, p, k, r);
  solution.solve(a, u);
  cout << solution.ans << '\n';
}