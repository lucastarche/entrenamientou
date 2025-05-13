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

const int MAX_X = 5000;

vi getPrimes() {
  vi ans;
  rep(p, 2, MAX_X + 1) {
    bool prime = true;
    for (int d = 2; d * d <= p; d++) prime &= (p % d != 0);
    if (prime) ans.push_back(p);
  }
  return ans;
}

const auto primes = getPrimes();
const auto PRIMES = sz(primes);
const int MOD = 1e9 + 7;
const int SIZE = 5000;
using bs = bitset<SIZE>;

int solveLinear(vector<bs>& A, vi& b, bs& x, int m) {
  int n = sz(A), rank = 0, br;
  assert(m <= sz(x));
  vi col(m);
  iota(all(col), 0);
  rep(i, 0, n) {
    for (br = i; br < n; ++br)
      if (A[br].any()) break;
    if (br == n) {
      rep(j, i, n) if (b[j]) return -1;
      break;
    }
    int bc = (int)A[br]._Find_next(i - 1);
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j, 0, n) if (A[j][i] != A[j][bc]) {
      A[j].flip(i);
      A[j].flip(bc);
    }
    rep(j, i + 1, n) if (A[j][i]) {
      b[j] ^= b[i];
      A[j] ^= A[i];
    }
    rank++;
  }

  x = bs();
  for (int i = rank; i--;) {
    if (!b[i]) continue;
    x[col[i]] = 1;
    rep(j, 0, i) b[j] ^= A[j][i];
  }
  return rank;  // (multiple solutions if rank < m)
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<bs> A(PRIMES);
  rep(i, 0, n) {
    int x;
    cin >> x;
    rep(j, 0, PRIMES) while (x % primes[j] == 0) A[j].flip(i), x /= primes[j];
  }

  bs x;
  vi b(PRIMES, 0);
  int rank = solveLinear(A, b, x, n);

  int ans = 1;
  rep(i, rank, n) ans = (2 * ans) % MOD;
  cout << ans << '\n';
}
