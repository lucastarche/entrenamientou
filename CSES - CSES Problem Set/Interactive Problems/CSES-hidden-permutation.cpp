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

int lessThan(int i, int j) {
  cout << "? " << i + 1 << ' ' << j + 1 << '\n';
  cout.flush();

  string ans;
  cin >> ans;
  return ans == "YES";
}

vi solve(const vi &a) {
  if (sz(a) == 1) return a;

  const int k = sz(a) / 2;
  vi lhs, rhs;
  rep(i, 0, k) lhs.push_back(a[i]);
  rep(i, k, sz(a)) rhs.push_back(a[i]);

  lhs = solve(lhs), rhs = solve(rhs);

  int i = 0, j = 0;
  vi ans;
  while (i < sz(lhs) || j < sz(rhs)) {
    if (i < sz(lhs) && j < sz(rhs)) {
      if (lessThan(lhs[i], rhs[j])) {
        ans.push_back(lhs[i++]);
      } else {
        ans.push_back(rhs[j++]);
      }
    } else if (i < sz(lhs)) {
      ans.push_back(lhs[i++]);
    } else {
      ans.push_back(rhs[j++]);
    }
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi p(n);
  iota(all(p), 0);
  p = solve(p);

  vi where(n);
  rep(i, 0, n) where[p[i]] = i;

  cout << "! ";
  rep(i, 0, n) cout << where[i] + 1 << " \n"[i == n - 1];
  cout.flush();
}
