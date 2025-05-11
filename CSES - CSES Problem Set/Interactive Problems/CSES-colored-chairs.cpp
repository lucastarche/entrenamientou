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

bool query(int x) {
  cout << "? " << x + 1 << '\n';
  cout.flush();

  char ans;
  cin >> ans;
  return ans == 'R';
}

void answer(int x) {
  cout << "! " << x + 1 << '\n';
  cout.flush();
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  bool left = query(0), right = query(n - 1);
  if (left == right) {
    answer(n - 1);
    return 0;
  }

  int lo = 0, hi = n - 1;
  while (hi - lo > 2) {
    int mid = (lo + hi) / 2;
    if (lo % 2 != mid % 2) mid--;
    bool val = query(mid);

    if (val == left) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  if (query(lo + 1) == left) {
    answer(lo);
  } else {
    answer(lo + 1);
  }
}
