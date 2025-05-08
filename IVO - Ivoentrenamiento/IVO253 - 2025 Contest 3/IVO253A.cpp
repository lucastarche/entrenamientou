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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  sort(all(a));

  vi odd, even;
  rep(i, 0, (n + 1) / 2) odd.push_back(a[i]);
  rep(i, (n + 1) / 2, n) even.push_back(a[i]);

  vi ans;
  rep(i, 0, n / 2) ans.push_back(odd[i]), ans.push_back(even[i]);
  if (n % 2 == 1) ans.push_back(odd.back());

  rep(i, 0, n) cout << ans[i] << " \n"[i + 1 == n];
}
