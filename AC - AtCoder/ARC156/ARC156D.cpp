#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const int BITS = 52;
const int MAX_X = 1000;
using Mask = bitset<2 * MAX_X>;

Mask half(const Mask &m) {
  Mask ans;
  rep(i, 0, MAX_X) ans.set(i, m.test(2 * i) ^ m.test(2 * i + 1));
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll k;
  cin >> n >> k;
  vi a(n);
  rep(i, 0, n) cin >> a[i];

  // Idea general: notar que si una secuencia no es palindrómica, tengo la secuencia y su reverso -> contribuye cero
  // Me interesa el elemento del medio (si k es impar) en cada paso, pienso como que voy recursivamente
  // Al final, el elemento que elijo después de partir x veces contribuye 2^x * a[i] a la suma

  Mask carry;
  carry.set(0);

  int missing = __builtin_popcountll(k);

  ll ans = 0;
  rep(b, 0, BITS) {
    carry = half(carry);
    if (k & (1LL << b)) {
      Mask next;
      rep(i, 0, n) next ^= carry << a[i];
      swap(next, carry);

      missing--;
    }

    bool isSet = false;
    rep(i, 0, 2 * MAX_X) if (i % 2 == 1) isSet ^= carry.test(i);

    // Nota: la segunda condición rara es porque nos falta elegir el resto de elementos, quedan `missing` elecciones,
    // con N opciones cada una, miro la paridad de N^missing
    if (isSet && (missing == 0 || n % 2 == 1)) ans += 1LL << b;
  }
  cout << ans << '\n';
}
