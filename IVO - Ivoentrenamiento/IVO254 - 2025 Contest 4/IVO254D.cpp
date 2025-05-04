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

vi check(const vi &a, const vi &t, int k, int T) {
  priority_queue<pii, vii, greater<pii>> pq;
  rep(i, 0, sz(a)) if (a[i] >= k) pq.emplace(t[i], i + 1);

  vi ans;
  while (k > 0 && !pq.empty() && pq.top().first <= T) {
    ans.push_back(pq.top().second);
    T -= pq.top().first;
    pq.pop();
    k--;
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, T;
  cin >> n >> T;

  vi a(n), t(n);
  rep(i, 0, n) cin >> a[i] >> t[i];

  int lo = 0, hi = n + 1;
  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    auto v = check(a, t, mid, T);
    if (sz(v) == mid) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  auto ans = check(a, t, lo, T);
  cout << lo << '\n' << lo << '\n';
  rep(i, 0, lo) cout << ans[i] << " \n"[i + 1 == lo];
}
