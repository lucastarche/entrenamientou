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

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  // Poner YES / NO en lugar de Yes / No me costó cinco minutos de penalty XD
  cout << (pii(a, b) > pii(c, d) ? "Yes" : "No") << '\n';
}
