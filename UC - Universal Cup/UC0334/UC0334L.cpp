#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)a; i < (int)b; ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x.size())

using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

pll solve(ll a, ll b) { return {(a + b) / 2, (b - a) / 2}; }

ll sqrtInt(ll x) {
  ll lo = sqrt(x) - 10, hi = lo + 20;
  while (hi - lo > 1) {
    ll mid = (lo + hi) / 2;
    if (mid * mid <= x) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  return lo;
}

using ull = unsigned long long;
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_clzll(n - 1), d = n >> s;
  for (ull a : A) {
    ull p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
    if (p != n - 1 && i != s) return false;
  }
  return true;
}

ull pollard(ull n) {
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ull x) { return modmul(x, x, n) + i; };
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}

vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), all(r));
  return l;
}

vl divisors(ll x) {
  auto primes = factor(x);
  map<ll, ll> freq;
  for (auto p : primes) freq[p]++;

  vl divi = {1};
  for (auto [p, f] : freq) {
    ll mult = p;
    int s = sz(divi);
    rep(i, 1, f + 1) {
      rep(j, 0, s) divi.push_back(divi[j] * mult);
      mult *= p;
    }
  }
  return divi;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int T;
  cin >> T;
  while (T--) {
    ll s, t;
    cin >> s >> t;

    ll sq = sqrtInt(s + t);
    if (sq * sq == s + t) {
      cout << 1 << " " << t << '\n';
      continue;
    }

    bool solved = false;
    ll delta = abs(s - t);
    for (ll d : divisors(delta)) {
      if (d % 2 != (delta / d) % 2) continue;

      auto [k1, k2] = solve(d, delta / d);
      if (s < t) swap(k1, k2);
      if (s < k1 * k1 && t < k2 * k2) {
        solved = true;
        cout << 2 << " " << k1 * k1 - s << " " << t << '\n';
        break;
      }
    }

    if (solved) continue;

    ll k3 = sqrtInt(t) + 1;
    ll k1 = sqrtInt(s + t + 2 * k3 + 1) + 1;
    if (k1 % 2 == (s + t) % 2) k1++;
    k1 += 10000;
    k3 = (k1 * k1 - s - t - 1) / 2;

    assert(k3 * k3 > t);
    cout << 3 << " " << t + 2 * k3 + 1 << " " << k3 * k3 - t << " " << t << '\n';
  }
}