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

random_device rd;
mt19937 rng(rd());

const int ITERS = 10000;

vi primes(int x) {
  if (x == 0) return {};

  vi ans;
  for (int p = 2; p * p <= x; p++) {
    if (x % p == 0) ans.push_back(p);
    while (x % p == 0) x /= p;
  }
  if (x > 1) ans.push_back(x);
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  const auto check = [&](int p, int i) {
    int cnt = 0;
    rep(j, 0, n) cnt += a[i] % p == a[j] % p;

    if (2 * cnt > n) {
      cout << p << '\n';
      exit(0);
    }
  };

  rep(i, 0, n) check(4, i);

  uniform_int_distribution<int> dist(0, n - 1);
  rep(_, 0, ITERS) {
    int i = dist(rng), j = dist(rng);
    int delta = abs(a[i] - a[j]);

    for (auto p : primes(delta)) {
      if (p > 2) check(p, i);
    }
  }

  cout << -1 << '\n';
}
