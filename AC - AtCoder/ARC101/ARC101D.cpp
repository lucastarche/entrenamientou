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

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }

  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

ll countPairs(const vi &a, int x) {
  const int n = sz(a);

  FT ft(2 * n + 1);
  const auto update = [&](int pos, ll dif) { ft.update(pos + n, dif); };
  const auto query = [&](int pos) { return ft.query(pos + n); };
  update(0, +1);

  ll ans = 0;
  int curr = 0;
  for (auto y : a) {
    if (y >= x) {
      curr++;
    } else {
      curr--;
    }

    ans += query(curr + 1);
    update(curr, +1);
  }

  return ans;
}

// Nota: el Fenwick está completamente al pedo
// Solo nos interesa la suma en [-inf, curr] del array de frecuencias en cada momento
// Como curr se mueve por +1 o -1, puedo mantener este número en O(1)
ll countPairsFaster(const vi &a, int x) {
  const int n = sz(a);
  vi freq(2 * n + 1);
  freq[0 + n]++;

  int curr = n;
  ll ans = 0, pfx = 1;
  for (auto y : a) {
    if (y >= x) {
      pfx += freq[++curr];
    } else {
      pfx -= freq[curr--];
    }

    ans += pfx;
    freq[curr]++, pfx++;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  vi sorted(a);
  sort(all(sorted));

  ll pairs = (ll)(n) * (n + 1) / 2;

  int lo = 0, hi = n;
  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if (countPairsFaster(a, sorted[mid]) >= pairs / 2) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << sorted[lo] << '\n';
}
