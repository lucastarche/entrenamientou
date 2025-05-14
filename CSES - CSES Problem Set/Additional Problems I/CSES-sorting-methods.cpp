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

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

ll countInversions(const vi &p) {
  const int n = sz(p);
  FT ft(n);

  ll ans = 0;
  rep(i, 0, n) {
    ans += i - ft.query(p[i]);
    ft.update(p[i], +1);
  }
  return ans;
}

int countSwaps(vi p) {
  const int n = sz(p);
  vi where(n);
  rep(i, 0, n) where[p[i]] = i;

  int ans = 0;
  rep(i, 0, n) {
    if (where[i] == i) continue;
    ans++;

    int j = where[i];
    swap(where[i], where[p[i]]);
    swap(p[i], p[j]);
  }

  return ans;
}

template <class I>
vi lis(const vector<I> &S) {
  if (S.empty()) return {};
  vi prev(sz(S));
  typedef pair<I, int> p;
  vector<p> res;
  rep(i, 0, sz(S)) {
    // change 0 -> i for longest non-decreasing subsequence
    auto it = lower_bound(all(res), p{S[i], 0});
    if (it == res.end()) res.emplace_back(), it = res.end() - 1;
    *it = {S[i], i};
    prev[i] = it == res.begin() ? 0 : (it - 1)->second;
  }
  int L = sz(res), cur = res.back().second;
  vi ans(L);
  while (L--) ans[L] = cur, cur = prev[cur];
  return ans;
}

int countdown(const vi &p) {
  const int n = sz(p);
  int ans = n;
  per(i, 0, n) if (p[i] == ans - 1) ans--;
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;

  vi p(n);
  rep(i, 0, n) cin >> p[i], p[i]--;

  cout << countInversions(p) << " " << countSwaps(p) << " " << n - sz(lis(p)) << " " << countdown(p) << '\n';
}
