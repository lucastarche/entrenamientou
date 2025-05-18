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

const int MAX_DEPTH = 63;
int depth(ll x) { return 63 - __builtin_clzll(x); }
void add(ll &x, ll y, ll z) { x = ((x + y) % z + z) % z; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int q;
  cin >> q;
  vector<pair<ll, ll>> shift(MAX_DEPTH, {0, 0});
  while (q--) {
    int type;
    cin >> type;

    if (type <= 2) {
      ll x, k;
      cin >> x >> k;
      int d = depth(x);
      add((type == 1 ? shift[d].first : shift[d].second), k, 1LL << d);
    } else {
      ll x;
      cin >> x;
      vector<ll> ans = {x};

      int d = depth(x);
      ll node = (x + shift[d].first + shift[d].second) % (1LL << d) + (1LL << d);
      node /= 2;

      while (d--) {
        ll val = (node + (1LL << d) - shift[d].first) % (1LL << d) + (1LL << d);
        ans.push_back(val);

        node = (node + (1LL << d) + shift[d].second) % (1LL << d) + (1LL << d);
        node /= 2;
      }

      for (auto x : ans) cout << x << ' ';
      cout << '\n';
    }
  }
}
