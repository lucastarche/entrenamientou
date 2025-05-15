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

struct Tree {
  int n;
  vii s;
  Tree(int _n) : n(_n), s(2 * n) {
    rep(i, 0, n) s[i + n].second = -i;
    per(i, 1, n) s[i] = max(s[2 * i], s[2 * i + 1]);
  }
  void update(int pos, int delta) {
    for (s[pos += n].first += delta; pos /= 2;) s[pos] = max(s[2 * pos], s[2 * pos + 1]);
  }

  int get() const { return -s[1].second; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  vi cmp = a;
  sort(all(cmp));
  cmp.erase(unique(all(cmp)), cmp.end());
  rep(i, 0, n) a[i] = lower_bound(all(cmp), a[i]) - cmp.begin();

  Tree st(sz(cmp));
  rep(i, 0, k) st.update(a[i], +1);

  cout << cmp[st.get()] << ' ';
  rep(i, k, n) {
    st.update(a[i], +1);
    st.update(a[i - k], -1);
    cout << cmp[st.get()] << ' ';
  }
  cout << '\n';
}
