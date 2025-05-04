/*
Busco "probabilidad de que la cola más larga mida a lo sumo $x$" $\forall x$, esto queda una DP, donde la "capacidad" de cada cuarto es $a_i \cdot x$, uso esto para recuperar el valor esperado.
*/
#include <bits/stdc++.h>

using namespace std;
using ld = long double;

const int MAX_N = 50;
ld choose[MAX_N + 1][MAX_N + 1];

// Probability of distributing the students, so the length of the longest queue is at most x
ld solve(const vector<int> &a, int n, int x) {
  const int m = (int)a.size();

  // f(i, k) is the number of ways to distribute k students into the first i rooms,
  // so the length of the longest queue is at most x
  vector<vector<ld>> f(m + 1, vector<ld>(n + 1, 0));
  f[0][0] = 1;

  for (int i = 0; i < m; i++) {
    for (int k = 0; k <= n; k++) {
      // We want the length to not exceed x, so y <= a[i] * x
      for (int y = 0; y + k <= n && y <= a[i] * x; y++) {
        f[i + 1][k + y] += f[i][k] * choose[n - k][y];
      }
    }
  }

  // Divide by the total number of ways
  return f[m][n] / powl(m, n);
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  // Precompute binomial coefficients
  choose[0][0] = 1;
  for (int i = 0; i < MAX_N; i++) {
    for (int j = 0; j <= MAX_N; j++) {
      choose[i + 1][j] += choose[i][j];
      if (j + 1 <= MAX_N) choose[i + 1][j + 1] += choose[i][j];
    }
  }

  int n, m;
  cin >> n >> m;

  vector<int> a(m);
  for (int i = 0; i < m; i++) cin >> a[i];

  ld ans = 0.0l;
  for (int x = 0; x <= n; x++) {
    ans += 1.0l - solve(a, n, x);
  }
  cout << fixed << setprecision(10) << ans << '\n';
}
