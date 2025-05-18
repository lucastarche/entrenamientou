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

const int MAX_N = 3e5 + 10;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vi mu(MAX_N, 1);
  vb prime(MAX_N, true);
  prime[0] = prime[1] = false;
  rep(p, 2, MAX_N) {
    if (not prime[p]) continue;
    mu[p] = -1;
    for (int k = 2 * p; k < MAX_N; k += p) mu[k] *= -1, prime[k] = false;
    for (ll k = (ll)p * p; k < MAX_N; k += (ll)p * p) mu[k] = 0;
  }

  int n;
  cin >> n;

  vi pfx(MAX_N);
  vb seen(MAX_N);
  rep(i, 0, n) {
    int x;
    cin >> x;
    pfx[x]++, seen[x] = true;
  }

  rep(i, 1, MAX_N) pfx[i] += pfx[i - 1];

  ll ans = 0;
  rep(g, 1, MAX_N) if (mu[g] != 0) {
    ll sum = 0, cnt = 0, curr = 0;

    for (int k = g; k < MAX_N; k += g) {
      if (seen[k]) {
        curr += cnt * pfx[k - 1] - sum;
        sum += pfx[k], cnt++;
      }
    }

    ans += curr * mu[g];
  }
  cout << ans << '\n';
}
