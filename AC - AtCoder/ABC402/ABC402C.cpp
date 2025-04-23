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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vi cnt(m);
  vector<vi> adj(n);
  rep(i, 0, m) {
    int k;
    cin >> k;
    cnt[i] = k;
    rep(j, 0, k) {
      int x;
      cin >> x, x--;
      adj[x].push_back(i);
    }
  }

  vi b(n);
  rep(i, 0, n) cin >> b[i], b[i]--;

  int ans = 0;
  rep(i, 0, n) {
    for (auto x : adj[b[i]]) cnt[x]--, ans += (cnt[x] == 0);
    cout << ans << '\n';
  }
}
