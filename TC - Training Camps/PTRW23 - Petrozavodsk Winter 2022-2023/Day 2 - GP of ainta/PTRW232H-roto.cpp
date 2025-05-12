// NOTA: deberia funcionar en teoria, pero el error numerico de simplex explota
// lo puse en el repo xq me dio lastima borrarlo (???
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

typedef long double T;
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-12, inf = 1 / .0;
#define MP make_pair
#define ltj(X) \
  if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s])) s = j

struct LPSolver {
  int m, n;
  vi N, B;
  vvd D;

  LPSolver(const vvd &A, const vd &b, const vd &c) : m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
    rep(i, 0, m) rep(j, 0, n) D[i][j] = A[i][j];
    rep(i, 0, m) {
      B[i] = n + i;
      D[i][n] = -1;
      D[i][n + 1] = b[i];
    }
    rep(j, 0, n) {
      N[j] = j;
      D[m][j] = -c[j];
    }
    N[n] = -1;
    D[m + 1][n] = 1;
  }

  void pivot(int r, int s) {
    T *a = D[r].data(), inv = 1 / a[s];
    rep(i, 0, m + 2) if (i != r && abs(D[i][s]) > eps) {
      T *b = D[i].data(), inv2 = b[s] * inv;
      rep(j, 0, n + 2) b[j] -= a[j] * inv2;
      b[s] = a[s] * inv2;
    }

    rep(j, 0, n + 2) if (j != s) D[r][j] *= inv;
    rep(i, 0, m + 2) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }

  bool simplex(int phase) {
    int x = m + phase - 1;
    for (;;) {
      int s = -1;
      rep(j, 0, n + 1) if (N[j] != -phase) ltj(D[x]);
      if (D[x][s] >= -eps) return true;
      int r = -1;
      rep(i, 0, m) {
        if (D[i][s] <= eps) continue;
        if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i]) < MP(D[r][n + 1] / D[r][s], B[r])) r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }

  T solve(vd &x) {
    int r = 0;
    rep(i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -eps) {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
      rep(i, 0, m) if (B[i] == -1) {
        int s = 0;
        rep(j, 1, n + 1) ltj(D[i]);
        pivot(i, s);
      }
    }

    bool ok = simplex(1);
    x = vd(n);
    rep(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return ok ? D[m][n + 1] : inf;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vl x(n), y(n);
    rep(i, 0, n) cin >> x[i] >> y[i];

    vvd A(2 * n, vd(4, 0));
    vd b(2 * n), c(4);
    c[0] = -1.0l;

    rep(i, 0, n) {
      A[2 * i][0] = A[2 * i + 1][0] = -1;

      A[2 * i][1] = -x[i] * x[i];
      A[2 * i + 1][1] = x[i] * x[i];

      A[2 * i][2] = -x[i];
      A[2 * i + 1][2] = x[i];

      A[2 * i][3] = -1;
      A[2 * i + 1][3] = 1;

      b[2 * i] = -y[i];
      b[2 * i + 1] = y[i];
    }

    T best = 1e7;
    rep(mask, 0, 1 << 3) {
      auto A2 = A;
      rep(bit, 0, 3) {
        if (mask & (1 << bit)) {
          rep(i, 0, 2 * n) A2[i][bit + 1] *= -1;
        }
      }

      LPSolver solver(A2, b, c);

      vd sol;
      T val = solver.solve(sol);
      assert(val <= 0);
      if (val > -inf) best = min(best, -val);
    }
    cout << fixed << setprecision(12) << best * best << '\n';
  }
}