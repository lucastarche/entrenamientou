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

  int N, W;
  cin >> N >> W;

  vector<priority_queue<int>> pqs(W + 1);
  rep(i, 0, N) {
    int w, v;
    cin >> w >> v;
    pqs[w].push(v - 1);
  }

  vii a;
  rep(w, 1, W + 1) {
    if (pqs[w].empty()) continue;
    rep(_, 0, W / w) {
      auto v = pqs[w].top();
      pqs[w].pop();

      a.emplace_back(w, v);
      pqs[w].push(v - 2);
    }
  }

  vl dp(W + 1, 0);
  for (auto [w, v] : a) {
    per(i, 0, W - w + 1) dp[i + w] = max(dp[i + w], dp[i] + v);
  }
  cout << *max_element(all(dp)) << '\n';
}
