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

vi getLeft(const vi &a) {
  const int n = sz(a);
  stack<int> s;

  vi ans(n, -1);
  rep(i, 0, n) {
    while (!s.empty() && a[s.top()] <= a[i]) s.pop();
    if (!s.empty()) ans[i] = s.top();
    s.push(i);
  }
  return ans;
}

vi getRight(vi a) {
  reverse(all(a));
  auto ans = getLeft(a);
  reverse(all(ans));
  rep(i, 0, sz(a)) ans[i] = (ans[i] == -1 ? -1 : sz(a) - ans[i] - 1);
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  vi p(n), dp(n, 1);
  iota(all(p), 0);
  sort(all(p), [&](int i, int j) { return a[i] < a[j]; });

  const auto left = getLeft(a), right = getRight(a);
  for (auto i : p) {
    if (left[i] != -1) dp[left[i]] = max(dp[left[i]], dp[i] + 1);
    if (right[i] != -1) dp[right[i]] = max(dp[right[i]], dp[i] + 1);
  }
  cout << *max_element(all(dp)) << '\n';
}
