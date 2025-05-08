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

using ld = long double;
using vd = vector<ld>;

const ld PI = acosl(-1);
const ld TO_RADIAN = PI / 180.0l;

using Point = pair<ld, ld>;
Point operator+(const Point &a, const Point &b) { return {a.first + b.first, a.second + b.second}; }
Point rot(const Point &p, int theta) {
  const ld c = cosl(TO_RADIAN * theta);
  const ld s = sinl(TO_RADIAN * theta);
  return {p.first * c + p.second * s, -p.first * s + p.second * c};
}

struct Tree {
  int n;
  vector<Point> s;
  vi lazy;

  Tree(int _n) : n(_n), s(2 * n), lazy(2 * n) {}

  void push(int k) {
    for (int i : {2 * k, 2 * k + 1}) {
      s[i] = rot(s[i], lazy[k]);
      lazy[i] += lazy[k];
    }
    lazy[k] = 0;
  }

  void add(int pos, int delta, int k = 1, int a = 0, int b = -1) {
    if (k == 1) b = n;
    if (a == pos && b == pos + 1) return void(s[k] = s[k] + rot(Point{delta, 0.0l}, lazy[k]));

    push(k);

    int mid = (a + b) / 2;
    if (pos < mid) {
      add(pos, delta, 2 * k, a, mid);
    } else {
      add(pos, delta, 2 * k + 1, mid, b);
    }

    s[k] = rot(s[2 * k] + s[2 * k + 1], lazy[k]);
  }

  void rotRange(int l, int r, int theta, int k = 1, int a = 0, int b = -1) {
    if (k == 1) b = n;
    if (r <= a || b <= l) return;
    if (l <= a && b <= r) return void((lazy[k] += theta, s[k] = rot(s[k], theta)));

    push(k);
    int mid = (a + b) / 2;
    rotRange(l, r, theta, 2 * k, a, mid);
    rotRange(l, r, theta, 2 * k + 1, mid, b);
    s[k] = rot(s[2 * k] + s[2 * k + 1], lazy[k]);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  int N = 1;
  while (N < n) N *= 2;
  Tree tree(N);

  rep(i, 0, n) tree.add(i, 1);

  cout << fixed << setprecision(10);
  rep(i, 0, m) {
    int type, pos, delta;
    cin >> type >> pos >> delta, pos--;

    if (type == 1) {
      tree.add(pos, delta);
    } else {
      tree.rotRange(pos, n, delta);
    }

    cout << tree.s[1].first << " " << tree.s[1].second << '\n';
  }
}
