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

const int MAX_X = 1e9;

bool query(int x) {
  cout << "? " << x << '\n';
  cout.flush();

  string ans;
  cin >> ans;
  return ans == "YES";
}

void answer(int x) {
  cout << "! " << x << '\n';
  cout.flush();
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int lo = 0, hi = MAX_X;
  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if (query(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  answer(hi);
}
