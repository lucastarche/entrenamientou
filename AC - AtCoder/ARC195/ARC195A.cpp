#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

vi getSeq(const vi &a, const vi &b) {
  vi ans;

  int j = 0;
  rep(i, 0, sz(a)) {
    if (j < sz(b) && a[i] == b[j]) {
      ans.push_back(i);
      j++;
    }
  }

  if (j < sz(b)) return {};
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vi a(n), b(m);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, m) cin >> b[i];

  auto ltr = getSeq(a, b);
  reverse(all(a)), reverse(all(b));
  auto rtl = getSeq(a, b);

  reverse(all(rtl));
  for (auto &x : rtl) x = n - x - 1;

  if (not ltr.empty() && ltr != rtl) {
    cout << "Yes" << '\n';
  } else {
    cout << "No" << '\n';
  }
}
