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

const int INF = 1e9 + 10;

template <class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      rep(j, 0, sz(jmp[k])) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) const {
    if (a == b) return INF;
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

ll solve(const RMQ<int> &lhs, const RMQ<int> &rhs) {
  const int n = sz(lhs.jmp[0]);
  ll ans = 0;
  rep(i, 0, sz(lhs.jmp[0])) {
    int lo = i, hi = n + 1;
    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;
      if (-lhs.query(i, mid) <= rhs.query(i, mid)) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    ans += lo - i;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n), b(n);
  rep(i, 0, n) cin >> a[i], a[i] *= -1;
  rep(i, 0, n) cin >> b[i];

  RMQ<int> lhs(a), rhs(b);
  ll ans = solve(lhs, rhs);
  rep(i, 0, sz(lhs.jmp)) rep(j, 0, sz(lhs.jmp[i])) lhs.jmp[i][j]--;
  ans -= solve(lhs, rhs);
  cout << ans << '\n';
}
