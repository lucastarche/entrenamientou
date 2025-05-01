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
  int N;
  vi v;
  vb bad;
  vector<priority_queue<pii>> s;

  Tree(vi _v, int Q) : v(_v), bad(Q, false) {
    N = 1;
    while (N < sz(v)) N *= 2;
    s.resize(2 * N);
  }

  void cancel(int i) { bad[i] = true; }

  void set(int l, int r, pii val, int k = 1, int a = 0, int b = -1) {
    if (k == 1) b = N;
    if (r <= a || b <= l) return;
    if (l <= a && b <= r) return s[k].push(val);
    int mid = (a + b) / 2;
    set(l, r, val, 2 * k, a, mid);
    set(l, r, val, 2 * k + 1, mid, b);
  }

  int get(int pos, int k = 1, int a = 0, int b = -1) {
    if (k == 1) b = N;
    while (!s[k].empty() && bad[s[k].top().second]) s[k].pop();

    int ans = 0;
    if (!s[k].empty()) ans = s[k].top().first;
    if (a + 1 == b) return max(ans, v[pos]);

    int mid = (a + b) / 2;
    if (pos < mid) {
      return max(ans, get(pos, 2 * k, a, mid));
    } else {
      return max(ans, get(pos, 2 * k + 1, mid, b));
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  int q;
  cin >> q;

  Tree tree(a, q);
  rep(i, 0, q) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r, x;
      cin >> l >> r >> x, l--;
      tree.set(l, r, {x, i});
    } else if (type == 2) {
      int j;
      cin >> j, j--;
      tree.cancel(j);
    } else {
      int j;
      cin >> j, j--;
      cout << tree.get(j) << '\n';
    }
  }
}
