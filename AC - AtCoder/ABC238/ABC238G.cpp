#include <bits/stdc++.h>
#pragma GCC optimize("O3")
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
using SmallVec = basic_string<int>;

const int MAX_X = 1e6;
const int BLOCK = 300;
const int POW = 20;

vi sieve() {
  vi nextPrime(MAX_X + 1, -1);
  rep(i, 2, MAX_X + 1) {
    if (nextPrime[i] != -1) continue;
    for (int j = i; j <= MAX_X; j += i) nextPrime[j] = i;
  }
  return nextPrime;
}

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) {
    return 0;
  }
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  const auto nextPrime = sieve();

  int n, q;
  cin >> n >> q;

  vi a(n);
  rep(i, 0, n) cin >> a[i];

  vector<SmallVec> primes(n);
  rep(i, 0, n) {
    while (a[i] > 1) {
      int p = nextPrime[a[i]];
      primes[i].push_back(p);
      a[i] /= p;
    }
  }

  vii queries(q);
  rep(i, 0, q) cin >> queries[i].first >> queries[i].second, queries[i].first--;

  vi perm(q);
  iota(all(perm), 0);
  sort(all(perm), [&](int i, int j) {
    return hilbertOrder(queries[i].first, queries[i].second, POW, 0) <
           hilbertOrder(queries[j].first, queries[j].second, POW, 0);
  });

  // Frecuencia de cada primo en a[l], ..., a[r-1]
  int l = 0, r = 0, wrong = 0;
  vi freq(MAX_X, 0);

  const auto add = [&](int i) {
    for (auto p : primes[i]) {
      if (freq[p] % 3 == 0) wrong++;
      freq[p]++;
      if (freq[p] % 3 == 0) wrong--;
    }
  };

  const auto remove = [&](int i) {
    for (auto p : primes[i]) {
      if (freq[p] % 3 == 0) wrong++;
      freq[p]--;
      if (freq[p] % 3 == 0) wrong--;
    }
  };

  vb ans(q);
  rep(i, 0, q) {
    auto [ql, qr] = queries[perm[i]];

    while (l > ql) add(--l);
    while (r < qr) add(r++);
    while (l < ql) remove(l++);
    while (r > qr) remove(--r);

    ans[perm[i]] = wrong == 0;
  }

  rep(i, 0, q) cout << (ans[i] ? "Yes" : "No") << '\n';
}
