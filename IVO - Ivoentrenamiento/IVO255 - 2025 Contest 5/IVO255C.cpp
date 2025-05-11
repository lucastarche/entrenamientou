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

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi p(n);
  rep(i, 0, n) cin >> p[i], p[i]--;

  UF uf(n);
  rep(i, 0, n) {
    string s;
    cin >> s;
    rep(j, 0, n) if (s[j] == '1') uf.join(i, j);
  }

  vector<vi> comps(n);
  rep(i, 0, n) comps[uf.find(i)].push_back(p[i]);
  rep(i, 0, n) sort(all(comps[i]));

  vi seen(n), ans(n);
  rep(i, 0, n) {
    int c = uf.find(i);
    ans[i] = comps[c][seen[c]++];
  }
  rep(i, 0, n) cout << ans[i] + 1 << " \n"[i == n - 1];
}
