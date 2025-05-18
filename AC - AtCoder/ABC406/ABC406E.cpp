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

const int SIZE = 60;
const ll MOD = 998244353;

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % MOD, e /= 2)
    if (e & 1) ans = ans * b % MOD;
  return ans;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // vl fact(SIZE + 1, 1), facti(SIZE + 1, 1);
  // rep(i, 0, SIZE) fact[i + 1] = fact[i] * (i + 1) % MOD;
  // facti.back() = modinv(fact.back());
  // per(i, 0, SIZE) facti[i] = facti[i + 1] * (i + 1) % MOD;

  // const auto choose = [&](int n, int k) { return fact[n] * (facti[k] * facti[n - k] % MOD) % MOD; };

  int t;
  cin >> t;
  while (t--) {
    ll n;
    int k;
    cin >> n >> k;

    vector<vector<vector<ll>>> ways(SIZE + 1, vector(SIZE + 1, vl(2, 0))), sum = ways;
    ways[SIZE][0][1] = 1;

    per(b, 0, SIZE) rep(cnt, 0, SIZE) {
      bool d = (n & (1LL << b)) > 0;
      ll val = (1LL << b) % MOD;

      // menor, pongo cero
      ways[b][cnt][0] = (ways[b][cnt][0] + ways[b + 1][cnt][0]) % MOD;
      sum[b][cnt][0] = (sum[b][cnt][0] + sum[b + 1][cnt][0]) % MOD;

      // menor, pongo uno
      ways[b][cnt + 1][0] = (ways[b][cnt + 1][0] + ways[b + 1][cnt][0]) % MOD;
      sum[b][cnt + 1][0] = (sum[b][cnt + 1][0] + sum[b + 1][cnt][0] + ways[b + 1][cnt][0] * val) % MOD;

      if (d == 0) {
        ways[b][cnt][1] = (ways[b][cnt][1] + ways[b + 1][cnt][1]) % MOD;
        sum[b][cnt][1] = (sum[b][cnt][1] + sum[b + 1][cnt][1]) % MOD;
      } else {
        ways[b][cnt][0] = (ways[b][cnt][0] + ways[b + 1][cnt][1]) % MOD;
        sum[b][cnt][0] = (sum[b][cnt][0] + sum[b + 1][cnt][1]) % MOD;

        ways[b][cnt + 1][1] = (ways[b][cnt + 1][1] + ways[b + 1][cnt][1]) % MOD;
        sum[b][cnt + 1][1] = (sum[b][cnt + 1][1] + sum[b + 1][cnt][1] + ways[b + 1][cnt][1] * val) % MOD;
      }
    }

    ll ans = (sum[0][k][0] + sum[0][k][1]) % MOD;
    cout << ans << '\n';
  }
}
