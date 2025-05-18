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

const ll MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vl f(n + 1, 0);
  vl fact(n + 1, 1);
  fact[2] = 2;

  rep(i, 3, n + 1) {
    fact[i] = fact[i - 1] * i % MOD;
    f[i] = (2LL * f[i - 1] + (i - 2) * fact[i - 1]) % MOD;
  }
  cout << f.back() << '\n';
}
